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
CHANGELOG
	12/08/04	-	endre

		Small bugfix: CopyAttributes fucntion could not handle "Text" Attributes.

	12/06/04	-	endre

		New function 
			set<Object> DataNetwork::GetAllInstancesOf(const ::Uml::Uml::Class& meta)
		added, which retrives all instances of an Class in a DataNetwork


	11/22/04	-	endre

		VC7++ .NET porting issues

	10/24/04	-	endre

		slight modification because of introducing a new type "Text", which is the
		same as "String", but it gets persisted differently in DOM backend.
	  
	09/03/04	-	endre
				
		fixed small bug in getIntegerAttrArr function
		which converted the last item in the array to long instead of __int64

	04/26/04	-	endre
		
		changed the DataNetwork assignment operator to first remove 
		existing objects in destination datanetwork

	02/10/04	-	endre
	
		added the generic container() function to class Udm::Object

	01/26/04	-	endre
		
		  Mainly porting issues to g++ 2.96, specially the compress/decompress stuff.
			void type had to be add to all the functions declared with no return type
  
	06/19/02	-	endre

			Added array attribute setter/getter implementations,
	  which basically are wrapper functions which use
	  get/set StringAttr.

		Array representation:
		integer, real :	values delimited by ';'
		bool:			sequence of 'true' or 'false', delimited by ';', case insensitive
		
		string:			strings are delimited by ';'. 
						';'s in strings are escaped with '\'
						'\'s in strings are escaped with '\'
	  

		DOM:	works OK
		MGA:	works OK, but since MGA lacks support
				for attribute arrays, these array 
				attributes must be declared in MGA
				paradigm as string attributes
		MEM:	it would work OK, but in MEM
				back-end these functions are overriden,
				so they are more performant.
				MEM backend provides real support for 
				attribute arrays

		This approach has no problems with 
	  DOM backend, it also works with MGA backend, but in 
	  the MGA paradigm the attribute must be declared as a 
	  string attribute. It would also work for MEM backend,
	  but in MEM backend 

*/

#include "UdmBase.h"
#include "UmlExt.h"
#include <UdmUtil.h>
#include <string>

#ifndef _WIN32
long long _atoi64(const char *x)  { long long i; sscanf(x,"%lld",&i);return i;};
#endif



//unix - windows portability issues
//1. stricmp, strnicmp on WIN32 are strcasecmp, strncasecmp on UNIX

#ifndef WIN32
#define stricmp(a, b) strcasecmp(a,b)
#define strnicmp(a, b, n) strncasecmp(a,b,n)
#endif

namespace Udm
{

	const ::Uml::Uml::CompositionChildRole NULLCHILDROLE;
	const ::Uml::Uml::CompositionParentRole NULLPARENTROLE;

	
	UDM_DLL ObjectImpl *Object::__Cast(const Object &a, const ::Uml::Uml::Class &meta)
	{
		if(a && !Uml::IsDerivedFrom(a.type(), meta) )
			throw udm_exception("Invalid cast");

		return a.impl->clone();
	}

	UDM_DLL ObjectImpl *Object::__Create(const ::Uml::Uml::Class &meta, const Object &parent, 
		const ::Uml::Uml::CompositionChildRole &role, const ObjectImpl * archetype, const bool subtype )
	{
		if (archetype && archetype != &_null)
		{
			if (archetype->type() != meta )
				throw udm_exception("Type of archetype and type must be the same!");
			
			return parent.impl->createChild(role, meta, archetype, subtype) ;
		}
		else
		return parent.impl->createChild(role, meta);
	}

	UDM_DLL Object Object::archetype() const
	{
		return impl->getArchetype();
	};

	UDM_DLL set<Object> Object::derived() const
	{
		set<Object> ret;
		vector<ObjectImpl*> der_vect = impl->getDerived();
		vector<ObjectImpl*>::iterator dv_i  = der_vect.begin();
		while (dv_i != der_vect.end())
			ret.insert(*dv_i++);
		return ret;
	};

	UDM_DLL set<Object> Object::instances() const
	{
		set<Object> ret;
		vector<ObjectImpl*> der_vect = impl->getInstances();
		vector<ObjectImpl*>::iterator dv_i  = der_vect.begin();
		while (dv_i != der_vect.end())
			ret.insert(*dv_i++);
		return ret;
	};

	UDM_DLL bool Object::hasRealArchetype() const
	{
		return impl->hasRealArchetype();
	};
	UDM_DLL bool Object::isInstance() const
	{
		return impl->isInstance();
	};
	UDM_DLL bool Object::isSubtype() const
	{
		return impl->isSubtype();
	};
	
	UDM_DLL Object Object::container() const
	{
		return impl->getParent(NULL);
	};


	udm_exception NullObject::e("Object handle is null");

	UDM_DLL bool IsDerivedFrom(const ::Uml::Uml::Class &derived, const ::Uml::Uml::Class &base) {
		return Uml::IsDerivedFrom(derived, base);
	}

	UDM_DLL NullObject _null;
	UDM_DLL Object null(&_null);

	//static member var initialization
	unsigned long DataNetwork::dn_id_gen = 0;
	map <const unsigned long, DataNetwork *> DataNetwork::dntab;

	UDM_DLL DataNetwork::DataNetwork(const Udm::UdmDiagram &metainfo, UdmProject* project) : metaroot(metainfo), pr(project) 
	{ 
		metainfo.init();
		dn_id = dn_id_gen++;
		pair <const unsigned long, DataNetwork *> ins_item(dn_id, this);
		pair <map <const unsigned long, DataNetwork *>::iterator, bool> ins_res = dntab.insert(ins_item);
		if (!ins_res.second)
			throw udm_exception("Can not register data network!");

		_static_pr = false;//it is either not part of a project or part of a non-static project

	}

	UDM_DLL DataNetwork *DataNetwork::GetDnById(const unsigned long id)
	{
		map <const unsigned long, DataNetwork *>::iterator dntab_i = dntab.find(id);
		if (dntab_i != dntab.end()) return dntab_i->second;
		return NULL;

	}

	UDM_DLL DataNetwork & DataNetwork::operator=(DataNetwork &a)
	{
		UdmUtil::copy_assoc_map dummy;
		vector<ObjectImpl*> vec = rootobject.__impl()->getChildren(NULL, NULL);
		for (vector<ObjectImpl*>::iterator vec_i = vec.begin(); vec_i != vec.end(); vec_i++)
		{
			(*vec_i)->detach();		//detach the object
			(*vec_i)->release();	//getChildren() cloned() them 
		};

		UdmUtil::CopyObjectHierarchy(a.GetRootObject().__impl(), rootobject.__impl(), this, dummy);
		return *this;
	}

