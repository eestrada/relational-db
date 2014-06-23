@echo off
PATH C:\mingw\bin\
echo Compiling...
g++ -w -o dont_run_me.exe ignore_me.o Student_Code/*.cpp Student_Code/*.h
if ERRORLEVEL 1 goto error 
START "Passoff" dont_run_me.exe
exit

:error
echo ---------------------------------- ERROR -------------------
echo If you see something like 'permission denied', close this window and try running it again. Also check if the driver is currently running.
echo ------------------------------------------------------------
pause
exit