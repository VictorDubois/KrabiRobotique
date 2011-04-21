# Note: plugindir is set in configure

plugin_LTLIBRARIES = libcolorseg.la

# sources used to compile this plug-in
libcolorseg_la_SOURCES = gstcolorseg.c gstcolorseg.h colorseg.c colorseg.h threshold.h

# compiler and linker flags used to compile this plugin, set in configure.ac
libcolorseg_la_CFLAGS = $(GST_CFLAGS)
libcolorseg_la_LIBADD = $(GST_LIBS)
libcolorseg_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libcolorseg_la_LIBTOOLFLAGS = --tag=disable-static


# headers we need but don't want installed
#noinst_HEADERS = gstplugin.h
