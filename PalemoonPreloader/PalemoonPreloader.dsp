# Microsoft Developer Studio Project File - Name="PalemoonPreloader" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PalemoonPreloader - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PalemoonPreloader.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PalemoonPreloader.mak" CFG="PalemoonPreloader - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PalemoonPreloader - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PalemoonPreloader - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "PalemoonPreloader - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PalemoonPreloader - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G3 /MD /W3 /GX /O2 /I "..\RegistryClass\Release" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib strsafe.lib /nologo /subsystem:windows /pdb:none /machine:I386 /libpath:"..\RegistryClass\Release"
# Begin Special Build Tool
OutDir=.\Release
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ..\RegistryClass\Release\regclass.dll $(OutDir)	CScript autover.js -n NextBuildNumber.txt -o autover.h
# End Special Build Tool

!ELSEIF  "$(CFG)" == "PalemoonPreloader - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GX /ZI /Od /I "..\RegistryClass\Debug" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib strsafe.lib /nologo /subsystem:windows /map /debug /machine:I386 /pdbtype:sept /libpath:"..\RegistryClass\Debug"
# Begin Special Build Tool
OutDir=.\Debug
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ..\RegistryClass\Debug\regclass.dll $(OutDir)	CScript autover.js -n NextBuildNumber.txt -o autover.h
# End Special Build Tool

!ELSEIF  "$(CFG)" == "PalemoonPreloader - Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "PalemoonPreloader___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "PalemoonPreloader___Win32_Unicode_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "UnicodeDebug"
# PROP Intermediate_Dir "UnicodeDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\RegistryClass\Debug" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G3 /MDd /W3 /Gm /Gi /GX /ZI /Od /I "..\RegistryClass\Debug" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\RegistryClass\Debug"
# ADD LINK32 version.lib strsafe.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /map /debug /machine:I386 /pdbtype:sept /libpath:"..\RegistryClass\Debug"
# SUBTRACT LINK32 /profile
# Begin Special Build Tool
OutDir=.\UnicodeDebug
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ..\RegistryClass\Debug\regclassu.dll $(OutDir)	CScript autover.js -n NextBuildNumber.txt -o autover.h
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "PalemoonPreloader - Win32 Release"
# Name "PalemoonPreloader - Win32 Debug"
# Name "PalemoonPreloader - Win32 Unicode Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DefaultDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FileVersionInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\PalemoonPreloader.cpp
# End Source File
# Begin Source File

SOURCE=.\PalemoonPreloader.rc
# End Source File
# Begin Source File

SOURCE=.\Helpers.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\processes.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\autover.h
# End Source File
# Begin Source File

SOURCE=.\DefaultDlg.h
# End Source File
# Begin Source File

SOURCE=.\FileVersionInfo.h
# End Source File
# Begin Source File

SOURCE=.\PalemoonPreloader.h
# End Source File
# Begin Source File

SOURCE=.\helpers.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\processes.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\PalemoonPreloader-Off.ico"
# End Source File
# Begin Source File

SOURCE=.\res\PalemoonPreloader.ico
# End Source File
# Begin Source File

SOURCE=.\res\PalemoonPreloader.rc2
# End Source File
# Begin Source File

SOURCE=".\res\PalemoonPreloader16-Off.ico"
# End Source File
# Begin Source File

SOURCE=.\res\PalemoonPreloader16.ico
# End Source File
# End Group
# Begin Group "Documents"

# PROP Default_Filter "txt;doc;rtf;html;htm"
# Begin Source File

SOURCE=.\Building.txt
# End Source File
# Begin Source File

SOURCE=.\ChangeLog.txt
# End Source File
# Begin Source File

SOURCE=.\License.txt
# End Source File
# Begin Source File

SOURCE=.\Manual.html
# End Source File
# Begin Source File

SOURCE=.\NextBuildNumber.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Group
# Begin Group "Scripts"

# PROP Default_Filter "js;vbs"
# Begin Source File

SOURCE=.\autover.js
# End Source File
# End Group
# End Target
# End Project
