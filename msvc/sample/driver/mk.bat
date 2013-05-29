@echo OFF

cd ..\..\..\Classes\Core
build

cd ..\Kernel
build

cd ..\TL
build

cd ..\..\msvc\sample\driver
rem C:\WinDDK\7600.16385.1\tools\Chkinf\chkinf.bat driver.inf
build

copy driver.inf \\localhost\shared\ /Y
copy build\amd64\* \\localhost\shared\ /Y
copy x64\Release\*.exe \\localhost\shared\ /Y
copy x64\Release\*.dll \\localhost\shared\ /Y

Inf2cat /driver:\\localhost\shared\ /os:7_X64
signtool sign /f ..\..\..\cert\win\kernel.pfx \\localhost\shared\driver.cat
signtool sign /f ..\..\..\cert\win\kernel.pfx \\localhost\shared\NntSampleDriver.sys