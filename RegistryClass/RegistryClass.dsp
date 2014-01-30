# Microsoft Developer Studio Project File - Name="RegistryClass" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Generic Project" 0x010a

CFG=RegistryClass - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RegistryClass.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RegistryClass.mak" CFG="RegistryClass - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RegistryClass - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "RegistryClass - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 1
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
MTL=midl.exe

!IF  "$(CFG)" == "RegistryClass - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# Begin Special Build Tool
OutDir=.\Release
SOURCE="$(InputPath)"
PostBuild_Cmds=CScript autover.js -n NextBuildNumber.txt -o autover.h	copy *.pdf $(OutDir)	copy ChangeLog.txt $(OutDir)	copy License.txt $(OutDir)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "RegistryClass - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=CScript autover.js -n NextBuildNumber.txt -o autover.h
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "RegistryClass - Win32 Release"
# Name "RegistryClass - Win32 Debug"
# Begin Group "Documents"

# PROP Default_Filter "txt,html,htm,doc,pdf"
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

SOURCE=.\manual.pdf
# End Source File
# Begin Source File

SOURCE=.\NextBuildNumber.txt
# End Source File
# Begin Source File

SOURCE=.\reference.pdf
# End Source File
# End Group
# Begin Source File

SOURCE=.\RegistryClass.h

!IF  "$(CFG)" == "RegistryClass - Win32 Release"

# Begin Custom Build
OutDir=.\Release
InputPath=.\RegistryClass.h

BuildCmds= \
	copy     Registry*.h     $(OutDir)\ 

"$(OutDir)\RegistryClass.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\Registry.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\RegistryKey.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\RegistryValue.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "RegistryClass - Win32 Debug"

# Begin Custom Build
OutDir=.\Debug
InputPath=.\RegistryClass.h

BuildCmds= \
	copy     Registry*.h     $(OutDir)\ 

"$(OutDir)\RegistryClass.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\Registry.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\RegistryKey.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\RegistryValue.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
