#!/bin/bash
# 1st parameter: file name, 2nd parameter: word length, 3rd (optional) parameter: unwind bound of user loops

if [ -z "$2" ]
then
libalf/examples/online $1 0 --auto f --v --user-unwind 1
elif [ -z "$3" ]
then
libalf/examples/online $1 $2 --auto f --v --user-unwind 1
else
libalf/examples/online $1 $2 --auto f --v --user-unwind $3
fi
