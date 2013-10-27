
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
	../../include/actionneurs/marteaux.h \
    ../../include/actionneurs/bras.h \
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
    ../../include/strategie/ramenerVerres.h \
    ../../include/strategie/ramasserVerreV2.h \
    ../../include/strategie/eteindreBougieV2.h \
	../../include/strategie/mediumLevelAction.h \
	../../include/strategie/actionGoTo.h \
	../../include/strategie/ramasserVerres.h \
    ../../include/simul/userdata.h \
    ../../include/simul/contactlistener.h


SOURCES += \
    ../../src/asservissement/pidFilterDistance.cpp \
	../../src/asservissement/pidFilterAngle.cpp \
	../../src/asservissement/commandAllerA.cpp \
    ../../src/asservissement/command.cpp \
	../../src/asservissement/asservissement.cpp \
    ../../src/actionneurs/servo.cpp \
    ../../src/actionneurs/sensors.cpp \
    ../../src/actionneurs/sensor.cpp \
	../../src/actionneurs/bras.cpp \
	../../src/actionneurs/marteaux.cpp \
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
    ../../src/strategie/ramasserVerreV2.cpp \
    ../../src/strategie/mediumLevelAction.cpp \
    ../../src/strategie/eteindreBougieV2.cpp \
	../../src/strategie/actionGoTo.cpp \
	../../src/strategie/eteindreBougies.cpp \
	../../src/strategie/ramasserVerres.cpp \
    ../../src/simul/userdata.cpp \
    ../../src/simul/contactlistener.cpp

