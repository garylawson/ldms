include $(top_srcdir)/ldms/rules.mk

sbin_PROGRAMS =
pkglib_LTLIBRARIES =
dist_man8_MANS =

AM_LDFLAGS = @OVIS_LIB_ABS@
AM_CPPFLAGS = @OVIS_INCLUDE_ABS@

COMMON_LD_ADD = ../../core/libldms.la \
		../libldmsd_request.la \
		../libldmsd_stream.la \
		$(top_builddir)/lib/src/ovis_json/libovis_json.la \
		$(top_builddir)/lib/src/coll/libcoll.la \
		$(top_builddir)/lib/src/ovis_util/libovis_util.la

sbin_PROGRAMS += ldms_msg_publish
ldms_msg_publish_SOURCES = ldms_msg_publish.c
ldms_msg_publish_LDADD = $(COMMON_LD_ADD)

sbin_PROGRAMS += ldms_msg_subscribe
ldms_msg_subscribe_SOURCES = ldms_msg_subscribe.c
ldms_msg_subscribe_LDADD = $(COMMON_LD_ADD)

sbin_PROGRAMS += ldmsd_stream_publish
ldmsd_stream_publish_SOURCES = ldmsd_stream_publish.c
ldmsd_stream_publish_LDADD = $(COMMON_LD_ADD)

sbin_PROGRAMS += ldmsd_stream_subscribe
ldmsd_stream_subscribe_SOURCES = ldmsd_stream_subscribe.c
ldmsd_stream_subscribe_LDADD = $(COMMON_LD_ADD)
ldmsd_stream_subscribe_LDFLAGS = $(AM_LDFLAGS) -pthread

dist_man8_MANS += ldmsd_stream_subscribe.man \
		  ldmsd_stream_publish.man

CLEANFILES = $(dist_man8_MANS)

EXTRA_DIST=ldmsd_stream_publish.rst ldmsd_stream_subscribe.rst
