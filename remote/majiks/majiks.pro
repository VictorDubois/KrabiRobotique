QT       += core gui widgets
QT       += bluetooth


CONFIG += console c++11

TARGET = majiks
TEMPLATE = app

#NB: you HAVE to set QWT_ROOT as an env variable yourself
# (it points to the folder where you compiled Qwt)
include ( $(QWT_ROOT)/features/qwt.prf )
LIBS += -lqwt

#Qwt is VERY finicky when it comes to Android...
android:ANDROID_EXTRA_LIBS += $$(QWT_ROOT)/lib/libqwt.so $$(QWT_ROOT)/lib/libQt5PrintSupport.so $$(QWT_ROOT)/lib/libQt5OpenGL.so
android:INCLUDEPATH += $$(QWT_ROOT)/include
android:QMAKE_LIBDIR += $$(QWT_ROOT)/lib


INCLUDEPATH += ../../stm32/include/hardware


win32:HEADERS += bluetoothproxy/bluetoothproxywinsock.h
win32:SOURCES += bluetoothproxy/bluetoothproxywinsock.cpp
win32:DEFINES += BLUETOOTH_USING_WINSOCK
win32:LIBS += -lws2_32

DEFINES += BLUETOOTH

SOURCES += main.cpp\
        magiks.cpp \
    ../../stm32/src/hardware/krabipacket.cpp \
    subwindows/asservwindow.cpp \
    subwindows/odometriewindow.cpp \
    subwindows/watchwindow.cpp \
    bluetoothproxy/bluetoothproxy.cpp \
    bluetoothproxy/bluetoothproxyqt5.cpp \
    subwindows/graph.cpp \
    packetprocessor.cpp \
    subwindows/graphwindow.cpp \
    subwindows/bluetoothmanagementwidget.cpp \
    subwindows/loggerwidget.cpp \
    subwindows/plotwidget.cpp \
    timemaster.cpp \
    bluetoothtestserver.cpp

HEADERS  += magiks.h \
    ../../stm32/include/hardware/krabipacket.h \
    bluetoothproxy/bluetoothproxy.h \
    bluetoothproxy/bluetoothproxyqt5.h \
    subwindows/asservwindow.h \
    subwindows/graph.h \
    subwindows/odometriewindow.h \
    subwindows/watchwindow.h \
    packetprocessor.h \
    subwindows/graphwindow.h \
    subwindows/bluetoothmanagementwidget.h \
    subwindows/loggerwidget.h \
    subwindows/plotwidget.h \
    timemaster.h \
    bluetoothtestserver.h

FORMS += \
    subwindows/asservwindow.ui \
    subwindows/debugwindow.ui \
    subwindows/odometriewindow.ui \
    subwindows/watchwindow.ui


