#include(ax_gxx_version.m4)

AC_PREREQ(2.59)
AC_INIT(paprika, 0.1, gregoire.dlg@free.fr)
AC_CONFIG_SRCDIR(src)
AC_CONFIG_HEADER(config.h)

AM_INIT_AUTOMAKE(paprika, 0.1)

CFLAGS="-g"

AC_PROG_CC
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_INSTALL

PKG_CHECK_MODULES(QT, QtCore QtGui QtOpenGL Qt3Support)


AC_MSG_CHECKING(for Boost >= 1.40)
AX_BOOST_BASE([1.40], [AC_MSG_RESULT(yes) ] , [AC_MSG_RESULT(no) ] )


CXXFLAGS=

AX_DEP_CHECK(Box2D, [/usr/lib /usr/local/lib], libBox2D.so,[/usr/include /usr/local/include],Box2D/Box2D.h, -lBox2D)

AC_ARG_ENABLE([debug], AS_HELP_STRING([--enable-debug],[Turn on debugging]), [enable_debug=$enableval],[enable_debug="no"])
AC_MSG_CHECKING(debug)
AC_MSG_RESULT($enable_debug)
if test "x$enable_debug" = "xyes"; then
	CXXFLAGS="$CXXFLAGS -g3 -ggdb -Wall -DDEBUG"
fi

CXXFLAGS="$CXXFLAGS   $AM_CXXFLAGS $QT_CFLAGS $BOOST_CFLAGS $Box2D_CFLAGS"
LDFLAGS="$LDFLAGS $AM_LDFLAGS $QT_LIBS $BOOST_LDFLAGS $Box2D_LIBS"
AC_SUBST([CFLAGS])

AC_HEADER_STDC
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

sed -i 's/\(.*\).o:/\1.o: moc\/\1.moc/' Makefile
mkdir -p moc
