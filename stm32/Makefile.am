
INCLUDES = -Iinclude -I. -ILibraries/CMSIS/Core/CM3 -ILibraries/STM32F10x_StdPeriph_Driver/inc

main_SOURCES=\
Libraries/CMSIS/Core/CM3/startup/gcc/startup_stm32f10x_md.s \
Libraries/STM32F10x_StdPeriph_Driver/src/misc.c \
Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c \
Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c \
Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c \
Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c \
Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c \
src/Angle.cpp \
src/Hctl_Handler.cpp \
src/Moteur.cpp \
src/Position.cpp \
src/PositionPlusAngle.cpp \
src/Rouleau.cpp \
src/ValeursRoues.cpp \
src/asservissement.cpp \
src/capteurs.cpp \
src/command.cpp \
src/distance.cpp \
src/main.cpp \
src/memory.cpp \
src/odometrie.cpp \
src/pid_filter_angle.cpp \
src/pid_filter_distance.cpp \
src/pwm_handler.cpp \
src/quadrature_coder_handler.cpp \
src/rateau.cpp \
src/roue.cpp \
src/roues.cpp \
src/servo.cpp \
src/strategie.cpp \
src/stub.c

main_INCLS=\
include/Angle.h \
include/Hctl_Handler.h \
include/Moteur.h \
include/Position.h \
include/PositionPlusAngle.h \
include/Rouleau.h \
include/ValeursRoues.h \
include/asservissement.h \
include/capteurs.h \
include/distance.h \
include/memory.h \
include/odometrie.h \
include/pid_filter_angle.h \
include/pid_filter_distance.h \
include/pwm_handler.h \
include/quadrature_coder_handler.h \
include/rateau.h \
include/roue.h \
include/roues.h \
include/servo.h \
include/strategie.h \
include/timer_handler.h 

bin_PROGRAMS = main

LIBS=$(AM_LDFLAGS)

all-local: main.out
	$(OBJCOPY) -Obinary main.out main.bin
	$(OBJDUMP) -S main.out > main.list


.PHONY:  cbp

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
