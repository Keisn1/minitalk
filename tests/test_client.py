#!/usr/bin/env python3
from functools import reduce
import subprocess
import signal


def test_client():
    ps_command = subprocess.Popen(
        ["ps", "-eo", "pid,user"],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    ps_out, _ = ps_command.communicate()
    ps_out = list(
        map(
            lambda x: (int(x[0]), x[1]),
            map(lambda x: x.strip().split(" "), ps_out.split("\n")[1:30]),
        )
    )

    pid_no_perm = list(filter(lambda x: x[1] == "root", ps_out))[0][0]
    pid_not_ex = [i + 1 for i, pid in enumerate(ps_out) if (i + 1) != pid[0]][0]
    print(pid_not_ex)

    client_p = subprocess.Popen(
        ["./client", str(pid_no_perm), "my message"],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    client_p.wait()

    assert client_p.stdout is not None
    stdout_client = client_p.stdout.readline()

    assert (
        "You don't have permission to send a message to that target\n" == stdout_client
    )

    client_p = subprocess.Popen(
        ["./client", str(pid_not_ex), "my message"],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    client_p.wait()

    assert client_p.stdout is not None
    stdout_client = client_p.stdout.readline()

    assert "The target you specified does not exist\n" == stdout_client

    # srv_p = subprocess.Popen(
    #     "./server",
    #     stdout=subprocess.PIPE,
    #     stderr=subprocess.STDOUT,  # Captures both stdout and stderr
    #     text=True,  # Ensure output is in text mode (Python 3.7+)
    # )

    # assert srv_p.stdout is not None
    # stdout_srv = srv_p.stdout.readline()
    # assert "Server pid: " in stdout_srv
    # server_pid = stdout_srv.split(" ")[-1]
    # srv_p.send_signal(signal.SIGINT)

    # client_p = subprocess.Popen(
    #     ["./client", server_pid, "my message"],
    #     stdout=subprocess.PIPE,
    #     stderr=subprocess.STDOUT,
    #     text=True,
    # )
    # client_p.wait()

    # assert client_p.stdout is not None
    # stdout_client = client_p.stdout.readline()

    # assert "The target you specified does not exist\n" == stdout_client


def test_client_valgrind():
    client_p = subprocess.Popen(
        ["valgrind", "--leak-check=full", "./client", "0"],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )

    assert client_p.stdout is not None
    stdout_client = client_p.stdout.readline()

    assert "Error" == stdout_client
