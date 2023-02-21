CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(qlockbuttonplugin)
TEMPLATE    = lib

HEADERS     = qlockbuttonplugin.h
SOURCES     = qlockbuttonplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer gui multimedia svg
} else {
    CONFIG += designer gui multimedia svg
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(qlockbutton/qlockbutton.pri)
