goto-cc $1.c -o $1.o
goto-instrument --function-enter _Learn_function_enter --dump-c $1.o a.c
grep _Learn_function_enter a.c | grep -v void | grep -v // | sed -e s/"_Learn_function_enter((const char \*)\"c::"// -e s/"\");"// > $2