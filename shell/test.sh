#!/bin/bash 

echo "Hello Shell"

read VAR
echo "VAR is $VAR"

expr $VAR - 5

test "Hello"="HelloWorld"

test $VAR -eq 10

test -d ./Android

exec ./othershell.sh

exit
