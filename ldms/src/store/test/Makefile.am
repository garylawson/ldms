include $(top_srcdir)/ldms/rules.mk



AM_CFLAGS = \
$(BOOST_CPPFLAGS)
dist_man8_MANS =

if ENABLE_CSV_CHECK
dist_man8_MANS += ldms-csv-time-drops.man
bin_PROGRAMS = ldms_csv_time_drops_range ldms_csv_time_drops

ldms_csv_time_drops_SOURCES = csv_time_drops.cxx
ldms_csv_time_drops_LDADD = -lboost_system
ldms_csv_time_drops_LDFLAGS = $(AM_LDFLAGS) -L$(BOOST_ROOT)/lib
ldms_csv_time_drops_CPPFLAGS = $(AM_CFLAGS)

ldms_csv_time_drops_range_SOURCES = csv_time_drops.cxx
ldms_csv_time_drops_range_LDADD = -lboost_system
ldms_csv_time_drops_range_LDFLAGS = $(AM_LDFLAGS) -L$(BOOST_ROOT)/lib
ldms_csv_time_drops_range_CPPFLAGS = $(AM_CFLAGS) -DPRINT_RANGE
endif

CLEANFILES = $(dist_man8_MANS)

EXTRA_DIST=ldms-csv-time-drops.rst
