@echo OFF

cd ..\..\..\Classes\Kernel
build

cd ..\..\msvc\sample\driver
build

copy driver.inf ..\..\..\exchange\ /Y
copy build\amd64\*.sys ..\..\..\exchange\ /Y

cd ..\..\..\exchange
signtool sign /f ..\cert\root.pfx NntSampleDriver.sys
Inf2cat /driver:.\ /os:7_X64

cd ..\msvc\sample\driver
