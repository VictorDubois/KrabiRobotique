
TEMPLATE = app
#add 'qwt' to the CONFIG for ploting
CONFIG += qt debug
QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += bluetooth
    CONFIG += qwt
    DEFINES += BLUETOOTH QT5 USE_PLOT
}

INCLUDEPATH += ../../include ../../../stm32/Libraries/CMSIS/Core/CM3 ../../../stm32/Libraries/STM32F10x_StdPeriph_Driver/inc /usr/local/include/Box2D
INCLUDEPATH += ../../include/simul ../../include/strategie ../../include/asservissement ../../include/actionneurs ../../include/hardware

LIBS += -L/usr/local/lib/ -lBox2D

DEFINES += NO_REMOTE
DEFINES += "KRABI"
#DEFINES += "KRABI_JR"

HEADERS += \
    ../../include/positionPlusAngle.h \
    ../../include/position.h \
    ../../include/distance.h \
    ../../include/constantes.h \
    ../../include/angle.h \
    ../../include/actionneurs/servo.h \
    ../../include/actionneurs/sensors.h \
    ../../include/actionneurs/sensor.h \
    ../../include/actionneurs/roues.h \
    ../../include/actionneurs/moteur.h \
    ../../include/actionneurs/ascenseur.h \
    ../../include/asservissement/pidFilterDistance.h \
    ../../include/asservissement/pidFilterAngle.h \
        ../../include/asservissement/odometrie.h \
        ../../include/asservissement/commandAllerA.h \
    ../../include/asservissement/command.h \
        ../../include/asservissement/asservissement.h \
    ../../include/simul/XMLReader.h \
    ../../include/simul/TableGraphics.h \
    ../../include/simul/table.h \
    ../../include/simul/robot.h \
    ../../include/simul/objet.h \
    ../../include/simul/main_window.h \
    ../../include/simul/main.h \
    ../../include/simul/GraphWindows.h \
    ../../include/simul/Graph.h \
    ../../include/simul/element.h \
    ../../include/simul/bougie.h \
    ../../include/hardware/ultrasoundSensor.h \
    ../../include/hardware/sharpSensor.h \
    ../../include/hardware/roue.h \
    ../../include/hardware/quadratureCoderHandler.h \
    ../../include/hardware/pwmHandler.h \
    ../../include/hardware/limitSwitchSensor.h \
    ../../include/hardware/ligthBarrierSensor.h \
    ../../include/hardware/ax12api.h \
        ../../include/hardware/leds.h \
    ../../include/hardware/analogSensor.h \
    ../../include/strategie/strategieV2.h \
    ../../include/strategie/recalibrerOdometrie.h \
        ../../include/strategie/mediumLevelAction.h \
        ../../include/strategie/actionGoTo.h \
    ../../include/simul/userdata.h \
    ../../include/simul/contactlistener.h \
    ../../include/strategie/strategiev3.h \
    ../../include/strategie/etape.h \
    ../../include/strategie/dijkstra.h \
    ../../include/hardware/tourelle.h \
    ../../include/strategie/krabi2014.h \
    ../../src/strategie/clap.h \
    ../../include/strategie/krabi2015.h \
    ../../include/strategie/clap.h \
    ../../include/strategie/gobelet.h \
    ../../include/strategie/krabijunior2015.h \
    ../../include/strategie/tapis.h \
    ../../include/actionneurs/brasTapis.h \
    ../../include/actionneurs/brasKrabi.h \
    ../../include/actionneurs/brasLateraux.h \
    ../../include/strategie/deposerGobelet.h \
    ../../include/actionneurs/pinces.h \
    ../../include/strategie/ramasserPied.h \
    ../../include/hardware/microSwitch.h \
    ../../include/simul/debugwindow.h \
    ../../include/asservissement/commandTournerVers.h \
    ../../include/asservissement/commandAllerEnArcA.h \
    ../../include/simul/remotedebug.h \
    ../../include/simul/bluetoothwindow.h \
    ../../include/simul/bluetoothinterface.h \
    ../../include/hardware/krabipacket.h \
    ../../include/simul/odometriewindow.h \
    ../../include/simul/asservwindow.h \
    ../../include/simul/sharpwindow.h \
    ../../include/simul/watchwindow.h \
    ../../include/strategie/deposerPied.h


