CONFIG      += designer plugin debug_and_release
TARGET      = $$qtLibraryTarget($$TARGET)
TEMPLATE    = lib
QTDIR_build:DESTDIR     = $$QT_BUILD_TREE/plugins/designer

INCLUDEPATH += ../../CameraAPI

win32:LIBS += ../../Release/CameraAPI.lib

HEADERS     = CameraWidget.h \
              CameraWidgetPlugin.h 
SOURCES     = CameraWidget.cpp \
              CameraWidgetPlugin.cpp

# install
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target
