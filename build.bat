@echo off
setlocal enabledelayedexpansion

set "file_list="

for %%f in ("src\*.c") do (
    set "file_list=!file_list! %%f"
)

gcc !file_list! -o "bin/clox"

if %errorlevel% equ 0 (
    echo Compilation successful.
) else (
    echo Compilation failed.
)

endlocal