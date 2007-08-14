/*
Copyright (c) Vanderbilt University, 2000-2001
ALL RIGHTS RESERVED
Vanderbilt University disclaims all warranties with regard to this
software, including all implied warranties of merchantability
and fitness.  In no event shall Vanderbilt University be liable for
any special, indirect or consequential damages or any damages
whatsoever resulting from loss of use, data or profits, whether
in an action of contract, negligence or other tortious action,
arising out of or in connection with the use or performance of
this software.
*/

/*
	11/22/04	-	endre

			-	Extended ExtractName with the name of the "name attribute", by default : 'name'
	
	23/07/04	-	endre
			
			-		Changed the usage of reqcopyLinks. The function has to be called twice, with the
					first with simpleLinks = true, then with simpleLinks = false, in order to copy 
					both types of links

*/

#ifndef MOBIES_UDMUTIL_H
#define MOBIES_UDMUTIL_H


namespace UdmUtil
{
	typedef map<Udm::Object, Udm::Object> copy_assoc_map;
	//utility which copies a subtree from a data network to another
	//consistent (same) meta is assumed.
	//direct parameter will be passed thru setAssociation
	
	UDM_DLL int reqCopyLinks(Udm::ObjectImpl* p_srcRoot,Udm::ObjectImpl* p_dstRoot, copy_assoc_map& cam, const bool direct = true,const bool simpleLinks = true);	
	UDM_DLL int CopyObjectHierarchy(Udm::ObjectImpl* p_srcRoot, Udm::ObjectImpl* p_dstRoot, Udm::DataNetwork* p_dstBackend, copy_assoc_map &cam);
	
	//this utility tries to extract the name-like attribute
	//using stupid heuristics and assuming odd things like
	//the name of the name attribute is "name". Anyway, it might be useful.
	UDM_DLL string ExtractName(Udm::Object ob, const string att_name = "name");
};

#endif //MOBIES_UDMUTIL_H