	UDM_DLL void DataNetwork::setStaticUdmProject(StaticUdmProject* _pr)
	{
		pr = _pr; 
		_static_pr = true;
	};

	
	/*
		Returns all instances of a certain class in a Data Network
	*/
	UDM_DLL set<Object> DataNetwork::GetAllInstancesOf(const ::Uml::Uml::Class& meta)
	{
		set<Object> ret;
		const ::Uml::Uml::Class root_meta = rootobject.type();
		vector<Uml::ChildRoleChain> chains;
		Uml::GetChildRoleChain(root_meta, meta, chains);
		while (chains.size())
		{
			Uml::ChildRoleChain chain = *(chains.rbegin());

			chains.pop_back();

			set<Object> ret_set = rootobject.getChildrenByChildRoleChain(meta, chain);
			if (ret_set.size()) ret.insert(ret_set.begin(), ret_set.end());
		};
		return ret;
	};

	//	--- attribute setters/getters for multiple value (array) type attributes

	/*
		
		Basic idea behind array'ing with DOM & MGA: 
		===========================================
		getters: get the attribute as a single value string;
				 then tokenize by ';', and try to parse back
				 return elements in a vector(order kept)

		setters: compose a string from the input vector,
				 by enumeration, delimit them with character ';' 
				 set the attribute to DOM as a single value string attribute

		MGA note:
				MGA paradigm version must declare the array attributes
				as string attributes for this to work
	*/


	UDM_DLL vector<string> ObjectImpl::getStringAttrArr(const ::Uml::Uml::Attribute &meta) const
	{
		/*
		Special characters:

			; - array field delimiter, unless escaped
			\ - escape character, unless escaped 
		*/
		vector<string> ret;
	
		//we rely on this function
		string sc_delimited = getStringAttr(meta);
		if (!sc_delimited.size()) return ret;

		char * sc_delimited_c_str = new char[sc_delimited.size()+1];
		strcpy(sc_delimited_c_str, sc_delimited.c_str());

		bool escape_in = false;
		char * scd_i = sc_delimited_c_str;

		char * array_val = scd_i;
		
		while (*scd_i != '\0')
		{
			switch (*scd_i)
			{
			case ';':
				if(!escape_in)
				{
					//a not-escaped ';' was received => end of an array token
					//put the value in the vector and go on
					char * t = scd_i;					//save the pointer
					*scd_i='\0';						//end the string
					ret.push_back(string(array_val));	//push the string in vector
					scd_i = array_val = ++t;			//restore the pointer &
														//set array_val to the beginning of
														//of the next string, if any
				}
				else
				{
					escape_in = false;					//escape has effect only for the next character
					scd_i++;
				}
				break;
			case '\\':
				if (!escape_in)
				{
					//it was an escape character, which must not be present in the value
					//we need to take it out from the string
					const char * t_src = scd_i;					//initialize the overwrinting copy
					char * t_dst = scd_i;

					t_src++;									//skip the escape character
					do
					{
						*t_dst++ = *t_src++;
					}while(*t_src!='\0');						//overcopy itself, skipping the first character
					*t_dst = '\0';								//needs ending, it will be 1 character less
					escape_in = true;
				}
				else
				{
					//this is a "\\" sequence, when the intent is to have a '\' in the 
					//value, so we just go on, and we set back the escape_in to false
					escape_in = false;
					scd_i++;
				}
				break;
			default:
				if (escape_in)
					throw udm_exception(string("Unknown escape sequence in: ") + sc_delimited);
				scd_i++;								//go on the length of the string 

			}//eo switch (*scd_i)

		}//eo while *scd_i != '\0'
		if (array_val != scd_i)
			ret.push_back(string(array_val));			//last string in array
		delete sc_delimited_c_str;						//clean up the buffer 
		return ret;										//return the vector
	};

	UDM_DLL void ObjectImpl::setStringAttrArr(const ::Uml::Uml::Attribute &meta, const vector<string> &a, const bool direct)
	{
		/*
		Special characters:
			- ';' -s and '\'-s which really occur in strings in a are escaped with '\'
			- fields are delimited with ';'
		*/

		vector<string>::const_iterator a_ci = a.begin();
		string encoded_attr;

		while (a_ci != a.end())
		{
			const string a_item = *a_ci;
			string::const_iterator a_item_ci = a_item.begin();
			while (a_item_ci != a_item.end())
			{

				switch (*a_item_ci)
				{
				case ';':
					encoded_attr.append("\\");		//escape the semicolon(;)
					break;
				case '\\':
					encoded_attr.append("\\");		//escape the escape(\)
					break;
				}
				
				const char a[] = {*a_item_ci, '\0'};
				encoded_attr.append(a);//append the character	
				a_item_ci++;
			};  //for each character in the string
			encoded_attr.append(";");				//append the delimiter character
			a_ci++;
		};	//for each string in the vector

		//use setStringAttr w/ the constructed string
		setStringAttr(meta, encoded_attr, direct);

	};

	UDM_DLL vector<bool> ObjectImpl::getBooleanAttrArr(const ::Uml::Uml::Attribute &meta) const
	{
		vector<bool> ret;
		string sc_delimited = getStringAttr(meta);
		if (!sc_delimited.size()) return ret;


		char * sc_delimited_c_str = new char[sc_delimited.size()+1];
		strcpy(sc_delimited_c_str, sc_delimited.c_str());

		char * scd_i = sc_delimited_c_str;
		char * array_val = scd_i;
		
		while (*scd_i != '\0')
		{
			switch (*scd_i)
			{
			case ';':
				{
					//delimiter character received
					char * t = scd_i;				//save the pointer
					*scd_i='\0';						//end the string
					if (!strnicmp(array_val, "true", 4))
					{
						ret.push_back(true);
						scd_i = array_val = ++t;	
						break;
					}

					if (!strnicmp(array_val, "false", 5))
					{
						ret.push_back(false);
						scd_i = array_val = ++t;	
						break;
					}
					throw udm_exception(string("Parsing of bool-array failed: ") + sc_delimited);
				}
				throw udm_exception(string("Parsing of bool-array failed: ") + sc_delimited);
				break;
			default:
				scd_i++;								//go on the length of the string 

			}//eo switch (*scd_i)

		}//eo while *scd_i != '\0'
		
		if (scd_i != array_val)
		{
			//get the last item in the array
			if (!strnicmp(array_val, "true", 4))
				ret.push_back(true);

			if (!strnicmp(array_val, "false", 5))
				ret.push_back(false);

			if (strnicmp(array_val, "true", 4) && strnicmp(array_val, "false", 5))
				throw udm_exception(string("Parsing of bool-array(last value) failed: ") + sc_delimited);
		}

		delete sc_delimited_c_str;						//clean up the buffer 
		return ret;

	};

