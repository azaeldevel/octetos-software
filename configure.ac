dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(octetos-software, 0.3.0-alpha)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CXX




dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
IT_PROG_INTLTOOL([0.35.0])

GETTEXT_PACKAGE=octetos-software
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT



dnl ***************************************************************************
dnl Check for Windows
dnl ***************************************************************************
AC_CANONICAL_HOST

case $host_os in
  *mingw*)
    platform_win32=yes
    native_win32=yes
    ;;
  pw32* | *cygwin*)
    platform_win32=yes
    native_win32=no
    ;;
  *)
    platform_win32=no
    native_win32=no
    ;;
esac
AM_CONDITIONAL(PLATFORM_WIN32, test x"$platform_win32" = "xyes")
AM_CONDITIONAL(NATIVE_WIN32, test x"$native_win32" = "xyes")


LT_INIT([win32-dll])

CFLAGS_backup="${CFLAGS}"
CPPFLAGS_backup="${CPPFLAGS}"
LDFLAGS_backup="${LDFLAGS}"
CFLAGS="-I/usr/locla/include/ ${CFLAGS}"
CPPFLAGS="-I/usr/locla/include/ ${CPPFLAGS}"
LDFLAGS="-L/usr/locla/lib/ ${LDFLAGS}"
#AC_LANG([C++])
#AC_CHECK_HEADERS([octetos/core/common.hh])
#AC_CHECK_LIB([liboctetos-core-cc.la],[octetos::core::getPackageInfo])
#AC_SEARCH_LIBS([octetos::core::getPackageInfo], [octetos-core-cc], [], [AC_MSG_ERROR([unable to find library octetos-core-cc])])
#PKG_CHECK_MODULES([OCTETOS_CORE_CC], [octetos-core-cc])
#AM_CONDITIONAL([OCTETOS_CORE_CC],  [test "$have_liboctetos_core_cc" = "yes"])


AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
])
