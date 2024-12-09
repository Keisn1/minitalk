#!/usr/bin/env sh

rm -f srv_output.txt
touch srv_output.txt
../server | cat > srv_output.txt
