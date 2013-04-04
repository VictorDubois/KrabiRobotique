
TEMPLATE = app
CONFIG += qt debug
QT += core gui

INCLUDEPATH += ../../include ../../../stm32/Libraries/CMSIS/Core/CM3 ../../../stm32/Libraries/STM32F10x_StdPeriph_Driver/inc /usr/local/include/Box2D
INCLUDEPATH += ../../include/simul ../../include/strategie ../../include/asservissement ../../include/actionneurs ../../include/hardware

LIBS += -L/usr/local/lib/ -lBox2D


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
    ../../include/actionneurs/bras.h \
    ../../include/asservissement/pidFilterDistance.h \
    ../../include/asservissement/pidFilterAngle.h \
    ../../include/asservissement/odometrie.h \
    ../../include/asservissement/commandTest.h \
    ../../include/asservissement/commandLookAt.h \
    ../../include/asservissement/commandGoTo.h \
    ../../include/asservissement/command.h \
    ../../include/asservissement/asservissement.h \
    ../../include/strategie/strategie.h \
    ../../include/strategie/singleton.h \
    ../../include/strategie/regarderCouleur.h \
    ../../include/strategie/ramasserVerre.h \
    ../../include/strategie/mediumLevelAction.h \
    ../../include/strategie/lowLevelAction.h \
    ../../include/strategie/lancerAscenseur.h \
    ../../include/strategie/eteindreBougie.h \
    ../../include/strategie/deposerVerres.h \
    ../../include/strategie/actionnerPortes.h \
    ../../include/strategie/actionnerMarteau.h \
    ../../include/strategie/actionnerAscenseur.h \
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
    ../../include/hardware/analogSensor.h


SOURCES += \
    ../../src/strategie/strategie.cpp \
    ../../src/strategie/regarderCouleur.cpp \
    ../../src/strategie/ramasserVerre.cpp \
    ../../src/strategie/mediumLevelAction.cpp \
    ../../src/strategie/lowLevelAction.cpp \
    ../../src/strategie/lancerAscenseur.cpp \
    ../../src/strategie/eteindreBougie.cpp \
    ../../src/strategie/deposerVerres.cpp \
    ../../src/strategie/actionnerPortes.cpp \
    ../../src/strategie/actionnerMarteau.cpp \
    ../../src/strategie/actionnerAscenseur.cpp \
    ../../src/asservissement/pidFilterDistance.cpp \
    ../../src/asservissement/pidFilterAngle.cpp \
    ../../src/asservissement/commandTest.cpp \
    ../../src/asservissement/commandLookAt.cpp \
    ../../src/asservissement/commandGoTo.cpp \
    ../../src/asservissement/command.cpp \
	../../src/asservissement/asservissement.cpp \
    ../../src/actionneurs/servo.cpp \
    ../../src/actionneurs/sensors.cpp \
    ../../src/actionneurs/sensor.cpp \
    ../../src/actionneurs/bras.cpp \
    ../../src/positionPlusAngle.cpp \
    ../../src/position.cpp \
    ../../src/distance.cpp \
    ../../src/angle.cpp \
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
    ../../src/hardware/analogSensor.cpp

