<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: regclass - Win32 (WCE ARMV4) Debug--------------------
</h3>
<h3>Command Lines</h3>
Creating temporary file "C:\DOCUME~1\Matthew\LOCALS~1\Temp\RSP1EC.bat" with contents
[
@echo off
copy         ..\..\RegistryValue.h         include\
]
Creating command line "C:\DOCUME~1\Matthew\LOCALS~1\Temp\RSP1EC.bat"
Creating temporary file "C:\DOCUME~1\Matthew\LOCALS~1\Temp\RSP1ED.bat" with contents
[
@echo off
copy         ..\..\RegistryKey.h         include\
]
Creating command line "C:\DOCUME~1\Matthew\LOCALS~1\Temp\RSP1ED.bat"
Creating temporary file "C:\DOCUME~1\Matthew\LOCALS~1\Temp\RSP1EE.bat" with contents
[
@echo off
copy         ..\..\RegistryClass.h         include\
]
Creating command line "C:\DOCUME~1\Matthew\LOCALS~1\Temp\RSP1EE.bat"
Creating temporary file "C:\DOCUME~1\Matthew\LOCALS~1\Temp\RSP1EF.bat" with contents
[
@echo off
copy         ..\..\Registry.h         include\
]
Creating command line "C:\DOCUME~1\Matthew\LOCALS~1\Temp\RSP1EF.bat"
Creating command line "rc.exe /l 0x409 /fo"ARMV4Dbg/regclass.res" /i "\Documents and Settings\Matthew\My Documents\My Projects\C C++\RegistryClass" /d UNDER_CE=420 /d _WIN32_WCE=420 /d "DEBUG" /d "UNICODE" /d "_UNICODE" /d "WIN32_PLATFORM_PSPC=400" /d "ARM" /d "_ARM_" /d "ARMV4" /d "_AFXDLL" /r "C:\Documents and Settings\Matthew\My Documents\My Projects\C C++\RegistryClass\regclass.rc"" 
Performing Custom Build Step on ..\..\RegistryValue.h
        1 file(s) copied.
Performing Custom Build Step on ..\..\RegistryKey.h
        1 file(s) copied.
Performing Custom Build Step on ..\..\RegistryClass.h
        1 file(s) copied.
Performing Custom Build Step on ..\..\Registry.h
        1 file(s) copied.
Creating temporary file "C:\DOCUME~1\Matthew\LOCALS~1\Temp\RSP1F0.tmp" with contents
[
/nologo /W3 /Zi /Od /I "include\\" /D "DEBUG" /D "ARM" /D "_ARM_" /D "ARMV4" /D UNDER_CE=420 /D _WIN32_WCE=420 /D "WIN32_PLATFORM_PSPC=400" /D "UNICODE" /D "_UNICODE" /D "_AFXDLL" /D "_AFXEXT" /FR"ARMV4Dbg/" /Fp"ARMV4Dbg/regclass.pch" /Yu"stdafx.h" /Fo"ARMV4Dbg/" /Fd"ARMV4Dbg/" /MC /c 
"C:\Documents and Settings\Matthew\My Documents\My Projects\C C++\RegistryClass\Helpers.cpp"
"C:\Documents and Settings\Matthew\My Documents\My Projects\C C++\RegistryClass\regclass.cpp"
"C:\Documents and Settings\Matthew\My Documents\My Projects\C C++\RegistryClass\Registry.cpp"
"C:\Documents and Settings\Matthew\My Documents\My Projects\C C++\RegistryClass\RegistryKey.cpp"
"C:\Documents and Settings\Matthew\My Documents\My Projects\C C++\RegistryClass\RegistryValue.cpp"
]
Creating command line "clarm.exe @C:\DOCUME~1\Matthew\LOCALS~1\Temp\RSP1F0.tmp" 
Creating temporary file "C:\DOCUME~1\Matthew\LOCALS~1\Temp\RSP1F1.tmp" with contents
[
/nologo /W3 /Zi /Od /I "include\\" /D "DEBUG" /D "ARM" /D "_ARM_" /D "ARMV4" /D UNDER_CE=420 /D _WIN32_WCE=420 /D "WIN32_PLATFORM_PSPC=400" /D "UNICODE" /D "_UNICODE" /D "_AFXDLL" /D "_AFXEXT" /FR"ARMV4Dbg/" /Fp"ARMV4Dbg/regclass.pch" /Yc"stdafx.h" /Fo"ARMV4Dbg/" /Fd"ARMV4Dbg/" /MC /c 
"C:\Documents and Settings\Matthew\My Documents\My Projects\C C++\RegistryClass\StdAfx.cpp"
]
Creating command line "clarm.exe @C:\DOCUME~1\Matthew\LOCALS~1\Temp\RSP1F1.tmp" 
Creating temporary file "C:\DOCUME~1\Matthew\LOCALS~1\Temp\RSP1F2.tmp" with contents
[
/nologo /base:"0x00100000" /stack:0x10000,0x1000 /entry:"_DllMainCRTStartup" /dll /incremental:yes /pdb:"ARMV4Dbg/regclass.pdb" /debug /def:".\regclass.def" /out:"ARMV4Dbg/regclass.dll" /implib:"ARMV4Dbg/regclass.lib" /subsystem:windowsce,4.20 /align:"4096" /MACHINE:ARM 
".\ARMV4Dbg\Helpers.obj"
".\ARMV4Dbg\regclass.obj"
".\ARMV4Dbg\Registry.obj"
".\ARMV4Dbg\RegistryKey.obj"
".\ARMV4Dbg\RegistryValue.obj"
".\ARMV4Dbg\StdAfx.obj"
".\ARMV4Dbg\regclass.res"
]
Creating command line "link.exe @C:\DOCUME~1\Matthew\LOCALS~1\Temp\RSP1F2.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
StdAfx.cpp
Compiling...
Helpers.cpp
regclass.cpp
Registry.cpp
RegistryKey.cpp
RegistryValue.cpp
Generating Code...
Linking...
   Creating library ARMV4Dbg/regclass.lib and object ARMV4Dbg/regclass.exp




<h3>Results</h3>
regclass.dll - 0 error(s), 0 warning(s)
</pre>
</body>
</html>
