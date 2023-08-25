@echo off
:rename
if "%1" == "" goto :ok
if "%2" == "" goto :err

ren %1 %2
shift
shift
goto :rename

:ok
echo Successfully renamed all files
goto :end

:err
echo Missing new name for the "%1" file
goto :end

:end

