rem 1st parameter: file name, 2nd parameter: word length 3rd (optional) parameter: unwind bound of user loops
grep -c _Learn_assert %1
if %errorlevel% neq 0 goto badend 
libalf\examples\online.exe %1 %2 --auto f --v --user-unwind %3
dotty a.dot
goto theend
:badend
echo source file must include a _Learn_assert line
:theend