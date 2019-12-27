AUTOMAKE_OPTIONS=foreign 1.4

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(OCTETOS_CORE_CFLAGS) \
	$(SQLITE3_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

#lib_LTLIBRARIES = liboctetos-software.la


bin_PROGRAMS = version testing-v0


#liboctetos_software_la_SOURCES = \
#	lib.c
#liboctetos_software_la_LDFLAGS = 
#liboctetos_software_la_LIBADD = $(OCTETOS_SOFTWARE_LIBS)
#if PLATFORM_WIN32
#liboctetos_software_la_LDFLAGS += -no-undefined
#endif
#if NATIVE_WIN32
#liboctetos_software_la_LDFLAGS += -export-dynamic
#endif



version_LDFLAGS =$(OCTETOS_CORE_CFLAGS) $(SQLITE3_CFLAGS)
version_CFLAGS = $(OCTETOS_CORE_CFLAGS) $(SQLITE3_CFLAGS)
version_CPPFLAGS = $(OCTETOS_CORE_CFLAGS) $(SQLITE3_CFLAGS)
version_LDADD = $(OCTETOS_CORE_LIBS) $(SQLITE3_LIBS)
version_SOURCES = \
	version.cc \
	software.cc \
	db.cc


testing_v0_LDFLAGS = $(OCTETOS_CORE_CFLAGS) $(SQLITE3_CFLAGS)
testing_v0_CFLAGS = $(OCTETOS_CORE_CFLAGS) $(SQLITE3_CFLAGS)
testing_v0_CPPFLAGS = $(OCTETOS_CORE_CFLAGS) $(SQLITE3_CFLAGS)
testing_v0_LDADD = $(OCTETOS_CORE_LIBS) $(SQLITE3_LIBS)
testing_v0_SOURCES = \
	testing-v0.cc \
	db.cc



#include_HEADERS = \
#	octetos_software.h

#pkgconfigdir = $(libdir)/pkgconfig
#pkgconfig_DATA = octetos_software-0.4.0-alpha.pc

#EXTRA_DIST = \
#	octetos_software-0.4.0-alpha.pc.in
