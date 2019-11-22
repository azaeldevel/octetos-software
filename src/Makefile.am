
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = version

version_SOURCES = \
	version.cc \
	software.cc

version_LDFLAGS =

version_CPPFLAGS = -DENABLED_AUTOTOOLS 

version_LDADD = /usr/local/lib/liboctetos-core-cc.so


if NATIVE_WIN32
	version_LDFLAGS += -mwindows
endif
