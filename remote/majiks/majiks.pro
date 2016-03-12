QT       += core gui widgets
QT       += bluetooth serialport


CONFIG += console c++11 warn_on

# Disabled because of an obnoxious bug in GCC (struct A = {0} triggers the warning even though it's legal)
win32-g++:QMAKE_CXXFLAGS += -Wno-missing-field-initializers

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

SOURCES += 	main.cpp \
                magiks.cpp \
                ../../stm32/src/hardware/krabipacket.cpp \
                subwindows/asservwindow.cpp \
                subwindows/watchwindow.cpp \
                subwindows/bluetoothmanagementwidget.cpp \
                subwindows/odometrywindow.cpp \
                subwindows/loggerwidget.cpp  \
                subwindows/plotwidget.cpp \
                subwindows/tablewidget.cpp \
                subwindows/remotewidget.cpp \
                bluetoothproxy/bluetoothproxy.cpp \
                bluetoothproxy/bluetoothproxyqt5.cpp \
                packetprocessor.cpp \
                timemaster.cpp 	\
                bluetoothtestserver.cpp \
    subwindows/movementsettingswidget.cpp \
    serialproxy/abstractserialproxy.cpp \
    serialproxy/serialproxy.cpp \
    subwindows/serialmanagementwidget.cpp \
    subwindows/serialportmanagementwidget.cpp

    

HEADERS  += magiks.h  \
            ../../stm32/include/hardware/krabipacket.h \
            bluetoothproxy/bluetoothproxy.h \
            bluetoothproxy/bluetoothproxyqt5.h 	\
            subwindows/asservwindow.h \
            subwindows/watchwindow.h \
            subwindows/odometrywindow.h \
            subwindows/bluetoothmanagementwidget.h 	\
            subwindows/loggerwidget.h \
            subwindows/tablewidget.h \
            subwindows/plotwidget.h \
            subwindows/remotewidget.h \
            packetprocessor.h \
            timemaster.h \
            bluetoothtestserver.h \
    subwindows/movementsettingswidget.h \
    serialproxy/abstractserialproxy.h \
    serialproxy/serialproxy.h \
    subwindows/serialmanagementwidget.h \
    subwindows/serialportmanagementwidget.h



FORMS += \
    subwindows/asservwindow.ui 		\
    subwindows/debugwindow.ui 		\
    subwindows/odometrywindow.ui 	\
    subwindows/watchwindow.ui


