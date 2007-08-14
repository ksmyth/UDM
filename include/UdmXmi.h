
#ifndef MOBIES_UDM_XMI_H
#define MOBIEX_UDM_XMI_H


#ifdef WIN32
#ifdef UDMXMI_EXPORTS
#define UDMXMI_API __declspec(dllexport)
#else
#define UDMXMI_API __declspec(dllimport)
#endif
#endif





void initXSLTstr();
int do_xslt_trans(const char * file_in, const char * file_out, const char * file_xsl);

int XmiToUdm(const char * in, const char * out);
int UdmToXmi(const char * in, const char * out);


#endif
