#!/usr/bin/env python3

import subprocess
import time
import signal
import pytest
import string
import random


def get_random_string(length):
    characters = string.ascii_letters + string.digits
    return "".join(random.choice(characters) for _ in range(length))


@pytest.mark.parametrize("messages", [["my message", "2nd message", "\n"]])
def test_server_multiple_messages(messages):
    srv_p = subprocess.Popen(
        "./server",
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,  # Captures both stdout and stderr
        text=True,  # Ensure output is in text mode (Python 3.7+)
    )

    assert srv_p.stdout is not None
    stdout_srv = srv_p.stdout.readline()
    assert "Server pid: " in stdout_srv
    server_pid = stdout_srv.split(" ")[-1].rstrip()

    stdout_srv = srv_p.stdout.readline()
    assert "Ready to receive messages...\n" == stdout_srv

    for msg in messages:
        client_p = subprocess.Popen(
            ["./client", str(server_pid), msg],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,  # Captures both stdout and stderr
            text=True,  # Ensure output is in text mode (Python 3.7+)
        )
        client_p.wait()

        stdout_srv = srv_p.stdout.read(len(msg))
        assert msg == stdout_srv

    time.sleep(0.01)
    srv_p.send_signal(signal.SIGINT)
    time.sleep(0.01)

    stdout_srv, _ = srv_p.communicate()
    assert "\nGoodbye.\n" == stdout_srv


# TODO flaky
def test_server_long_msg(length=100000):
    srv_p = subprocess.Popen(
        "./server",
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,  # Captures both stdout and stderr
        text=True,  # Ensure output is in text mode (Python 3.7+)
    )

    assert srv_p.stdout is not None
    stdout_srv = srv_p.stdout.readline()
    assert "Server pid: " in stdout_srv
    server_pid = stdout_srv.split(" ")[-1].rstrip()

    stdout_srv = srv_p.stdout.readline()
    assert "Ready to receive messages...\n" == stdout_srv

    msg = get_random_string(length)
    client_p = subprocess.Popen(
        ["./client", server_pid, msg],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,  # Captures both stdout and stderr
        text=True,  # Ensure output is in text mode (Python 3.7+)
    )
    client_p.wait()

    time.sleep(5)
    srv_p.send_signal(signal.SIGINT)

    stdout_srv, _ = srv_p.communicate()  # it is failing here, so not in the code
    print(len(stdout_srv))
    assert msg == stdout_srv[: -len("\nGoodbye.\n")]
    assert "\nGoodbye.\n" == stdout_srv[-len("\nGoodbye.\n") :]


def test_server_valgrind():
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
