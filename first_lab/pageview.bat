@echo off
:loop
type %1 | more
shift
if not "%1" == "" goto loop

