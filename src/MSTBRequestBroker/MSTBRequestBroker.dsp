# Microsoft Developer Studio Project File - Name="MSTBRequestBroker" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=MSTBRequestBroker - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MSTBRequestBroker.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MSTBRequestBroker.mak" CFG="MSTBRequestBroker - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MSTBRequestBroker - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "MSTBRequestBroker - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/IPTV/2.开发区/4.机顶盒应用/6.settopbox_xpe/src/MSTBRequestBroker", JRAEAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MSTBRequestBroker - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_CONSOLE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 powrprof.lib STBCommon.lib Winmm.lib ServiceFramework.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=del      d:\settopbox\MSTBRequestBroker.exe	copy     F:\suddy\xpe_stb\src\MSTBRequestBroker\Release\MSTBRequestBroker.exe     d:\settopbox\MSTBRequestBroker.exe
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MSTBRequestBroker - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Powrprof.lib Winmm.lib ServiceFramework.lib STBCommon.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=del      d:\settopbox\MSTBRequestBroker.exe    	copy     F:\suddy\xpe_stb\src\MSTBRequestBroker\Debug\MSTBRequestBroker.exe     d:\settopbox\MSTBRequestBroker.exe
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "MSTBRequestBroker - Win32 Release"
# Name "MSTBRequestBroker - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BrokerServiceObject.cpp
# End Source File
# Begin Source File

SOURCE=.\DesktopBroker.cpp
# End Source File
# Begin Source File

SOURCE=.\DVBBroker.cpp
# End Source File
# Begin Source File

SOURCE=.\DVBCommunicatorClient.cpp
# End Source File
# Begin Source File

SOURCE=.\HotelPortalBroker.cpp
# End Source File
# Begin Source File

SOURCE=.\MSTBConfiguration.cpp
# End Source File
# Begin Source File

SOURCE=.\MSTBFunctionSwitcher.cpp
# End Source File
# Begin Source File

SOURCE=.\MSTBRequestBroker.cpp
# End Source File
# Begin Source File

SOURCE=.\MSTBRequestBrokerApp.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkedTVBroker.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemTaskExecutor.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BrokerServiceObject.h
# End Source File
# Begin Source File

SOURCE=.\DesktopBroker.h
# End Source File
# Begin Source File

SOURCE=.\DVBBroker.h
# End Source File
# Begin Source File

SOURCE=.\DVBCommunicatorClient.h
# End Source File
# Begin Source File

SOURCE=.\HotelPortalBroker.h
# End Source File
# Begin Source File

SOURCE=.\MSTBConfiguration.h
# End Source File
# Begin Source File

SOURCE=.\MSTBFunctionSwitcher.h
# End Source File
# Begin Source File

SOURCE=.\MSTBRequestBrokerApp.h
# End Source File
# Begin Source File

SOURCE=.\MSTBSubBroker.h
# End Source File
# Begin Source File

SOURCE=.\NetworkedTVBroker.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemTaskExecutor.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
