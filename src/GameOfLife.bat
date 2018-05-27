@echo off
SET IT=0;

:START
IF %IT%==10000 (
	goto END
)

cl /std:c++17 Source.cpp > nul
del State.txt > nul
cls
Source.exe
echo R^"(>> State.txt
Source.exe >> State.txt
echo E>> State.txt
echo R)^">> State.txt

SET /a IT=%IT%+1
goto START
:END