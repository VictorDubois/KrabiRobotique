#include(ax_gxx_version.m4)

AC_PREREQ(2.59)
AC_INIT(paprika, 0.1, gregoire.dlg@free.fr)

AC_CONFIG_SRCDIR(src)
AC_CONFIG_HEADER(config.h)

AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(paprika, 0.1)


CFLAGS="-g"

dnl AC_PROG_CC
dnl AM_PROG_AS
dnl AC_PROG_CXX
dnl AC_PROG_CPP
dnl AC_PROG_INSTALL

CC=$target-gcc
CXX=$target-g++

LIB_AC_PROG_CC
AS=${AS-as}
AC_SUBST(AS)
LIB_AM_PROG_AS
AC_PROG_CXX

CXXFLAGS=
CFLAGS="-mcpu=cortex-m3 -mthumb -fno-common -O0 -DSTM32F10X_MD -DROUES -DROBOTHW"
CCASFLAGS="-mcpu=cortex-m3 -mthumb -fno-common -O0"

AC_ARG_ENABLE([debug], AS_HELP_STRING([--enable-debug],[Turn on debugging]), [enable_debug=$enableval],[enable_debug="no"])
AC_MSG_CHECKING(debug)
AC_MSG_RESULT($enable_debug)
if test "x$enable_debug" = "xyes"; then
	CXXFLAGS="$CXXFLAGS -g3 -ggdb -Wall -Wextra"
else
    CXXFLAGS="-Os"
fi

CXXFLAGS="$CXXFLAGS $CFLAGS "
LDFLAGS="$LDFLAGS -nostartfiles -Tstm32LinkerScript.cmd"
AC_SUBST([CFLAGS])

OBJCOPY=$target-objcopy
AC_SUBST([OBJCOPY])
OBJDUMP=$target-objdump
AC_SUBST([OBJDUMP])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