	UDM_DLL void ObjectImpl::setBooleanAttrArr(const ::Uml::Uml::Attribute &meta, const vector<bool> &a, const bool direct)
	{
		string encoded_attr;
		vector<bool>::const_iterator a_ci = a.begin();

		while (a_ci != a.end())
		{
			if (encoded_attr.size())
				encoded_attr.append(";");			//delimiter character
			if (*a_ci)
				encoded_attr+="true";				//literal true
			else
				encoded_attr+="false";				//literal false
			a_ci++;									//go on 
		}
		
		setStringAttr(meta, encoded_attr, direct);

	};

	UDM_DLL vector<__int64> ObjectImpl::getIntegerAttrArr(const ::Uml::Uml::Attribute &meta) const
	{
		vector<__int64> ret;
		string sc_delimited = getStringAttr(meta);
		if (!sc_delimited.size()) return ret;


		char * sc_delimited_c_str = new char[sc_delimited.size()+1];
		strcpy(sc_delimited_c_str, sc_delimited.c_str());

		char * scd_i = sc_delimited_c_str;
		char * array_val = scd_i;
		
		while (*scd_i != '\0')
		{
			switch (*scd_i)
			{
			case ';':
				{
					//delimiter character received
					char * t = scd_i;				//save the pointer
					*scd_i='\0';						//end the string
					ret.push_back(_atoi64(array_val));
					scd_i = array_val = ++t;	
					
				}								
				break;
			default:
				scd_i++;								//go on the length of the string 

			}//eo switch (*scd_i)

		}//eo while *scd_i != '\0'
		
		if (array_val != scd_i) ret.push_back(_atoi64(array_val));		//last value in array is not ended with ';'!
		
		delete sc_delimited_c_str;						//clean up the buffer 
		return ret;

	};

	UDM_DLL void ObjectImpl::setIntegerAttrArr(const ::Uml::Uml::Attribute &meta, const vector<__int64> &a, const bool direct)
	{
		string encoded_attr;
		vector<__int64>::const_iterator a_ci = a.begin();
		
		char * lit_integer = new char[20];			//32-bit integers in decimal representation
													//can go up to max 9 characters, +1 (sign)
													//so 20 is safe enough
			
		while (a_ci != a.end())
		{
			if (encoded_attr.size())
				encoded_attr.append(";");			//delimiter character

#ifdef _WIN32
			sprintf(lit_integer, "%I64d", *a_ci);		
#else
			sprintf(lit_integer, "%lld", *a_ci);		
#endif

			encoded_attr.append(lit_integer);
			
			a_ci++;									//go on 
		}
		
		delete lit_integer;

		setStringAttr(meta, encoded_attr, direct);


	};

	UDM_DLL vector<double> ObjectImpl::getRealAttrArr(const ::Uml::Uml::Attribute &meta) const
	{
		vector<double> ret;
		string sc_delimited = getStringAttr(meta);
		if (!sc_delimited.size()) return ret;

		char * sc_delimited_c_str = new char[sc_delimited.size()+1];
		strcpy(sc_delimited_c_str, sc_delimited.c_str());

		char * scd_i = sc_delimited_c_str;
		char * array_val = scd_i;
		double d;
					
		
		while (*scd_i != '\0')
		{
			switch (*scd_i)
			{
			case ';':
				{
					//delimiter character received
					char * t = scd_i;				//save the pointer
					*scd_i='\0';						//end the string
					if(sscanf(array_val, "%lf", &d) != 1) throw udm_exception("Attr is of non-float format");
					ret.push_back(d);
					scd_i = array_val = ++t;	
					
				}								
				break;
			default:
				scd_i++;								//go on the length of the string 

			}//eo switch (*scd_i)

		}//eo while *scd_i != '\0'

		if((array_val != scd_i) && sscanf(array_val, "%lf", &d) != 1) throw udm_exception("Attr is of non-float format");
		ret.push_back(d);								//last value in array is not ended with ';' !
					
		delete sc_delimited_c_str;						//clean up the buffer 
		return ret;

	};

	UDM_DLL void ObjectImpl::setRealAttrArr(const ::Uml::Uml::Attribute &meta, const vector<double> &a, const bool direct)
	{
		string encoded_attr;
		vector<double>::const_iterator a_ci = a.begin();
		
		char * lit_double = new char[(20+15+2)*2];			//first 20:before the decimal point
															//second 15: precission
															//2: decimal point + ending null
															// *2: just to make sure ;-)
			
		while (a_ci != a.end())
		{
			if (encoded_attr.size())
				encoded_attr.append(";");			//delimiter character

			sprintf(lit_double, "%.15lf", *a_ci);		
			encoded_attr.append(lit_double);
			
			a_ci++;									//go on 
		}
		
		delete lit_double;
		//set the attribute as a string attribute
		setStringAttr(meta, encoded_attr, direct);
	};

	
	UDM_DLL tmap &ObjectImpl::locatemap(bool create) const
	{
		static tmap emptymap;
		DataNetwork *dn = const_cast<ObjectImpl*>(this)->__getdn();
		uniqueId_type u = uniqueId();
		ttmap::iterator found = dn->tempvarmap.find(u);
		if(found == dn->tempvarmap.end()) 
		{
			if(create) 
				found = dn->tempvarmap.insert(ttmap::value_type(u,emptymap)).first;
			else 
				return emptymap;
		}
		return found->second;
	}

