@echo off
rem Copyright 2024 Oğuz İsmail Uysal <oguzismailuysal@gmail.com>
rem
rem This program is free software: you can redistribute it and/or modify
rem it under the terms of the GNU General Public License as published by
rem the Free Software Foundation, either version 3 of the License, or
rem (at your option) any later version.
rem
rem This program is distributed in the hope that it will be useful,
rem but WITHOUT ANY WARRANTY; without even the implied warranty of
rem MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
rem GNU General Public License for more details.
rem
rem You should have received a copy of the GNU General Public License
rem along with this program. If not, see <https://www.gnu.org/licenses/>.

setlocal
set skip=0
set args=%*
set found=0
set next=new_target

:retry
rachel -s %skip% -- %args%
if errorlevel 2 (
	exit /b
) else if errorlevel 1 (
	if %found% == 1 (
		exit /b 0
	) else (
		goto %next%
	)
)

set found=1
echo more? [y]es, [n]o (default: no^) 1>&2
set reply=n
set /p reply=
if /i %reply:~0,1% == y (
	set /a skip+=1
	goto retry
)
exit /b 0

:new_target
set numbers=
set target=
for %%a in (%args%) do (
	call :arg %%a
)
set /a low=target-1
set /a high=target+1

:no_answer
set next=no_answer
echo try again? [+] %high%, [-] %low%, [new target], [n]o 1>&2
set reply=n
set /p reply=
if %reply% == + (
	set target=%high%
	set /a high+=1
) else if %reply% == - (
	set target=%low%
	set /a low-=1
) else if %reply% == n (
	exit /b 1
) else (
	set target=%reply%
	set next=new_target
)
set "args=%numbers% %target%"
goto retry

:arg
set "numbers=%numbers%%target% "
set target=%*
