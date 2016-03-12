TARGET = majiks
TEMPLATE = app

QT       += core gui widgets
QT       += bluetooth

CONFIG += console c++11 warn_on

# By default, QtSerialPort is not compiled with Qt for Android.
# Since direct serial communications are only usefull for desktops anyway, it's easier to disable it entierely.
!android:CONFIG += serial

# Disabled because of an obnoxious bug in GCC (struct A = {0} triggers the warning even though it's legal)
win32-g++:QMAKE_CXXFLAGS += -Wno-missing-field-initializers

# The config when serial coms are enabled
serial {
    QT += serialport
    DEFINES += SERIAL_ENABLED

    SOURCES +=  serialproxy/serialproxy.cpp \
                subwindows/serialportmanagementwidget.cpp
    HEADERS +=  serialproxy/serialproxy.h \
                subwindows/serialportmanagementwidget.h
}

# Check if QWT_ROOT is defined as an environment variable
_QWT_ROOT = $$(QWT_ROOT)
isEmpty(_QWT_ROOT) {
    error("Please set QWT_ROOT as an environment variable.")
}
# NB: you HAVE to set QWT_ROOT as an env variable yourself
# (it points to the folder where you compiled Qwt)
# We are not using the 'module' install because it is broken on several platforms
# qwt.prf should setup everything nicely...
include ( $(QWT_ROOT)/features/qwt.prf )
LIBS += -lqwt

# Qwt is VERY finicky when it comes to Android...
# There has to be a better way to include Qt5PrintSupport.so and Qt5OpenGL.so by default directly from Qt, but I couldn't find it.
android:ANDROID_EXTRA_LIBS += $$(QWT_ROOT)/lib/libqwt.so $$(QWT_ROOT)/lib/libQt5PrintSupport.so $$(QWT_ROOT)/lib/libQt5OpenGL.so
# qwt.prf is broken for Android (the config is confused by the X-compil and uses Unix settings instead of the host's...)
android:INCLUDEPATH += $$(QWT_ROOT)/include
android:QMAKE_LIBDIR += $$(QWT_ROOT)/lib

# For KrabiPacket
INCLUDEPATH += ../../stm32/include/hardware
DEFINES += BLUETOOTH

# Winsock config
win32 {
    HEADERS += bluetoothproxy/bluetoothproxywinsock.h
    SOURCES += bluetoothproxy/bluetoothproxywinsock.cpp
    DEFINES += BLUETOOTH_USING_WINSOCK
    LIBS += -lws2_32
}

# Sources files used by every config
# (note: used by both QtCreator for the project view AND by the linker - don't forget to call qmake when changing those)
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
                subwindows/serialmanagementwidget.cpp

    
# Headers files used by every config
# (note: only useful for the project view in QtCreator)
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
            subwindows/serialmanagementwidget.h



FORMS += \
    subwindows/asservwindow.ui 		\
    subwindows/odometrywindow.ui 	\
    subwindows/watchwindow.ui


