include $(top_srcdir)/ldms/rules.mk



AM_CPPFLAGS = @OVIS_INCLUDE_ABS@
AM_LDFLAGS = @OVIS_LIB_ABS@
COMMON_LIBADD = $(top_builddir)/ldms/src/sampler/libsampler_base.la \
		$(top_builddir)/ldms/src/core/libldms.la \
		@LDFLAGS_GETTIME@ \
		$(top_builddir)/lib/src/ovis_util/libovis_util.la \
		$(top_builddir)/lib/src/coll/libcoll.la

#	$(top_builddir)/lib/src/ovis_json/libovis_json.la \
#	$(top_builddir)/lib/src/ovis_log/libovis_log.la \
#	-lm -lpthread



libhweventpapi_la_SOURCES = hweventpapi.c
libhweventpapi_la_CFLAGS = $(AM_CFLAGS)
libhweventpapi_la_LDFLAGS = $(AM_LDFLAGS)
libhweventpapi_la_LIBADD = $(COMMON_LIBADD) $(JOBID_LIBFLAGS) $(LTLIBPAPI) $(LTLIBPFM) -lm
pkglib_LTLIBRARIES = libhweventpapi.la

dist_man7_MANS = ldms-sampler_hweventpapi.man

CLEANFILES = $(dist_man7_MANS)

EXTRA_DIST=ldms-sampler_hweventpapi.rst
