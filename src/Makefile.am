
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = version testing-v0

version_SOURCES = \
	version.cc \
	software.cc \
	db.cc

version_LDFLAGS =

version_CPPFLAGS = -DENABLED_AUTOTOOLS 

version_LDADD = /usr/local/lib/liboctetos-core-cc.so /usr/lib/libsqlite.so -lsqlite3


testing_v0_SOURCES = \
	testing-v0.cc \
	db.cc


testing_v0_LDFLAGS =

testing_v0_CPPFLAGS = -DENABLED_AUTOTOOLS 

testing_v0_LDADD = /usr/local/lib/liboctetos-core-cc.so /usr/lib/libsqlite.so -lsqlite3


if NATIVE_WIN32
	version_LDFLAGS += -mwindows
endif
