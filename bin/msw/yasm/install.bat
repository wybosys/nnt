@echo off

if %PROCESSOR_ARCHITECTURE% == "AMD64" (
		goto win32
	) else (
		goto win64
	)

:win32
	echo "32"
	goto end

:win64
	rem msvc9 installed
	if exist "%ProgramFiles(x86)%\Microsoft Visual Studio 9.0\VC\VCProjectDefaults" (
		copy yasm.rules "%ProgramFiles(x86)%\Microsoft Visual Studio 9.0\VC\VCProjectDefaults\" /Y
	)
	if exist "%ProgramFiles(x86)%\MSBuild\Microsoft.Cpp\v4.0\V110\BuildCustomizations" (
		copy Win32\yasm.exe "%ProgramFiles(x86)%\Microsoft Visual Studio 11.0\VC\bin" /Y
		copy Win32\yasm.props "%ProgramFiles(x86)%\MSBuild\Microsoft.Cpp\v4.0\V110\BuildCustomizations" /Y
		copy Win32\yasm.targets "%ProgramFiles(x86)%\MSBuild\Microsoft.Cpp\v4.0\V110\BuildCustomizations" /Y
		copy Win32\yasm.xml "%ProgramFiles(x86)%\MSBuild\Microsoft.Cpp\v4.0\V110\BuildCustomizations" /Y
	)
	goto end
	
:end
	echo "completed"
	