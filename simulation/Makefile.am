ACLOCAL_AMFLAGS = -I m4

INCLUDES = -Iinclude -Iimpl -Imoc -I. 


paprika_SOURCES=\
src/simul/element.cpp \
src/simul/objet.cpp \
src/simul/main.cpp \
src/simul/main_window.cpp \
src/simul/GraphWindows.cpp \
src/simul/XMLReader.cpp \
src/simul/TableGraphics.cpp \
src/simul/table.cpp \
src/simul/Graph.cpp \
src/simul/robot.cpp \
src/asservissement.cpp \
src/command.cpp \
src/Position.cpp \
src/PositionPlusAngle.cpp \
src/distance.cpp \
src/Angle.cpp \
src/strategie.cpp \
src/pid_filter_angle.cpp \
src/pid_filter_distance.cpp \
src/CommandAvancerToutDroit.cpp \
src/CommandTourner.cpp \
src/CommandGoTo.cpp \  
src/action.cpp \
src/actionSuivreChemin.cpp \
src/actionChercherPiece.cpp \
src/Sensors.cpp \
src/Sensor.cpp \
src/AnalogSensor.cpp \
src/SharpSensor.cpp \
src/ListeDActions.cpp \
src/LimitSwitchSensor.cpp \
src/LigthBarrierSensor.cpp \
src/UltrasoundSensor.cpp \
src/Bras.cpp

paprika_INCLS=\
include/simul/main.h \
include/simul/main_window.h \
include/simul/XMLReader.h \
include/simul/TableGraphics.h \
include/simul/table.h \
include/simul/robot.h \
include/simul/pion.h

bin_PROGRAMS = paprika

paprika_LDADD=$(LIBS)

.PHONY:  cbp

moc/%.moc: include/simul/%.h
	moc $< -o $@


moc/%.moc: include/%.h
	moc $< -o $@

cbp:
	
	sed -e  "s@\#Debug Compiler.*\(<.*\)AUTOOPTIONS\(.*\)@\1$(DEBUG_CXXFLAGS)\2@" \
	    -e  "s@\#Debug Linker.*\(<.*\)AUTOOPTIONS\(.*\)@\1$(DEBUG_LDFLAGS)\2@" \
	    -e  "s@\#Release Compiler.*\(<.*\)AUTOOPTIONS\(.*\)@\1$(RELEASE_CXXFLAGS)\2@" \
	    -e  "s@\#Release Linker.*\(<.*\)AUTOOPTIONS\(.*\)@\1$(RELEASE_LDFLAGS)\2@" \
	    -e  "s@\#Compiler.*\(<.*\)AUTOOPTIONS\(.*\)@\1$(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)\2@" \
	    -e  "s@\#Linker.*\(<.*\)AUTOOPTIONS\(.*\)@\1$(AM_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) $(LIBS)\2@" \
	    -n -e  "1,/<\/ExtraCommands>/ p" \
		paprika.cbp.in > paprika.cbp
	echo "$(paprika_SOURCES) $(paprika_INCLS)" | awk '{for(i=1; i <= NF; i++) print "\t\t\t<Unit filename=\"" $$i "\"/>"}' - >> paprika.cbp
	sed -n -e "/<Extensions>/,$$ p" paprika.cbp.in >> paprika.cbp
