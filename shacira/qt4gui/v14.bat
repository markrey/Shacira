junction -d omniORB
junction omniORB omniORB-4.1.5.vc10
junction -d Shacira
junction Shacira Shacira.trunk

xcopy %QTDIR%\plugins\designer\mosaicwidgets.* %QTDIR%\plugins\designer\v13 /d /Y
xcopy %QTDIR%\plugins\designer\nwidgets.* %QTDIR%\plugins\designer\v13 /d /Y
xcopy %QTDIR%\plugins\designer\pvwidgets.* %QTDIR%\plugins\designer\v13 /d /Y
xcopy %QTDIR%\plugins\designer\pmwidgets.* %QTDIR%\plugins\designer\v13 /d /Y
xcopy %QTDIR%\plugins\designer\lswidgets.* %QTDIR%\plugins\designer\v13 /d /Y
xcopy %QTDIR%\plugins\designer\cwidgets.* %QTDIR%\plugins\designer\v13 /d /Y
xcopy %QTDIR%\plugins\designer\qt_plugin_kbdlayouts.* %QTDIR%\plugins\designer\v13 /d /Y
xcopy %QTDIR%\plugins\designer\qt_plugin_keypads.* %QTDIR%\plugins\designer\v13 /d /Y
xcopy %QTDIR%\plugins\designer\apcwidgets.* %QTDIR%\plugins\designer\v14 /d /Y
xcopy %QTDIR%\plugins\designer\q3_cwidget_plugin.* %QTDIR%\plugins\designer\v14 /d /Y
xcopy %QTDIR%\plugins\designer\q3_kbdlayout_plugin.* %QTDIR%\plugins\designer\v14 /d /Y
xcopy %QTDIR%\plugins\designer\q3_keypad_plugin.* %QTDIR%\plugins\designer\v14 /d /Y

del %QTDIR%\plugins\designer\mosaicwidgets.*
del %QTDIR%\plugins\designer\nwidgets.*
del %QTDIR%\plugins\designer\pvwidgets.*
del %QTDIR%\plugins\designer\pmwidgets.*
del %QTDIR%\plugins\designer\lswidgets.*
del %QTDIR%\plugins\designer\cwidgets.*
del %QTDIR%\plugins\designer\qt_plugin_kbdlayouts.*
del %QTDIR%\plugins\designer\qt_plugin_keypads.*

xcopy %QTDIR%\plugins\designer\v14 %QTDIR%\plugins\designer /d /Y

