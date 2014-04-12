rem 1st parameter: file name, 2nd parameter: word length
grep -c _Learn_assert %1
if %errorlevel% neq 0 goto badend 
libalf\examples\online.exe %1 %2 --auto f --v 
goto theend
:badend
echo source file must include a _Learn_assert line
:theend