SOURCES += \
    ../../src/asservissement/pidFilterDistance.cpp \
        ../../src/asservissement/pidFilterAngle.cpp \
        ../../src/asservissement/commandAllerA.cpp \
    ../../src/asservissement/command.cpp \
        ../../src/asservissement/asservissement.cpp \
    ../../src/actionneurs/servo.cpp \
    ../../src/actionneurs/sensors.cpp \
    ../../src/actionneurs/sensor.cpp \
    ../../src/position.cpp \
    ../../src/distance.cpp \
    ../../src/angle.cpp \
        ../../src/positionPlusAngle.cpp \
    ../../src/simul/XMLReader.cpp \
    ../../src/simul/TableGraphics.cpp \
    ../../src/simul/table.cpp \
    ../../src/simul/robot.cpp \
    ../../src/simul/objet.cpp \
    ../../src/simul/main_window.cpp \
    ../../src/simul/main.cpp \
    ../../src/simul/GraphWindows.cpp \
    ../../src/simul/Graph.cpp \
    ../../src/simul/element.cpp \
    ../../src/simul/bougie.cpp \
    ../../src/hardware/ultrasoundSensor.cpp \
    ../../src/hardware/sharpSensor.cpp \
    ../../src/hardware/limitSwitchSensor.cpp \
    ../../src/hardware/ligthBarrierSensor.cpp \
    ../../src/hardware/ax12api.cpp \
        ../../src/hardware/leds.cpp \
    ../../src/hardware/analogSensor.cpp \
    ../../src/strategie/strategieV2.cpp \
    ../../src/strategie/recalibrerOdometrie.cpp \
    ../../src/strategie/mediumLevelAction.cpp \
        ../../src/strategie/actionGoTo.cpp \
    ../../src/simul/userdata.cpp \
    ../../src/simul/contactlistener.cpp \
    ../../src/strategie/strategiev3.cpp \
    ../../src/strategie/etape.cpp \
    ../../src/strategie/dijkstra.cpp \
    ../../src/hardware/tourelle.cpp \
    ../../src/strategie/krabi2015.cpp \
    ../../src/strategie/clap.cpp \
    ../../src/strategie/gobelet.cpp \
    ../../src/strategie/krabijunior2015.cpp \
    ../../src/strategie/tapis.cpp \
    ../../src/actionneurs/brasTapis.cpp \
    ../../src/actionneurs/brasLateraux.cpp \
    ../../src/actionneurs/brasKrabi.cpp \
    ../../src/actionneurs/ascenseur.cpp \
    ../../src/strategie/deposerGobelet.cpp \
    ../../src/actionneurs/pinces.cpp \
    ../../src/strategie/ramasserPied.cpp \
    ../../src/simul/debugwindow.cpp \
    ../../src/hardware/microSwitch.cpp \
    ../../src/asservissement/commandTournerVers.cpp \
    ../../src/asservissement/commandAllerEnArcA.cpp \
    ../../src/asservissement/odometrie.cpp \
    ../../src/simul/remotedebug.cpp \
    ../../src/simul/bluetoothwindow.cpp \
    ../../src/simul/bluetoothinterface.cpp \
    ../../src/hardware/krabipacket.cpp \
    ../../src/simul/odometriewindow.cpp \
    ../../src/simul/asservwindow.cpp \
    ../../src/simul/sharpwindow.cpp \
    ../../src/simul/watchwindow.cpp \
    ../../src/strategie/deposerPied.cpp

FORMS += \
    ../../include/simul/remotedebug.ui \
    ../../include/simul/debugwindow.ui \
    ../../include/simul/bluetoothwindow.ui \
    ../../include/simul/bluetoothinterface.ui \
    ../../include/simul/odometriewindow.ui \
    ../../include/simul/asservwindow.ui \
    ../../include/simul/sharpwindow.ui \
    ../../include/simul/watchwindow.ui

