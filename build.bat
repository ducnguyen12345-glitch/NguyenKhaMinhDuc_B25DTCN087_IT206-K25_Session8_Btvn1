@echo off
echo Building main.c...
gcc main.c -o main.exe
if %errorlevel% neq 0 (
  echo Build failed.
  exit /b %errorlevel%
)
echo Build succeeded: main.exe
