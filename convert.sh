@echo off
sed -e s/"_Learn_function_exit((const char \*)\"c::main\");"/@@/ -e s/"_Learn_function_exit((const char \*)\"c::[a-zA-Z0-9_$]*\");"// -e s/"@@"/"Learn_trap();"/ -e s/"int exit"/"@@"/ -e s/"\(exit([a-zA-Z0-9_$]*)\)"/"Learn_trap\(\); \n &"/ -e s/"@@"/"int exit"/ -e s/"signed int _Learn_letter;"// -e s/"void _Learn_branch(const char \*)"/"void _Learn_branch(int _Learn_letter) "/ -e s/"void _Learn_function_enter(const char \*)"/"void _Learn_function_enter(int _Learn_letter) "/  a.c > tmp.c
cp tmp.c a.c
sed -e s/"_Learn_function_enter((const char \*)\"c::_Learn_function_enter(0);\");"// -e s/"_Learn_function_enter((const char \*)\"c::_Learn_function_enter(1);\");"// -e s/"_Learn_function_enter((const char \*)\"c::_Learn_function_enter(2);\");"// -e s/"_Learn_function_enter((const char \*)\"c::_Learn_function_enter(3);\");"// -e s/"_Learn_function_enter((const char \*)\"c::_Learn_function_enter(4);\");"// -e s/"_Learn_function_enter((const char \*)\"c::_Learn_function_enter(5);\");"//  a.c > tmp.c
cp tmp.c a.c
