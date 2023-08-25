@echo off
if "%1" == "" goto :bat

del *.%1
goto :end

:bat
del *.bat

:end

