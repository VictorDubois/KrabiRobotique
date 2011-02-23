# Code imported from Newlib
#
# FIXME: We temporarily define our own version of AC_PROG_CC.  This is
# copied from autoconf 2.12, but does not call AC_PROG_CC_WORKS.  We
# are probably using a cross compiler, which will not be able to fully
# link an executable.  This should really be fixed in autoconf
# itself.

AC_DEFUN([LIB_AC_PROG_CC_GNU],
[AC_CACHE_CHECK(whether we are using GNU C, ac_cv_prog_gcc,
[dnl The semicolon is to pacify NeXT's syntax-checking cpp.
cat > conftest.c <<EOF
#ifdef __GNUC__
  yes;
#endif
EOF
if AC_TRY_COMMAND(${CC-cc} -E conftest.c) | egrep yes >/dev/null 2>&1; then
  ac_cv_prog_gcc=yes
else
  ac_cv_prog_gcc=no
fi])])

AC_DEFUN([LIB_AM_PROG_AS],
[# By default we simply use the C compiler to build assembly code.
AC_REQUIRE([LIB_AC_PROG_CC])
test "${CCAS+set}" = set || CCAS=$CC
test "${CCASFLAGS+set}" = set || CCASFLAGS=$CFLAGS
AC_ARG_VAR([CCAS],      [assembler compiler command (defaults to CC)])
AC_ARG_VAR([CCASFLAGS], [assembler compiler flags (defaults to CFLAGS)])
])

AC_DEFUN([LIB_AC_PROG_CC],
[AC_BEFORE([$0], [AC_PROG_CPP])dnl
AC_CHECK_PROG(CC, gcc, gcc)
_AM_DEPENDENCIES(CC)
if test -z "$CC"; then
  AC_CHECK_PROG(CC, cc, cc, , , /usr/ucb/cc)
  test -z "$CC" && AC_MSG_ERROR([no acceptable cc found in \$PATH])
fi

LIB_AC_PROG_CC_GNU

if test $ac_cv_prog_gcc = yes; then
  GCC=yes
dnl Check whether -g works, even if CFLAGS is set, in case the package
dnl plays around with CFLAGS (such as to build both debugging and
dnl normal versions of a library), tasteless as that idea is.
  ac_test_CFLAGS="${CFLAGS+set}"
  ac_save_CFLAGS="$CFLAGS"
  CFLAGS=
  _AC_PROG_CC_G
  if test "$ac_test_CFLAGS" = set; then
    CFLAGS="$ac_save_CFLAGS"
  elif test $ac_cv_prog_cc_g = yes; then
    CFLAGS="-g -O2"
  else
    CFLAGS="-O2"
  fi
else
  GCC=
  test "${CFLAGS+set}" = set || CFLAGS="-g"
fi
])

m4_rename([AC_PROG_CXX],[old_AC_PROG_CXX])
AN_MAKEVAR([CXX],  [AC_PROG_CXX])
AN_PROGRAM([CC],   [AC_PROG_CXX])
AN_PROGRAM([c++],  [AC_PROG_CXX])
AN_PROGRAM([g++],  [AC_PROG_CXX])
AC_DEFUN([AC_PROG_CXX],
[AC_LANG_PUSH(C++)dnl
AC_ARG_VAR([CXX],      [C++ compiler command])dnl
AC_ARG_VAR([CXXFLAGS], [C++ compiler flags])dnl
_AC_ARG_VAR_LDFLAGS()dnl
_AC_ARG_VAR_LIBS()dnl
_AC_ARG_VAR_CPPFLAGS()dnl
_AC_ARG_VAR_PRECIOUS([CCC])dnl
if test -z "$CXX"; then
  if test -n "$CCC"; then
    CXX=$CCC
  else
    AC_CHECK_TOOLS(CXX,
		   [m4_default([$1],
			       [g++ c++ gpp aCC CC cxx cc++ cl.exe FCC KCC RCC xlC_r xlC])],
		   g++)
  fi
fi
# Provide some information about the compiler.
_AS_ECHO_LOG([checking for _AC_LANG compiler version])
set X $ac_compile
ac_compiler=$[2]
for ac_option in --version -v -V -qversion; do
  _AC_DO_LIMIT([$ac_compiler $ac_option >&AS_MESSAGE_LOG_FD])
done

#m4_expand_once([_AC_COMPILER_EXEEXT])[]dnl
m4_expand_once([_AC_COMPILER_OBJEXT])[]dnl
#_AC_LANG_COMPILER_GNU
#if test $ac_compiler_gnu = yes; then
#  GXX=yes
#else
#  GXX=
#fi
#_AC_PROG_CXX_G
AC_LANG_POP(C++)dnl
])# AC_PROG_CXX
