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


	//note: escape_char is not escaped unless it is contained in to_escape_chars
	UDM_DLL string escape_chars(const string &src, const char escape_char, const string &to_escape_chars);

	//convert array of strings to string and back; used by backends that store array attributes as strings
	UDM_DLL string vector_to_string(const vector<string> &v, const char separator, bool add_sep_at_end = false, bool unquote_strings = false);
	UDM_DLL vector<string> string_to_vector(const string &src, const char separator);

	UDM_DLL string replace_delimiter(const string &s, const string &old_d, const string &new_d);

	// Converts a double value to a string, using the least necessary
	// precision to represent the original double value.
	UDM_DLL string doubleToString(double val, int minimum_precision = 2);
};

#endif //MOBIES_UDMUTIL_H

