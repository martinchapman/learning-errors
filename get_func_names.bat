@echo off
rem making a list of function names in func_names.data
goto-cl %1.c
goto-instrument --function-enter _Learn_function_enter --dump-c %1.exe a.c
grep _Learn_function_enter a.c | grep -v void | grep -v // | sed -e s/"_Learn_function_enter((signed char \*)\"c::"// -e s/"\");"// > %2