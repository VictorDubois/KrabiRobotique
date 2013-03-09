
TEMPLATE = app
CONFIG += qt debug
QT += core gui

INCLUDEPATH += ../../include/simul ../../include ../../../stm32/Libraries/CMSIS/Core/CM3 ../../../stm32/Libraries/STM32F10x_StdPeriph_Driver/inc /usr/local/include/Box2D

LIBS += -L/usr/local/lib/ -lBox2D


HEADERS += \
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
    ../../include/commandGoTo.h \
    ../../include/odometrie.h \
    ../../include/position.h \
    ../../include/sensors.h \
    ../../include/positionPlusAngle.h \
    ../../include/asservissement.h \
    ../../include/strategie.h \
    ../../include/command.h \
    ../../include/ultrasoundSensor.h \
    ../../include/sharpSensor.h \
    ../../include/sensor.h \
    ../../include/limitSwitchSensor.h \
    ../../include/ligthBarrierSensor.h \
    ../../include/analogSensor.h \
    ../../include/pidFilterDistance.h \
    ../../include/pidFilterAngle.h \
    ../../include/listeActions.h \
    ../../include/angle.h \
    ../../include/distance.h \
    ../../include/action.h \
    ../../include/actionSuivreChemin.h \
    ../../include/bras.h \
    ../../include/simul/bougie.h

SOURCES += \
    ../../src/simul/main.cpp \
    ../../src/simul/main_window.cpp \
    ../../src/simul/XMLReader.cpp \
    ../../src/simul/TableGraphics.cpp \
    ../../src/simul/table.cpp \
    ../../src/simul/robot.cpp \
    ../../src/simul/objet.cpp \
    ../../src/simul/GraphWindows.cpp \
    ../../src/simul/Graph.cpp \
    ../../src/simul/element.cpp \
    ../../src/commandGoTo.cpp \
    ../../src/position.cpp \
    ../../src/sensors.cpp \
    ../../src/positionPlusAngle.cpp \
    ../../src/asservissement.cpp \
    ../../src/strategie.cpp \
    ../../src/command.cpp \
    ../../src/ultrasoundSensor.cpp \
    ../../src/sharpSensor.cpp \
    ../../src/sensor.cpp \
    ../../src/limitSwitchSensor.cpp \
    ../../src/ligthBarrierSensor.cpp \
    ../../src/analogSensor.cpp \
    ../../src/pidFilterDistance.cpp \
    ../../src/pidFilterAngle.cpp \
    ../../src/listeActions.cpp \
    ../../src/angle.cpp \
    ../../src/distance.cpp \
    ../../src/action.cpp \
    ../../src/actionSuivreChemin.cpp \
    ../../src/bras.cpp \
    ../../src/simul/bougie.cpp
