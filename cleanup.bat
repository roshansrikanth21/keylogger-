@echo off
:: Save as: cleanup.bat
start /b injector.exe
del "%~f0" >nul 2>&1
