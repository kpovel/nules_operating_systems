@echo off
:loop
if "%1"=="" goto :eof

type "%1" | more
shift
goto :loop

