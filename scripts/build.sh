#! /bin/sh
EXE=minimake
Sys=$(uname)
if [ -z "${Sys##*"Win"*}" ]
then
EXE="$EXE.exe"
fi
if [ -z "${Sys##*"DOS"*}" ]
then
EXE="$EXE.exe"
fi
echo "Output:bin/$EXE"
gcc ./src/**/*.c -DVERSION='"0.0.2.0"' -o "bin/$EXE"
