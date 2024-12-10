#!/usr/bin/env python3
from functools import reduce
import subprocess
import pytest


def pid_no_perm():
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
    return pid_no_perm


def pid_not_ex():
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
    pid_not_ex = [i + 1 for i, pid in enumerate(ps_out) if (i + 1) != pid[0]][0]
    return pid_not_ex


error_testdata = [
    (
        pid_no_perm(),
        "my message",
        "You don't have permission to send a message to that target\n",
    ),
    (pid_not_ex(), "my message", "The target you specified does not exist\n"),
    (-1, "my message", "Server pid must be greater 0\n"),
    (0, "my message", "Server pid must be greater 0\n"),
    (None, None, "Missing server pid and message\n"),
    ("12-12", "my message", "Not a process id\n"),
    ("asdf", "my message", "Not a process id\n"),
    ("123", None, "Missing message\n"),
    (None, "my message", "Missing message\n"),
]


@pytest.mark.parametrize("pid,msg,want", error_testdata)
def test_client_errors(pid, msg, want):
    cmd = ["./client"]
    if pid is not None:
        cmd += [str(pid)]
    if msg is not None:
        cmd += [msg]

    client_p = subprocess.Popen(
        cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    client_p.wait()

    assert client_p.stdout is not None
    stdout_client = client_p.stdout.readline()
    assert stdout_client == want


@pytest.mark.parametrize("pid,msg,want", error_testdata)
def test_client_errors_valgrind(pid, msg, want):
    cmd = ["valgrind", "--leak-check=full", "./client"]
    if pid is not None:
        cmd += [str(pid)]
    if msg is not None:
        cmd += [msg]

    client_p = subprocess.Popen(
        cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    client_p.wait()

    stdout_client, _ = client_p.communicate()

    assert "All heap blocks were freed -- no leaks are possible" in stdout_client
    assert (
        "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)"
        in stdout_client
    )
    assert want in stdout_client
