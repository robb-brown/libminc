INCLUDES = -I$(top_srcdir)/libsrc \
	-I$(top_srcdir)/volume_io/Include \
	-I$(top_builddir)/volume_io/Include

script_tests = \
	run_test_arg_parse.sh \
	run_tests.sh \
	run_test2.sh \
	xfmconcat_01.sh \
	xfmconcat_02.sh \
	run_test_progs.sh

all-local:
	cd $(srcdir) && chmod +x $(script_tests)

LDADD = ../libvolume_io2.la ../libminc2.la
TESTS = run_test_arg_parse.sh \
	run_tests.sh \
	run_test2.sh \
	xfmconcat_01.sh \
	xfmconcat_02.sh \
	mincapi \
	run_test_progs.sh

check_PROGRAMS = minc test_mconv minc_types icv icv_range \
	icv_dim test_speed icv_dim1 icv_fillvalue \
	test_xfm create_grid_xfm mincapi test_speed test_arg_parse

EXTRA_DIST = $(script_tests) $(expect_files) t1.xfm icv.mnc

CLEANFILES = test.mnc _*

# The test script "run_tests.sh" uses a series of "expected output"
# files, comparing each with the output generated by the file under
# test.  We need to distribute these files (so they are in
# EXTRA_DIST).
#
expect_files = icv.out icv_dim.out icv_dim1.out icv_fillvalue.out	\
	icv_range.out minc_types.out

# Unfortunately, GNU make has implicit rules for files with the suffix
# ".out".  The following lines disable implicit rules.  In future, we
# should probably use a different naming scheme for these files ...
# 
icv.out: ;
icv_dim.out: ;
icv_dim1.out: ;
icv_fillvalue.out: ;
icv_range.out: ;
minc_types.out: ;

if MINC2
	
INCLUDES += -I$(top_srcdir)/libsrc2

minc2_script_tests = \
	minc2-testminctools.sh

minc2-all-local: # CHECK!
	cd $(srcdir) && chmod +x $(script_tests)


LDADD += ../../libminc2.la

AM_CFLAGS = -DAPPARENTORDER

MINC2_TESTS =	\
	minc2-create-test-images \
	minc2-create-test-images-2 \
	minc2-datatype-test \
	minc2-dimension-test \
	minc2-full-test \
	minc2-grpattr-test \
	minc2-hyper-test \
        minc2-hyper-test-2 \
	minc2-label-test \
	minc2-record-test \
	minc2-slice-test \
	minc2-valid-test \
	minc2-volprops-test \
	minc2-multires-test \
	minc2-convert-test \
	minc2-vector_dimension-test 

TESTS += \
	$(MINC2_TESTS) \
	$(minc2_script_tests)

EXTRA_DIST += $(minc2_script_tests)

check_PROGRAMS += $(ALL_TESTS)

CLEANFILES += *.mnc

endif # MINC2
