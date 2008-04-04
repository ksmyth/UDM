#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT([udm], [3.01])
AC_CONFIG_AUX_DIR([config])
# judm paths are longer than 99 characters, so force pax format
AM_INIT_AUTOMAKE([tar-pax])
AC_CONFIG_SRCDIR([src/UdmBase/UdmBase.cpp])
AC_CONFIG_SUBDIRS([src/UdmOclPat/GOCL])
AC_LANG([C++])
AC_DISABLE_STATIC

# Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_PROG_AWK

AC_ARG_WITH(swig,
	AC_HELP_STRING([--with-swig=PATH],
			[Name of swig version 1.3.24 or later [[default=swig]]]),
	[swig_name="$withval"],
	[swig_name="swig"])
AC_CHECK_PROG(swig, $swig_name, $swig_name)
if test x$swig = x; then
   AC_MSG_ERROR([$swig_name not found])
fi
AC_MSG_CHECKING([if $swig_name is version 1.3.24 or later])
if $swig -version 2>&1 | awk 'BEGIN { nok = 1 } /^SWIG Version / { split($3, ver, /\./); split("1.3.24", min_ver, /\./); for (i in ver) { if (min_ver[i] > ver[i]) { exit } }; nok = 0 } END { exit nok }'; then
   AC_MSG_RESULT([yes])
else
   AC_MSG_RESULT([no])
   AC_MSG_ERROR([swig version 1.3.24 or later is needed])
fi

# XXX share this with gocl configure.ac
AC_ARG_WITH(antlr,
	AC_HELP_STRING([--with-antlr=PATH],
			[Name of antlr (version 1.33) from PCCTS [[default=antlr]]]),
	[antlr_name="$withval"],
	[antlr_name="antlr"])
AC_CHECK_PROG(antlr, $antlr_name, $antlr_name)
if test x$antlr = x; then
   AC_MSG_ERROR([$antlr_name not found])
fi
AC_MSG_CHECKING([if $antlr_name is version 1.33])
if $antlr 2>&1 | $EGREP -iq 'Antlr parser generator   Version 1.33'; then
   AC_MSG_RESULT([yes])
else
   AC_MSG_RESULT([no])
   AC_MSG_ERROR([antlr version 1.33 is needed])
fi

# Checks for libraries.
CPPUNITLIBS="-lcppunit -ldl"
MINIZIPLIBS="-lz -lminizip"
XALANLIBS="-lxalan-c"
XERCESLIBS="-lxerces-c"

# Checks for header files.
CPPUNITINC=""
MINIZIPINC=""
XALANINC=""
XERCESINC=""

AC_CHECK_HEADER([boost/concept_check.hpp], [],
	[AC_MSG_ERROR([boost/concept_check.hpp header is needed; please install Boost])])
AC_CHECK_HEADER([boost/format.hpp], [],
	[AC_MSG_ERROR([boost/format.hpp header is needed; please install Boost])])

AC_CHECK_HEADER([loki/Typelist.h], [],
	[AC_MSG_ERROR([loki/Typelist.h header is needed; please install Loki])])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.

UDM_INCDIR="\$(includedir)/udm"
UDM_INC="-I\$(UDM_INCDIR)"
UDM_LIBS="-ludm"
UDM_DTD_PATH="\$(datadir)/udm/etc"
UDM_SAMPLES_PATH="\$(datadir)/udm/samples"
AC_SUBST([UDM_INCDIR])
AC_SUBST([UDM_INC])
AC_SUBST([UDM_LIBS])
AC_SUBST([UDM_DTD_PATH])
AC_SUBST([UDM_SAMPLES_PATH])

AC_SUBST([antlr])
AC_SUBST([swig])
AC_SUBST([CPPUNITLIBS])
AC_SUBST([MINIZIPLIBS])
AC_SUBST([XALANLIBS])
AC_SUBST([XERCESLIBS])
AC_SUBST([CPPUNITINC])
AC_SUBST([MINIZIPINC])
AC_SUBST([XALANINC])
AC_SUBST([XERCESINC])

AC_CONFIG_FILES([Makefile
	bin/Makefile
	etc/Makefile
	doc/Makefile
	include/Makefile
	judm/Makefile
	judm/doc/Makefile
	judm/etc/Makefile
	judm/samples/Makefile
	judm/src/Makefile
	lib/Makefile
	rpm/Makefile
	rpm/udm.spec
	src/Makefile
	src/Udm/Makefile
	src/Udm/File2Code/Makefile
	src/Udm/JavaAPIGen/Makefile
	src/UdmBase/Makefile
	src/UdmBackendDump/Makefile
	src/UdmCopy/Makefile
	src/UdmDom/Makefile
	src/UdmOcl/Makefile
	src/UdmOclPat/Makefile
	src/UdmPOI/Makefile
	src/UdmSwig/Makefile
	src/UdmToXmi/Makefile
	src/UdmUtil/Makefile
	src/UdmViz/Makefile
	src/UdmXmi/Makefile
	src/Uml/Makefile
	src/XmiToUdm/Makefile
	samples/Makefile
	samples/CreateLampModel/Makefile
	samples/CreateLampModel/Makefile.sample
	samples/cross_links/Makefile
	samples/cross_links/Makefile.sample
	tests/Makefile
	tests/test_childrenorder/Makefile
	tests/test_cintstring/Makefile
	tests/test_crosslinks/Makefile
	tests/test_domstringdn/Makefile
	tests/test_generic/Makefile
	tests/test_generic2/Makefile
	tests/testGetAdjacentObjects/Makefile
	tests/test_ns/Makefile
	tests/testOCL/Makefile
	tests/test_simpleudmops/Makefile
	tests/testUdmCint/Makefile
])
AC_OUTPUT
