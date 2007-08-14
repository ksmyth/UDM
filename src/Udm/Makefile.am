## Makefile.am -- Process this file with automake to produce Makefile.in

SUBDIRS	= File2Code JavaAPIGen

AM_CPPFLAGS		= -I$(top_srcdir)/include -I$(top_srcdir)/src $(MINIZIPINC)

noinst_LTLIBRARIES	= libudm.la
libudm_la_SOURCES	= UdmCorbaCppH.cpp Udm.cpp UdmCpp.cpp UdmCppH.cpp \
			  Udm.h UdmH.cpp UdmMetaCpp.cpp UdmUtil.cpp
# UdmCS.cpp
libudm_la_LIBADD	= File2Code/libudm_file2code.la \
			  JavaAPIGen/libudm_javaapigen.la
