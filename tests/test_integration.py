#!/usr/bin/env python3

import subprocess
import time
import signal
import pytest


@pytest.mark.parametrize("msg", (["my messsage"]))
def test_integration(msg):
    srv_p = subprocess.Popen(
        "./server",
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,  # Captures both stdout and stderr
        text=True,  # Ensure output is in text mode (Python 3.7+)
    )

    assert srv_p.stdout is not None
    stdout_srv = srv_p.stdout.readline()
    assert "Server pid: " in stdout_srv
    server_pid = stdout_srv.split(" ")[-1]

    stdout_srv = srv_p.stdout.readline()
    assert "Ready to receive messages...\n" == stdout_srv

    client_p = subprocess.Popen(
        ["./client", server_pid, msg],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,  # Captures both stdout and stderr
        text=True,  # Ensure output is in text mode (Python 3.7+)
    )
    client_p.wait()

    # stdout_srv = srv_p.stdout.readline()
    stdout_srv = srv_p.stdout.read(len(msg))
    assert msg == stdout_srv

    time.sleep(0.01)
    srv_p.send_signal(signal.SIGINT)
    time.sleep(0.01)

    stdout_srv, _ = srv_p.communicate()
    assert "\nGoodbye.\n" == stdout_srv


def test_integration_valgrind():
    srv_p = subprocess.Popen(
        ["valgrind", "--leak-check=full", "./server"],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,  # Captures both stdout and stderr
        text=True,  # Ensure output is in text mode (Python 3.7+)
    )

    assert srv_p.stdout is not None

    time.sleep(0.1)
    srv_p.send_signal(signal.SIGINT)
    time.sleep(0.1)

    stdout, _ = srv_p.communicate()

    assert "All heap blocks were freed -- no leaks are possible" in stdout
    assert "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)" in stdout
