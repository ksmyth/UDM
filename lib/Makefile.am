## Makefile.am -- Process this file with automake to produce Makefile.in

if ! NO_XALAN
XALANLIBS += ../src/UdmXmi/libudmxmi.la
endif

if ! NO_ANTLR
XALANLIBS += ../src/UdmOcl/libudmocl.la \
	../src/UdmOclPat/GOCL/src/libgocl.la
endif

lib_LTLIBRARIES		= libudm.la libUdmSwig.la

libudm_la_SOURCES	=
libudm_la_LIBADD	= \
	../src/Uml/libuml.la \
	../src/UdmPOI/libudmpoi.la \
	../src/UdmBase/libudmbase.la \
	../src/UdmUtil/libudmutil.la \
	../src/UdmDom/libudmdom.la \
	$(XERCESLIBS) $(XALANLIBS) $(MINIZIPLIBS) $(DLOPENLIBS)
libudm_la_LDFLAGS	= -version-info 3:1:3
# Force C++ linking
nodist_EXTRA_libudm_la_SOURCES	= dummy.cxx

libUdmSwig_la_SOURCES	=
libUdmSwig_la_LIBADD	= ../src/UdmSwig/libudmswig.la libudm.la
libUdmSwig_la_LDFLAGS	= -version-info 3:1:3
# Force C++ linking
nodist_EXTRA_libUdmSwig_la_SOURCES	= dummy.cxx
