# Microsoft Developer Studio Project File - Name="Convert" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Convert - Win32 Debug
!MESSAGE Dies ist kein g�ltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und f�hren Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Convert.mak".
!MESSAGE 
!MESSAGE Sie k�nnen beim Ausf�hren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Convert.mak" CFG="Convert - Win32 Debug"
!MESSAGE 
!MESSAGE F�r die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Convert - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "Convert - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Convert - Win32 Release"

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
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(SHACIRADIR)\Src" /I "$(SHACIRADIR)\Src\Include" /I "$(SHACIRADIR)\Extern\STL\stlport" /I "$(SHACIRADIR)\Extern\STL\stlport\old_hp" /I "$(SHACIRADIR)\Extern\ECL\Src" /I "$(SHACIRADIR)\Src\Orb" /I "$(SHACIRADIR)\Extern\STYX\Src\INC" /I "$(SHACIRADIR)\Extern\STYX\Src\LIBBASE" /I "$(SHACIRADIR)\Extern\STYX\Src\MODSTD" /I "./" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__WIN32__" /D "__x86__" /D "_OCS_TRACE" /D "__NT__" /D __OSVERSION__=4 /D "__USE_REC__" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 addidata.lib omnithread2_rt.lib omniORB304_rt.lib omniDynamic304_rt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /map /machine:I386 /libpath:"$(SHACIRADIR)\Extern\STL\lib" /libpath:"$(SHACIRADIR)\Extern\ADDIDATA\lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Convert - Win32 Debug"

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
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "$(SHACIRADIR)\Src" /I "$(SHACIRADIR)\Src\Include" /I "$(SHACIRADIR)\Extern\STL\stlport" /I "$(SHACIRADIR)\Extern\STL\stlport\old_hp" /I "$(SHACIRADIR)\Extern\ECL\Src" /I "$(SHACIRADIR)\Src\Orb" /I "$(SHACIRADIR)\Extern\STYX\Src\INC" /I "$(SHACIRADIR)\Extern\STYX\Src\LIBBASE" /I "$(SHACIRADIR)\Extern\STYX\Src\MODSTD" /I "./" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__WIN32__" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 addidata.lib omnithread2_rtd.lib omniORB304_rtd.lib omniDynamic304_rtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /out:"Debug/Convertd.exe" /pdbtype:sept /libpath:"$(SHACIRADIR)\Extern\STL\lib" /libpath:"$(SHACIRADIR)\Extern\ADDIDATA\lib"
# SUBTRACT LINK32 /profile /pdb:none /force

!ENDIF 

# Begin Target

# Name "Convert - Win32 Release"
# Name "Convert - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Convert.cpp

!IF  "$(CFG)" == "Convert - Win32 Release"

!ELSEIF  "$(CFG)" == "Convert - Win32 Debug"

# ADD CPP /I "IQT" /I "IQT\iqtheaders"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\IQT\iqtreg.c

!IF  "$(CFG)" == "Convert - Win32 Release"

!ELSEIF  "$(CFG)" == "Convert - Win32 Debug"

# ADD CPP /I "IQT" /I "IQT\iqtheaders"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\IQT\iscosbit.c

!IF  "$(CFG)" == "Convert - Win32 Release"

!ELSEIF  "$(CFG)" == "Convert - Win32 Debug"

# ADD CPP /I "IQT" /I "IQT\iqtheaders"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\IQT\iscosreg.c

!IF  "$(CFG)" == "Convert - Win32 Release"

!ELSEIF  "$(CFG)" == "Convert - Win32 Debug"

# ADD CPP /I "IQT" /I "IQT\iqtheaders"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
