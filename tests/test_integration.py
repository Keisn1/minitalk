#!/usr/bin/env python3

import subprocess
import time
import signal


def test_integration():
    srv_p = subprocess.Popen(
        "./server",
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,  # Captures both stdout and stderr
        text=True,  # Ensure output is in text mode (Python 3.7+)
    )

    assert srv_p.stdout is not None

    time.sleep(0.001)
    srv_p.send_signal(signal.SIGINT)
    time.sleep(0.001)

    stdout, _ = srv_p.communicate()

    lines = stdout.split("\n")[:-1]

    assert "Server pid: " in lines[0]
    assert "Ready to receive messages..." == lines[1]
    assert "Goodbye." == lines[-1]


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
