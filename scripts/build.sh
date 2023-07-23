#! /bin/sh
EXE=minimake
Sys=$(uname)
if [ ! -d "./bin/" ]
then
	mkdir bin
fi
if [ -z "${Sys##*"Win"*}" ]
then
EXE="$EXE.exe"
fi
if [ -z "${Sys##*"DOS"*}" ]
then
EXE="$EXE.exe"
fi
echo "Output:bin/$EXE"
find ./src/ -name "*.c" | xargs gcc -DVERSION='"1.1.3.0"' -o "bin/$EXE"
