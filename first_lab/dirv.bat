@echo off
:loop
if "%1"=="" goto end
dir %1 | more
shift
goto loop
:end
