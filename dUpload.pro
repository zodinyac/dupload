TEMPLATE = app
TARGET = dUpload
DESTDIR = ./
QT += network
CONFIG += release uic resources
DEFINES += QT_NETWORK_LIB
INCLUDEPATH += .
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles

include(dUpload.pri)

win32:RC_FILE = dUpload.rc

macx:LIBS += -framework carbon
macx:ICON = dUpload.icns
macx:CONFIG += x86
macx:QMAKE_INFO_PLIST = Info.plist
