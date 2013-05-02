TITLE TA Test Driver

@echo off


rem setting up environment variables needed for VS compiler
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86_amd64

rem compiling the .obj
cl /EHsc /Fedont_run_me.exe Student_Code\*.cpp ignoreme.lib

rem if compilation failed, goto error section
if ERRORLEVEL 1 goto error 

rem cleanup unnecessary generated files
del *.obj

rem run the driver in another window
.\dont_run_me.exe
del dont_run_me.exe
pause

exit

:error

rem remove any generated files
del *.obj

echo ---------------------------------------------------------------------
echo                      Error: Could not compile
echo            Make sure your factory no longer returns NULL,
echo            as this can prevent the test driver from working.
echo ---------------------------------------------------------------------

pause
exit
