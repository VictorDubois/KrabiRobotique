
AC_DEFUN([AX_DEP_CHECK],
[

libluabindpath="/usr/lib /usr/local/lib"
libluabindname=libluabind.so
libluabindheader="/usr/include /usr/local/include"

AC_MSG_CHECKING(for $1 libs)

for l in $2; do
	for lib in $3; do
		if test -f $l/$lib; then
			AC_MSG_RESULT($l/$lib)
			$1_LIBS="-L$l $(echo $lib | sed -e 's/^lib/-l/' -e 's/\.so$//')"
			break
		fi
	done
done

if test -z "${$1_LIBS}"; then
	AC_MSG_RESULT(not found)
	exit 1
fi

AC_MSG_CHECKING(for $1 headers)

for l in $4; do
	if test -f $l/$5; then
		AC_MSG_RESULT($l)
		$1_CFLAGS="-I$l"
		break
	fi
done

if test -z "${$1_CFLAGS}"; then
	AC_MSG_RESULT(not found)
	exit 1
fi

AC_SUBST($1_CFLAGS)
AC_SUBST($1_LIBS)

])
