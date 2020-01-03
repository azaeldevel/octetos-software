dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(octetos_software, 0.5.0-alpha)
AC_CANONICAL_SYSTEM
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE
AM_SILENT_RULES([yes])

AM_PROG_AS
AC_LANG_CPLUSPLUS
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL



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

PKG_CHECK_MODULES(SQLITE3, [sqlite3])
PKG_CHECK_MODULES(CUNIT, [cunit])
PKG_CHECK_MODULES([OCTETOS_CORE], [octetos-core])



AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in])
