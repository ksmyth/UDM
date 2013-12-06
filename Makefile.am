## Makefile.am -- Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = foreign
SUBDIRS = . doc etc include src lib bin samples tests judm rpm

EXTRA_DIST	= CHANGELOG.txt license.txt Linux_build.txt \
	model-files.zip readme.txt releaseinfo.txt \
	samples/CL_udm.udm samples/cross_links/CL_udm.udm \
	samples/LampDiagram_udm.xml samples/cross_links/CL_export.xml \
	tests/test_ns/CL_udm.udm tests/test_crosslinks/CL_udm.udm \
	tests/testGetAdjacentObjects/testAssociationScenarios_udm.udm \
	tests/test_ns/test_ns_udm.xml tests/test_refports/RefPort_udm.xml \
	tests/testUdmCint/GeneTF_udm.xml tests/testUdmCint/SBML2Ex_udm.xml \
	tests/testOCL/SBML2_udm.xml

all-local: model-files.zip
	unzip -x -o $(srcdir)/model-files.zip

rpms: all
	$(MAKE) rpms -C rpm
