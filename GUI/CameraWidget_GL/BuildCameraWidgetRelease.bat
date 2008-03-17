cd %1
%QTDIR%\bin\qmake.exe CameraWidgetPlugin.pro
nmake /D /f Makefile.Release install
echo Done compiling Camera Widget