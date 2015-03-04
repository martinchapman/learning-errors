#!/bin/bash
# 1st parameter: file name, 2nd parameter: word length, 3rd (optional) parameter: unwind bound of user loops

if [ -z "$2" ]
then
echo 0 >word_length
libalf/examples/online $1 0 --auto f --v --user-unwind 1 $2
elif [ -z "$3" ]
then
echo $2 >word_length
libalf/examples/online $1 $2 --auto f --v --user-unwind 1 $3
else
echo $2 >word_length
libalf/examples/online $1 $2 --auto f --v --user-unwind $3 $4
fi