	//non-persistent , single-value attributes 
///
	UDM_DLL string ObjectImpl::getTempStringAttr(const ::Uml::Uml::Attribute &meta) const 
	{
			tmap &tempvarmap = locatemap(false);
			string ret;
			map<string, udmvariant>::iterator f = tempvarmap.find(string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@string");
			if(f != tempvarmap.end()) ret = f->second.strval;
			return ret;
	}

	UDM_DLL void ObjectImpl::setTempStringAttr(const ::Uml::Uml::Attribute &meta, const string &a, const bool direct) 
	{
			tmap &tempvarmap = locatemap(true);
			string sig = string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@string";
			

			ObjectImpl * archetype = getArchetype();
			if (archetype && (archetype != (ObjectImpl*)&Udm::_null) )
			{
				string desynch_sig = sig + "_is_desycnhed";
				if (direct)
				{
					//set the attribute
					tmap::iterator f = tempvarmap.find(sig);
					if(f != tempvarmap.end()) f->second.strval = a;
					else tempvarmap.insert(tmap::value_type(sig, a)); 

					//desynch from archetype
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if (d != tempvarmap.end()) d->second.boolval = true;
					else tempvarmap.insert(tmap::value_type(desynch_sig, true)); 

				}
				else
				{
					//check if desynched
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if  ( (d == tempvarmap.end()) || !(d->second.boolval))
					{
						//set the attribute
						tmap::iterator f = tempvarmap.find(sig);
						if(f != tempvarmap.end()) f->second.strval = a;
						else tempvarmap.insert(tmap::value_type(sig, a)); 
					}
				}
				archetype->release();
			}
			else
			{
				//set the attrbute
				tmap::iterator f = tempvarmap.find(sig);
				if(f != tempvarmap.end()) f->second.strval = a;
				else tempvarmap.insert(tmap::value_type(sig, a)); 
			}

			//go through all derived and instances
			vector<ObjectImpl*>::iterator i;
			vector<ObjectImpl*> deriveds = getDerived();
			for (i = deriveds.begin(); i != deriveds.end(); i++)
			{
				ObjectImpl* derived = *i;
				derived->setTempStringAttr(meta, a, false);
				derived->release();
			}

			vector<ObjectImpl*> instances = getInstances();
			for (i = instances.begin(); i != instances.end(); i++)
			{
				ObjectImpl* instance = *i;
				instance->setTempStringAttr(meta, a, false);
				instance->release();
			}
	}

///
	UDM_DLL __int64 ObjectImpl::getTempIntegerAttr(const ::Uml::Uml::Attribute &meta) const
	{
			tmap &tempvarmap = locatemap(false);
			__int64 ret=0;
			map<string, udmvariant>::iterator f = tempvarmap.find(string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@long");
			if(f != tempvarmap.end()) ret = f->second.longval;
			return ret;
	}

	UDM_DLL void ObjectImpl::setTempIntegerAttr(const ::Uml::Uml::Attribute &meta, const __int64 &a, const bool direct) 
	{
			tmap &tempvarmap = locatemap(true);
			string sig = string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@long";
			
			ObjectImpl * archetype = getArchetype();
			if (archetype && (archetype != (ObjectImpl*)&Udm::_null) )
			{
				string desynch_sig = sig + "_is_desycnhed";
				if (direct)
				{
					//set the attribute
					tmap::iterator f = tempvarmap.find(sig);
					if(f != tempvarmap.end()) f->second.longval = a;
					else tempvarmap.insert(tmap::value_type(sig, a)); 
			
					//desynch from archetype
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if (d != tempvarmap.end()) d->second.boolval = true;
					else tempvarmap.insert(tmap::value_type(desynch_sig, true)); 

				}
				else
				{
					//check if desynched
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if  ( (d == tempvarmap.end()) || !(d->second.boolval))
					{
						//set the attribute
						tmap::iterator f = tempvarmap.find(sig);
						if(f != tempvarmap.end()) f->second.longval = a;
						else tempvarmap.insert(tmap::value_type(sig, a)); 
						}
				}
				archetype->release();
			}
			else
			{
				//set the attrbute
				tmap::iterator f = tempvarmap.find(sig);
				if(f != tempvarmap.end()) f->second.longval = a;
				else tempvarmap.insert(tmap::value_type(sig, a)); 
			}

			//go through all derived and instances
			vector<ObjectImpl*>::iterator i;
			vector<ObjectImpl*> deriveds = getDerived();
			for (i = deriveds.begin(); i != deriveds.end(); i++)
			{
				ObjectImpl* derived = *i;
				derived->setTempIntegerAttr(meta, a, false);
				derived->release();
			}

			vector<ObjectImpl*> instances = getInstances();
			for (i = instances.begin(); i != instances.end(); i++)
			{
				ObjectImpl* instance = *i;
				instance->setTempIntegerAttr(meta, a, false);
				instance->release();
			}

			/*
			tmap::iterator f = tempvarmap.find(sig);
			if(f != tempvarmap.end()) f->second.longval = a;
			else tempvarmap.insert(tmap::value_type(sig, a)); 
			*/
	}

///
	UDM_DLL double ObjectImpl::getTempRealAttr(const ::Uml::Uml::Attribute &meta) const 
	{
			tmap &tempvarmap = locatemap(false);
			double ret=0;
			map<string, udmvariant>::iterator f = tempvarmap.find(string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@double");
			if(f != tempvarmap.end()) ret = f->second.doubleval;
			return ret;
	}

	UDM_DLL void ObjectImpl::setTempRealAttr(const ::Uml::Uml::Attribute &meta, const double &a, const bool direct) 
	{
			tmap &tempvarmap = locatemap(true);
			string sig = string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@double";



			ObjectImpl * archetype = getArchetype();
			if (archetype && (archetype != (ObjectImpl*)&Udm::_null) )
			{
				string desynch_sig = sig + "_is_desycnhed";
				if (direct)
				{
					//set the attribute
					tmap::iterator f = tempvarmap.find(sig);
					if(f != tempvarmap.end()) f->second.doubleval = a;
					else tempvarmap.insert(tmap::value_type(sig, a)); 
			
					//desynch from archetype
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if (d != tempvarmap.end()) d->second.boolval = true;
					else tempvarmap.insert(tmap::value_type(desynch_sig, true)); 

				}
				else
				{
					//check if desynched
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if  ( (d == tempvarmap.end()) || !(d->second.boolval))
					{
						//set the attribute
						tmap::iterator f = tempvarmap.find(sig);
						if(f != tempvarmap.end()) f->second.doubleval = a;
						else tempvarmap.insert(tmap::value_type(sig, a)); 
						}
				}
				archetype->release();
			}
			else
			{
				//set the attrbute
				tmap::iterator f = tempvarmap.find(sig);
				if(f != tempvarmap.end()) f->second.doubleval = a;
				else tempvarmap.insert(tmap::value_type(sig, a)); 
			}

			//go through all derived and instances
			vector<ObjectImpl*>::iterator i;
			vector<ObjectImpl*> deriveds = getDerived();
			for (i = deriveds.begin(); i != deriveds.end(); i++)
			{
				ObjectImpl* derived = *i;
				derived->setTempRealAttr(meta, a, false);
				derived->release();
			}

			vector<ObjectImpl*> instances = getInstances();
			for (i = instances.begin(); i != instances.end(); i++)
			{
				ObjectImpl* instance = *i;
				instance->setTempRealAttr(meta, a, false);
				instance->release();
			}

			/*
			tmap::iterator f = tempvarmap.find(sig);
			if(f != tempvarmap.end()) f->second.doubleval = a;
			else tempvarmap.insert(tmap::value_type(sig, a)); 
			*/
	}

///
	UDM_DLL bool ObjectImpl::getTempBooleanAttr(const ::Uml::Uml::Attribute &meta) const
	{
			tmap &tempvarmap = locatemap(false);
			bool ret=false;
			map<string, udmvariant>::iterator f = tempvarmap.find(string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@bool");
			if(f != tempvarmap.end()) ret = f->second.boolval;
			return ret;
	}

	UDM_DLL void ObjectImpl::setTempBooleanAttr(const ::Uml::Uml::Attribute &meta, const bool &a, const bool direct) 
	{
			tmap &tempvarmap = locatemap(true);
			string sig = string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@bool";
	
			ObjectImpl * archetype = getArchetype();
			if (archetype && (archetype != (ObjectImpl*)&Udm::_null) )
			{
				string desynch_sig = sig + "_is_desycnhed";
				if (direct)
				{
					//set the attribute
					tmap::iterator f = tempvarmap.find(sig);
					if(f != tempvarmap.end()) f->second.boolval = a;
					else tempvarmap.insert(tmap::value_type(sig, a)); 
					
					//desynch from archetype
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if (d != tempvarmap.end()) d->second.boolval = true;
					else tempvarmap.insert(tmap::value_type(desynch_sig, true)); 

				}
				else
				{
					//check if desynched
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if  ( (d == tempvarmap.end()) || !(d->second.boolval))
					{
						//set the attribute
						tmap::iterator f = tempvarmap.find(sig);
						if(f != tempvarmap.end()) f->second.boolval = a;
						else tempvarmap.insert(tmap::value_type(sig, a)); 
				}
				}
				archetype->release();
			}
			else
			{
				//set the attrbute
				tmap::iterator f = tempvarmap.find(sig);
				if(f != tempvarmap.end()) f->second.boolval = a;
				else tempvarmap.insert(tmap::value_type(sig, a)); 
			
			}

			//go through all derived and instances
			vector<ObjectImpl*>::iterator i;
			vector<ObjectImpl*> deriveds = getDerived();
			for (i = deriveds.begin(); i != deriveds.end(); i++)
			{
				ObjectImpl* derived = *i;
				derived->setTempBooleanAttr(meta, a, false);
				derived->release();
			}

			vector<ObjectImpl*> instances = getInstances();
			for (i = instances.begin(); i != instances.end(); i++)
			{
				ObjectImpl* instance = *i;
				instance->setTempBooleanAttr(meta, a, false);
				instance->release();
			}

			/*
			tmap::iterator f = tempvarmap.find(sig);
			if(f != tempvarmap.end()) f->second.boolval = a;
			else tempvarmap.insert(tmap::value_type(sig, a)); 
			*/
	}

	//non-persistent , array attributes
///
	UDM_DLL vector<string> ObjectImpl::getTempStringAttrArr(const ::Uml::Uml::Attribute &meta) const
	{
			tmap &tempvarmap = locatemap(false);
			vector<string> ret;
			map<string, udmvariant>::iterator f = tempvarmap.find(string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@string_array");
			if(f != tempvarmap.end()) ret = f->second.strarrval;
			return ret;
	}

	UDM_DLL void ObjectImpl::setTempStringAttrArr(const ::Uml::Uml::Attribute &meta, const vector<string> &a, const bool direct) 
	{
			tmap &tempvarmap = locatemap(true);
			string sig = string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@string_array";

			ObjectImpl * archetype = getArchetype();
			if (archetype && (archetype != (ObjectImpl*)&Udm::_null) )
			{
				string desynch_sig = sig + "_is_desycnhed";
				if (direct)
				{
					//set the attribute
					tmap::iterator f = tempvarmap.find(sig);
					if(f != tempvarmap.end()) f->second.strarrval = a;
					else tempvarmap.insert(tmap::value_type(sig, a)); 
			
					//desynch from archetype
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if (d != tempvarmap.end()) d->second.boolval = true;
					else tempvarmap.insert(tmap::value_type(desynch_sig, true)); 

				}
				else
				{
					//check if desynched
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if  ( (d == tempvarmap.end()) || !(d->second.boolval))
					{
						//set the attribute
						tmap::iterator f = tempvarmap.find(sig);
						if(f != tempvarmap.end()) f->second.strarrval = a;
						else tempvarmap.insert(tmap::value_type(sig, a)); 
						}
				}
				archetype->release();
			}
			else
			{
				//set the attrbute
				tmap::iterator f = tempvarmap.find(sig);
				if(f != tempvarmap.end()) f->second.strarrval = a;
				else tempvarmap.insert(tmap::value_type(sig, a)); 
			}

			//go through all derived and instances
			vector<ObjectImpl*>::iterator i;
			vector<ObjectImpl*> deriveds = getDerived();
			for (i = deriveds.begin(); i != deriveds.end(); i++)
			{
				ObjectImpl* derived = *i;
				derived->setTempStringAttrArr(meta, a, false);
				derived->release();
			}

			vector<ObjectImpl*> instances = getInstances();
			for (i = instances.begin(); i != instances.end(); i++)
			{
				ObjectImpl* instance = *i;
				instance->setTempStringAttrArr(meta, a, false);
				instance->release();
			}

			/*
			tmap::iterator f = tempvarmap.find(sig);
			if(f != tempvarmap.end()) f->second.strarrval = a;
			else tempvarmap.insert(tmap::value_type(sig, a)); 
			*/
	}

///
	UDM_DLL vector<__int64> ObjectImpl::getTempIntegerAttrArr(const ::Uml::Uml::Attribute &meta) const
	{
			tmap &tempvarmap = locatemap(false);
			vector<__int64> ret;
			map<string, udmvariant>::iterator f = tempvarmap.find(string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@long_array");
			if(f != tempvarmap.end()) ret = f->second.longarrval;
			return ret;
	}

	UDM_DLL void ObjectImpl::setTempIntegerAttrArr(const ::Uml::Uml::Attribute &meta, const vector<__int64> &a, const bool direct) 
	{
			tmap &tempvarmap = locatemap(true);
			string sig = string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@long_array";


			ObjectImpl * archetype = getArchetype();
			if (archetype && (archetype != (ObjectImpl*)&Udm::_null) )
			{
				string desynch_sig = sig + "_is_desycnhed";
				if (direct)
				{
					//set the attribute
					tmap::iterator f = tempvarmap.find(sig);
					if(f != tempvarmap.end()) f->second.longarrval = a;
					else tempvarmap.insert(tmap::value_type(sig, a)); 
			
					//desynch from archetype
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if (d != tempvarmap.end()) d->second.boolval = true;
					else tempvarmap.insert(tmap::value_type(desynch_sig, true)); 

				}
				else
				{
					//check if desynched
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if  ( (d == tempvarmap.end()) || !(d->second.boolval))
					{
						//set the attribute
						tmap::iterator f = tempvarmap.find(sig);
						if(f != tempvarmap.end()) f->second.longarrval = a;
						else tempvarmap.insert(tmap::value_type(sig, a)); 
					}
				}
				archetype->release();
			}
			else
			{
				//set the attrbute
				tmap::iterator f = tempvarmap.find(sig);
				if(f != tempvarmap.end()) f->second.longarrval = a;
				else tempvarmap.insert(tmap::value_type(sig, a)); 
			}

			//go through all derived and instances
			vector<ObjectImpl*>::iterator i;
			vector<ObjectImpl*> deriveds = getDerived();
			for (i = deriveds.begin(); i != deriveds.end(); i++)
			{
				ObjectImpl* derived = *i;
				derived->setTempIntegerAttrArr(meta, a, false);
				derived->release();
			}

			vector<ObjectImpl*> instances = getInstances();
			for (i = instances.begin(); i != instances.end(); i++)
			{
				ObjectImpl* instance = *i;
				instance->setTempIntegerAttrArr(meta, a, false);
				instance->release();
			}

			/*
			tmap::iterator f = tempvarmap.find(sig);
			if(f != tempvarmap.end()) f->second.longarrval = a;
			else tempvarmap.insert(tmap::value_type(sig, a)); 
			*/
	}

///
	UDM_DLL vector<double> ObjectImpl::getTempRealAttrArr(const ::Uml::Uml::Attribute &meta) const
	{
			tmap &tempvarmap = locatemap(false);
			vector<double> ret;
			map<string, udmvariant>::iterator f = tempvarmap.find(string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@double_array");
			if(f != tempvarmap.end()) ret = f->second.doublearrval;
			return ret;
	}

	UDM_DLL void ObjectImpl::setTempRealAttrArr(const ::Uml::Uml::Attribute &meta, const vector<double> &a, const bool direct) 
	{
			tmap &tempvarmap = locatemap(true);
			string sig = string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@double_array";

			ObjectImpl * archetype = getArchetype();
			if (archetype && (archetype != (ObjectImpl*)&Udm::_null) )
			{
				string desynch_sig = sig + "_is_desycnhed";
				if (direct)
				{
					//set the attribute
					tmap::iterator f = tempvarmap.find(sig);
					if(f != tempvarmap.end()) f->second.doublearrval = a;
					else tempvarmap.insert(tmap::value_type(sig, a)); 
			
					//desynch from archetype
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if (d != tempvarmap.end()) d->second.boolval = true;
					else tempvarmap.insert(tmap::value_type(desynch_sig, true)); 

				}
				else
				{
					//check if desynched
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if  ( (d == tempvarmap.end()) || !(d->second.boolval))
					{
						//set the attribute
						tmap::iterator f = tempvarmap.find(sig);
						if(f != tempvarmap.end()) f->second.doublearrval = a;
						else tempvarmap.insert(tmap::value_type(sig, a)); 
					}
				}
				archetype->release();
			}
			else
			{
				//set the attrbute
				tmap::iterator f = tempvarmap.find(sig);
				if(f != tempvarmap.end()) f->second.doublearrval = a;
				else tempvarmap.insert(tmap::value_type(sig, a)); 
			
			}

			//go through all derived and instances
			vector<ObjectImpl*>::iterator i;
			vector<ObjectImpl*> deriveds = getDerived();
			for (i = deriveds.begin(); i != deriveds.end(); i++)
			{
				ObjectImpl* derived = *i;
				derived->setTempRealAttrArr(meta, a, false);
				derived->release();
			}

			vector<ObjectImpl*> instances = getInstances();
			for (i = instances.begin(); i != instances.end(); i++)
			{
				ObjectImpl* instance = *i;
				instance->setTempRealAttrArr(meta, a, false);
				instance->release();
			}

			/*
			tmap::iterator f = tempvarmap.find(sig);
			if(f != tempvarmap.end()) f->second.doublearrval = a;
			else tempvarmap.insert(tmap::value_type(sig, a)); 
			*/
	}

///
	UDM_DLL vector<bool> ObjectImpl::getTempBooleanAttrArr(const ::Uml::Uml::Attribute &meta) const
	{
			tmap &tempvarmap = locatemap(false);
			vector<bool> ret;
			map<string, udmvariant>::iterator f = tempvarmap.find(string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@bool_array");
			if(f != tempvarmap.end()) ret = f->second.boolarrval;
			return ret;
	}

	UDM_DLL void ObjectImpl::setTempBooleanAttrArr(const ::Uml::Uml::Attribute &meta, const vector<bool> &a, const bool direct) 
	{
			tmap &tempvarmap = locatemap(true);
			string sig = string(meta.name()) + "@" + string(::Uml::Uml::Class(meta.parent()).name()) + "@bool_array";

			ObjectImpl * archetype = getArchetype();
			if (archetype && (archetype != (ObjectImpl*)&Udm::_null) )
			{
				string desynch_sig = sig + "_is_desycnhed";
				if (direct)
				{
					//set the attribute
					tmap::iterator f = tempvarmap.find(sig);
					if(f != tempvarmap.end()) f->second.boolarrval = a;
					else tempvarmap.insert(tmap::value_type(sig, a)); 
			
					//desynch from archetype
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if (d != tempvarmap.end()) d->second.boolval = true;
					else tempvarmap.insert(tmap::value_type(desynch_sig, true)); 

				}
				else
				{
					//check if desynched
					tmap::iterator d = tempvarmap.find(desynch_sig);
					if  ( (d == tempvarmap.end()) || !(d->second.boolval))
					{
						//set the attribute
						tmap::iterator f = tempvarmap.find(sig);
						if(f != tempvarmap.end()) f->second.boolarrval = a;
						else tempvarmap.insert(tmap::value_type(sig, a)); 
					}
				}
				archetype->release();
			}
			else
			{
				//set the attrbute
				tmap::iterator f = tempvarmap.find(sig);
				if(f != tempvarmap.end()) f->second.boolarrval = a;
				else tempvarmap.insert(tmap::value_type(sig, a)); 
			
			}

			//go through all derived and instances
			vector<ObjectImpl*>::iterator i;
			vector<ObjectImpl*> deriveds = getDerived();
			for (i = deriveds.begin(); i != deriveds.end(); i++)
			{
				ObjectImpl* derived = *i;
				derived->setTempBooleanAttrArr(meta, a, false);
				derived->release();
			}

			vector<ObjectImpl*> instances = getInstances();
			for (i = instances.begin(); i != instances.end(); i++)
			{
				ObjectImpl* instance = *i;
				instance->setTempBooleanAttrArr(meta, a, false);
				instance->release();
			}
		
			/*
			tmap::iterator f = tempvarmap.find(sig);
			if(f != tempvarmap.end()) f->second.boolarrval = a;
			else tempvarmap.insert(tmap::value_type(sig, a)); 
			*/
	}



	DataNetwork::backendtabt *DataNetwork::backendtab = NULL;

	UDM_DLL void DataNetwork::RegisterBackend(const string &sig, const string &ext, DataNetwork *(*crea)(const UdmDiagram &, UdmProject*)) 
	{
		backendtabt **p = &backendtab;
		while(*p) {
			p = &((*p)->next);
		}
		*p = new backendtabt;
		(*p)->sig = sig;
		(*p)->ext = ext;
		(*p)->crea = crea;
		(*p)->next = NULL;
	}
	UDM_DLL void DataNetwork::UnRegisterBackends() 
	{
		backendtabt *p = backendtab, *tp;
		while(p) {
			tp = p;
			p = p->next;
			delete tp;
		}
		backendtab = 0;
	}
	UDM_DLL string DataNetwork::DumpBackendNames() 
	{
		backendtabt *p = backendtab;
		string r;
		if(!p) r = "<none>";
		else {
			while(p) {
				r += ' ';
				r += p->sig;
				p = p->next;
			}
		}
		return r;
	}
	UDM_DLL DataNetwork *DataNetwork::CreateBackend(string bid, const UdmDiagram &metainfo, UdmProject* project) 
	{
		backendtabt *p = backendtab;
		unsigned int l;
		/*l = bid.find(':');
		if(l >= 3) {
			bid.erase(l);
			while(p) {
				if(!stricmp(p->sig.c_str(), bid.c_str())) {
					return p->crea(metainfo);
				}
				p = p->next;
			}
		}
		else */if((l = bid.rfind('.')) >= bid.size()-4) {
			bid.erase(0,l+1);
			while(p) {
				if(!stricmp(p->ext.c_str(), bid.c_str())) {
					return p->crea(metainfo, project);
				}
				p = p->next;
			}
		}
		return NULL;
	}


	UDM_DLL bool CheckAttributeOrdering(const ::Uml::Uml::Attribute & att)
	{
		return (bool) att.ordered();
	};

	UDM_DLL vector<string> SortStrArrAttr(const vector<string> &a)
	{
		multiset<string, less<string> > b;
		vector<string> c;
		b.insert(a.begin(), a.end());
		multiset<string>::iterator i = b.begin();
		while (i != b.end()) c.push_back(*i++);

		return c;
	};

	UDM_DLL vector<__int64> StrToLongArrAttr(const vector<string> &a)
	{
		vector<__int64> c;
		vector<string>::const_iterator i = a.begin();
		while (i != a.end()) 
		{
			c.push_back(_atoi64(i->c_str()));
			i++;
		}
		return c;
	};

	UDM_DLL vector<double> StrToRealArrAttr(const vector<string> &a)
	{
		vector<double> c;
		vector<string>::const_iterator i = a.begin();
		while (i != a.end()) 
		{
			c.push_back(atof(i->c_str()));
			i++;
		}
		return c;
	};

	UDM_DLL vector<bool> StrToBoolArrAttr(const vector<string> &a)
	{
		vector<bool> c;
		vector<string>::const_iterator i = a.begin();
		while (i != a.end()) 
		{
			c.push_back(i->compare("true") ? false : true);
			i++;
		}
		return c;
	};




	UDM_DLL void ObjectImpl::setDefaultAttributes(const bool all)
	{
	
		//if all is false, only nonpersistent attributes will be modified
		set<::Uml::Uml::Attribute> attributes = Uml::AncestorAttributes(type());
		set<::Uml::Uml::Attribute>::const_iterator c_i = attributes.begin();

			while (c_i != attributes.end())
			{
				::Uml::Uml::Attribute att = *c_i++;
				if (att.defvalue() || (att.min() > 0))
				{

					//has a default value specified in the MetaModel
					//so we set it's default value to this
					string attrType=att.type();
					bool attrArray = ((att.max() != 0) && (att.max() != 1));
					bool np_attr = att.nonpersistent();
					bool ordered = att.ordered();

					if (!np_attr && !all) continue;

					if((attrType=="String")||(attrType=="Text"))
					{

						if(attrArray)
						{
							if (!np_attr)
							{
								if (ordered)
									setStringAttrArr(att, SortStrArrAttr(att.defvalue()), false);
								else
									setStringAttrArr(att, att.defvalue(), false);
							}//if (!np_attr)
							else
							{
								if (ordered)
									setTempStringAttrArr(att, SortStrArrAttr(att.defvalue()), false);
								else
									setTempStringAttrArr(att,att.defvalue(), false);
							}//else (!np_attr)
						}

						else
						{
							if (!np_attr)
								setStringAttr(att,att.defvalue()[0], false);
							else
								setTempStringAttr(att,att.defvalue()[0], false);
						}

					}
					
					else if(attrType=="Integer")
					{
						if (attrArray)
						{
							if (!np_attr)
							{
								if (ordered)
									setIntegerAttrArr(att,SortArrAttr<__int64>(StrToLongArrAttr(att.defvalue())), false);
								else
									setIntegerAttrArr(att,StrToLongArrAttr(att.defvalue()), false);
							}//if (!np_attr)
							else
							{
								if (ordered)
									setTempIntegerAttrArr(att,SortArrAttr<__int64>(StrToLongArrAttr(att.defvalue())), false);
								else
									setTempIntegerAttrArr(att,StrToLongArrAttr(att.defvalue()), false);

							}//else  (!np_attr)
						}//if (attrArray)
						else
						{
							if (!np_attr)
								setIntegerAttr(att,atol(((string)att.defvalue()[0]).c_str()), false);
							else
								setTempIntegerAttr(att,atol(((string)att.defvalue()[0]).c_str()), false);
						}//else (attrArray)

					}
					
					else if(attrType=="Real")
					{
						if (attrArray)
						{
							if (!np_attr)
							{
								if (ordered)
									setRealAttrArr(att,SortArrAttr(StrToRealArrAttr(att.defvalue())), false);
								else
									setRealAttrArr(att,StrToRealArrAttr(att.defvalue()), false);
							}
							else
							{
								if (ordered)
									setTempRealAttrArr(att,SortArrAttr(StrToRealArrAttr(att.defvalue())), false);
								else
									setTempRealAttrArr(att,StrToRealArrAttr(att.defvalue()), false);
							}
						}//if (attrArray)
						else
						{
							if (!np_attr)
								setRealAttr(att, atof(((string)att.defvalue()[0]).c_str()), false);
							else
								setTempRealAttr(att, atof(((string)att.defvalue()[0]).c_str()), false);
						}


					}
					
					else if(attrType=="Boolean")
					{
						if (attrArray)
						{
							if (!np_attr)
							{
								if (ordered)
								{
									setBooleanAttrArr(att,SortArrAttr<bool>(StrToBoolArrAttr(att.defvalue())), false);
								}
								else
								{
									setBooleanAttrArr(att,StrToBoolArrAttr(att.defvalue()), false);
								}
							}
							else
							{
								if (ordered)
								{
									setTempBooleanAttrArr(att,SortArrAttr<bool>(StrToBoolArrAttr(att.defvalue())), false);
								}
								else
								{
									setTempBooleanAttrArr(att,StrToBoolArrAttr(att.defvalue()), false);
								}
							}
						}
						else
						{
							if (!np_attr)
								setBooleanAttr(att,( (((string)att.defvalue()[0])).compare("true") ? false : true ), false);
							else
								setTempBooleanAttr(att,( (((string)att.defvalue()[0])).compare("true") ? false : true ), false);
						}

					}
					else
					{
						// Unknown attribute type
						throw udm_exception(string("Unknown attribute type: ") + attrType);
					}
				}
			}
		}

		UDM_DLL void ObjectImpl::CopyAttributeFrom(const ::Uml::Uml::Attribute& which, const ObjectImpl*  from, bool direct)
		{
			string attrType=which.type();
			bool attrArray = ((which.max() != 0) && (which.max() != 1));
			bool np_attr = which.nonpersistent();

			if((attrType=="String") || (attrType=="Text") )
			{
				if(attrArray)
					if (!np_attr)
						setStringAttrArr(which,from->getStringAttrArr(which), direct);
					else
						setTempStringAttrArr(which,from->getTempStringAttrArr(which), direct);

				else
					if (!np_attr)
						setStringAttr(which,from->getStringAttr(which), direct);
					else
						setTempStringAttr(which,from->getTempStringAttr(which), direct);			

			}
			else if(attrType=="Integer")
			{
				if (attrArray)
					if (!np_attr)
						setIntegerAttrArr(which,from->getIntegerAttrArr(which), direct);
					else
						setTempIntegerAttrArr(which,from->getTempIntegerAttrArr(which), direct);

				else
					if (!np_attr)
						setIntegerAttr(which,from->getIntegerAttr(which), direct);
					else
						setTempIntegerAttr(which,from->getTempIntegerAttr(which), direct);

			}
			else if(attrType=="Real")
			{
				if (attrArray)
					if (!np_attr)
						setRealAttrArr(which,from->getRealAttrArr(which), direct);
					else
						setTempRealAttrArr(which,from->getTempRealAttrArr(which), direct);

				else
					if (!np_attr)
						setRealAttr(which,from->getRealAttr(which), direct);
					else
						setTempRealAttr(which,from->getTempRealAttr(which), direct);
			}
			else if(attrType=="Boolean")
			{
				if (attrArray)
					if (!np_attr)
						setBooleanAttrArr(which,from->getBooleanAttrArr(which), direct);
					else
						setTempBooleanAttrArr(which,from->getTempBooleanAttrArr(which), direct);

				else
					if (!np_attr)
						setBooleanAttr(which,from->getBooleanAttr(which), direct);
					else
						setTempBooleanAttr(which,from->getTempBooleanAttr(which), direct);

					
			}
			else
			{
				// Unknown attribute type
				throw udm_exception(string("Unknown attribute type: ") + attrType);
			}

		};

		UDM_DLL void ObjectImpl::CopyAttributesFrom(const ObjectImpl*  from, bool direct)
		{
			set <::Uml::Uml::Attribute> attributes = Uml::AncestorAttributes(type());
			set <::Uml::Uml::Attribute>::iterator attr_i = attributes.begin();
			while (attr_i != attributes.end())
				CopyAttributeFrom(*attr_i++, from, direct);
		};

		UDM_DLL void ObjectImpl::CopyAttributeFromArchetype(const ::Uml::Uml::Attribute& which)
		{
			ObjectImpl * archetype = getArchetype();
			CopyAttributeFrom(which, archetype);
			archetype->release();
		};

		UDM_DLL void ObjectImpl::CopyAttributesFromArchetype()
		{
			ObjectImpl * archetype = getArchetype();
			CopyAttributesFrom(archetype);
			archetype->release();
		};


		//the map for static metadepository
		map<string, const UdmDiagram*>* MetaDepository::meta_dep = NULL;
		

		UDM_DLL const UdmDiagram & MetaDepository::LocateDiagram(const string& DgrName) 
		{
			
			map<string, const UdmDiagram*>::const_iterator i = meta_dep->find(DgrName);
			if ( i == meta_dep->end()) 	
				throw udm_exception(string("Meta diagram ") + DgrName + string(" was not found in metadepository!"));
			
			return *(i->second);
			

		};

		UDM_DLL bool MetaDepository::StoreDiagram(const string& DgrName, const UdmDiagram& dgr)
		{
			if (meta_dep == NULL)
				meta_dep = new map<string, const UdmDiagram*>;

			pair<const string, const UdmDiagram *> item(DgrName, &dgr);
			pair<map<string, const UdmDiagram*>::iterator, bool> res = meta_dep->insert(item);
			return res.second;
			
		};

		UDM_DLL void MetaDepository::RemoveDiagram(const string& DgrName)
		{
			meta_dep->erase(DgrName);
			if (meta_dep->size() == 0)
				delete meta_dep;

		};
}

