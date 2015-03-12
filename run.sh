#!/bin/bash
# 1st parameter: file name, 2nd (optional, in experiment mode) parameter: word length, 3rd (optional) parameter: unwind bound of user loops

if [ -z "$2" ]
then
echo 0 >word_length
libalf/examples/online $1 0 --auto f --v --user-unwind 1
elif [ -z "$3" ]
then
echo $2 >word_length
libalf/examples/online $1 $2 --auto f --v --user-unwind 1
else
    if [ "$1" == "--compare" ]
    then
    echo $0 >word_length
    libalf/examples/online $1 $2 $3 0 --auto f --v --user-unwind 1
    else
    echo $2 >word_length
    libalf/examples/online $1 $2 --auto f --v --user-unwind $3
    fi
fi