@echo off
setlocal enableextensions

:loop
set "has_empty_dir="
for /d /r %%d in (*) do (
    if /i "%%~nd"=="branches" (
        echo Skipping directory: "%%d"
    ) else if not "%%~nd"=="tmp" (
        dir /a /b "%%d" 2>nul | findstr "^" >nul || (
            rd "%%d" 2>nul && (
                set "has_empty_dir=1"
                echo Deleted empty directory: "%%d"
            )
        )
    )
)

if defined has_empty_dir goto :loop

echo All empty directories have been deleted.

endlocal