#include "StdAfx.h"

#include <strstream>
#include <cmath>
#include "CardinalityObject.h"
#include "AttributeObject.h"

/*
CHANGELOG

  10/24/04	-	endre

		- Added a new type, 'Text'. It's the same as String but it gets persisted differently in DOM backend.
*/


//parser

#include "Lattrib.hpp"
#include "Pattrib.hpp"

//Stringbuffer

#include "StringBuffer.h"




bool isTypeSpec(const std::string str)
{
	if 
	(!str.compare(TS_INTEGER)) return true;
	else if 
	(!str.compare(TS_REAL)) return true;
	else if 
	(!str.compare(TS_BOOLEAN)) return true;
	else if 
	(!str.compare(TS_STRING)) return true;
	else if 
	(!str.compare(TS_TEXT)) return true;
	else 
	{
		throw AttributeObjectException(std::string("Unknown Type specifier: ") + str);
		return false;		//semantic error
	}
};

//valid order specifiers
bool isOrderSpec(const std::string str)
{
	if 
	(!str.compare(OS_ORDERED)) return true;
	else if 
	(!str.compare(OS_UNORDERED)) return true;
	else 
	{
		throw AttributeObjectException(std::string("Unknown Order specifier: ") + str);
		return false;		//semantic error
	}
};

//valid visibility specifier
bool isVisibSpec(const std::string str)
{
	if 
	(!str.compare(VSS_PUBLIC)) return true;
	else if 
	(!str.compare(VSS_PROTECTED)) return true;
	else if 
	(!str.compare(VSS_PRIVATE)) return true;
	else if 
	(!str.compare(VSS_PACKAGE)) return true;
	else 
	{
		throw AttributeObjectException(std::string("Unknown Visibility specifier: ") + str);
		return false;		//semantic error
	}
};

//valid volatile specifier
bool isVolatileSpec(const std::string str)
{
	if 
	(!str.compare(VSS_VOLATILE)) return true;
	else  if
	(!str.compare(VSS_REGISTER)) return true;
	{
		throw AttributeObjectException(std::string("Unknown Volatile specifier: ") + str);
		return false;		//semantic error
	}
};

//calid volatile or visib specifier
bool isVisibNpSpec(const std::string str)
{
	if 
	(!str.compare(VSS_PUBLIC)) return true;
	else if 
	(!str.compare(VSS_PROTECTED)) return true;
	else if 
	(!str.compare(VSS_PRIVATE)) return true;
	else if 
	(!str.compare(VSS_PACKAGE)) return true;
	else if
	(!str.compare(VSS_VOLATILE)) return true;
	else if
	(!str.compare(VSS_REGISTER)) return true;
	else 
	{
		throw AttributeObjectException(std::string("Unknown specifier: ") + str);
		return false;		//semantic error
	}

	

};

//valid bool specifier
bool isBoolSpec(const std::string str)
{
	if 
	(!str.compare(BV_TRUE)) return true;
	else if 
	(!str.compare(BV_FALSE)) return true;
	else 
	{
		throw AttributeObjectException(std::string("Unknown Boolean value: ") + str);
		return false;		//semantic error
	}
};

AttributeObject * AttributeObject::theInstance = NULL;

AttributeObject::AttributeObject(std::string str)
: UML_attribute(str),ordered(false), type_set(false), name_set(false), vis(Public), nonpersistent(false), reg_val(false), real_int_set(false)
{
	theInstance = this;

	StringBuffer strbuf(str);

	Lattrib lexer(strbuf);
	lexer.setFilename(std::string("buffer:") + str);
	Pattrib parser(lexer);
	parser.setFilename(std::string("buffer:") + str);

	try 
	{
		parser.startRule();
	}
	catch (CardinalityObjectException &e)
	{
		throw AttributeObjectException(std::string("Cardinality Parse error: ") + e.what() + ", in Attribute Specifier: " + UML_attribute);
	}


	catch (...)
	{
		throw AttributeObjectException(std::string("Unknown Parse error occured while parsing:") + str);

	}



	if (!name_set || !type_set)
		throw AttributeObjectException(std::string("Parser error:(Either name or type as not specified: " ) + str);

	//reset the static pointers, this object is completly parsed in
	theInstance = NULL;
	c_obj.ResetInstance();
};

AttributeObject::~AttributeObject()
{
	theInstance = NULL;
};


AttributeObject* AttributeObject::GetInstance()
{
	return theInstance;
};

void AttributeObject::setName(const std::string str)
{
	this->name = str;
	name_set = true;
};

void AttributeObject::setType(const std::string str)
		{
	
	if (!str.compare(TS_INTEGER)) t = Integer;
	else if
		(!str.compare(TS_REAL)) t = Real;
	else if
		(!str.compare(TS_BOOLEAN)) t = Boolean;
	else if
		(!str.compare(TS_STRING)) t = String; 
	else if
		(!str.compare(TS_TEXT)) t = Text; 
	
	//the parser should guarantee that this never happens
	else throw AttributeObjectException(std::string("Unknown type specifier: " ) + str);

	type_set = true;
};

std::string AttributeObject::strType()
{

	if (t == Integer) return TS_INTEGER;
	if (t == Real) return TS_REAL;
	if (t == Boolean) return TS_BOOLEAN;
	if (t == String) return TS_STRING;
	if (t == Text) return TS_TEXT;
	return "";
};


void AttributeObject::setOrder(const std::string str)
{
	if (!str.compare(OS_ORDERED)) ordered = true;
	else if (!str.compare(OS_UNORDERED)) ordered = false;
	//the parser should guarantee that this never happens
	else throw AttributeObjectException(std::string("Unknown order specifier: " ) + str);


};


void AttributeObject::setVolReg(const std::string str)
{
	if (!str.compare(VSS_VOLATILE)) nonpersistent = true;
	if (!str.compare(VSS_REGISTER)) reg_val = true;
	
};

void AttributeObject::setVisib(const std::string str)
{
	if (!str.compare(VSS_PUBLIC))
		vis = Public;
	else if (!str.compare(VSS_PROTECTED))
		vis = Protected;
	else if (!str.compare(VSS_PRIVATE))
		vis = Private;
	else if (!str.compare(VSS_PACKAGE))
		vis = Package;
	//the parser should guarantee that this never happens
	else throw AttributeObjectException(std::string("Unknown visibility specifier: " ) + str);
};

void AttributeObject::setVisibNp(const std::string str)
{
	if (!str.compare(VSS_PUBLIC))
		vis = Public;
	else if (!str.compare(VSS_PROTECTED))
		vis = Protected;
	else if (!str.compare(VSS_PRIVATE))
		vis = Private;
	else if (!str.compare(VSS_PACKAGE))
		vis = Package;
	else if (!str.compare(VSS_VOLATILE))
		nonpersistent = true;
	else if (!str.compare(VSS_REGISTER))
		reg_val = true;
//the parser should guarantee that this never happens
	else throw AttributeObjectException(std::string("Unknown visibility specifier: " ) + str);
};

std::string AttributeObject::strVisibility()
{
	if (vis == Public) return VSS_PUBLIC;
	if (vis == Protected) return VSS_PROTECTED;
	if (vis == Private) return VSS_PRIVATE;
	if (vis == Package) return VSS_PACKAGE;
	return "";
};

void AttributeObject::setVisib(const char c)
{
	switch (c)
	{
	case VSC_PUBLIC:
		vis = Public;
		break;
	case VSC_PROTECTED:
		vis = Protected;
		break;
	case VSC_PRIVATE:
		vis = Private;
		break;
	case VSC_PACKAGE:
		vis = Package;
		break;
	};
};


bool AttributeObject::CheckCard() const
{
	if (c_obj.getmax() < 0) return true;
	unsigned int c_obj_max = c_obj.getmax();//it is positive


	switch (t)
	{
	case Integer:
		return (defval_int.size() < c_obj_max);
		break;
	case Real:
		return (defval_real.size() < c_obj_max);
		break;
	case Boolean:
		return (defval_bool.size() < c_obj_max);
		break;
	case String:
		return (defval_string.size() < c_obj_max);
		break;
	};
	return false;

};

void AttributeObject::addDefBool(const std::string str)
{
	if (t != Boolean)
		throw AttributeObjectException("The attribute is not of boolean type!");

	if (!CheckCard())
		throw AttributeObjectException("The default value multiplicity exceeds attribute multiplicity!");

	if (!str.compare(BV_TRUE)) 
		defval_bool.push_back(true);
	else if (!str.compare(BV_FALSE))
		defval_bool.push_back(false);
	//the parser shoudl guarantee that this never happens
	else throw AttributeObjectException(std::string("Unknown bool specifier: " ) + str);

};

bool AttributeObject::CheckNum(const std::string str) const
{
	if ((t == Integer) && (str.find('.') != std::string::npos))
		throw AttributeObjectException(std::string("Numerical type expected: " ) + str);
	else return true;
};

void AttributeObject::addDefReal(const std::string str)
{
	if ((t != Integer) && (t != Real))
		throw AttributeObjectException(std::string("The attribute is not of numerical type. Val:  ") + str + ", Attribute specifier: " + UML_attribute );


	if (!CheckCard())
		throw AttributeObjectException(std::string("The default value multiplicity exceeds attribute multiplicity. Attribute specifier:") + UML_attribute);

	//we read in the real values in two steps ( first the integer, then the decimal part)
	// I admit that this is a hack, But I was unable to create a grammar which whould have parsed
	// the default real values otherwise.

	if (!real_int_set)
		real_int = atol(str.c_str());
	else
		defval_real.push_back( (double)real_int + (double)atof(str.c_str())/ pow(10, str.size()) );
	
	

	real_int_set = !real_int_set;

};
void AttributeObject::addDefNum(const std::string str)
{
	if ((t != Integer) && (t != Real))
		throw AttributeObjectException(std::string("The attribute is not of numerical type. Val:  ") + str + ", Attribute specifier: " + UML_attribute );


	if (!CheckCard())
		throw AttributeObjectException(std::string("The default value multiplicity exceeds attribute multiplicity. Attribute specifier:") + UML_attribute);

	if (t == Real)
		defval_real.push_back(atof(str.c_str()));
	else if ( (t == Integer) && (str.find('.') == std::string::npos) )
		defval_int.push_back(atol(str.c_str()));
	else throw AttributeObjectException(std::string("Not a numerical value, or wrong numerical type. Val: ") + str + ", Attribute specifier: " + UML_attribute);

};

void AttributeObject::addDefStr(const std::string str)
{
	//the parser should guarantee this never happens
	if ( t != String)
		throw AttributeObjectException("The attribute is not of string type. Val: " + str + ", Attribute specifier:" + UML_attribute);

	if (!CheckCard())
		throw AttributeObjectException("The default value multiplicity exceeds attribute multiplicity!");

	defval_string.push_back(str);
};


//XML writer

std::strstream& AttributeObject::operator >>(std::strstream& xml)
{

	//name and type, 
	xml << "   <Uml:Attribute name= \"" << name << "\" type= \"" << strType() << "\"";

	//ordered and visibility, optionals 
	xml << (ordered ? " ordered= \"true\"" : " ordered= \"false\"");

	
	xml << " visibility= \"" << strVisibility() << "\"";
	xml << " nonpersistent= \"" << (nonpersistent? "true" : "false") << "\"";
	xml << " registry= \"" << (reg_val? "true" : "false") << "\"";

	//default values

	if (t == Integer && defval_int.size())
	{

		xml << " defvalue= \"";
		for(std::vector<long>::iterator i = defval_int.begin(); i!= defval_int.end(); i++)
		{
			if (i != defval_int.begin()) 
				xml << ';';

			//need some escapeing here,
			//we have to be DOM DataNetwork compliant,
			//regarding array strings
			//that means, the delimiter is ; and
			

			xml << *i;
		}
		xml << "\"";
	}

	if (t == Real && defval_real.size())
	{
		xml << " defvalue= \"";
		for(std::vector<double>::iterator i = defval_real.begin(); i!= defval_real.end(); i++)
		{
			if (i != defval_real.begin()) 
				xml << ';';
			xml << *i;
		}
		xml << "\"";
	}



	if (t == Boolean && defval_bool.size())
	{
		xml << " defvalue= \"";
		for(std::vector<bool>::iterator i = defval_bool.begin(); i!= defval_bool.end(); i++)
		{
			if (i != defval_bool.begin()) 
				xml << ';';
			xml << (*i ? "true" : "false" );
		}
		xml << "\"";
	
	}

	if (t == String && defval_string.size())
	{
		xml << " defvalue= \"";
		for(std::vector<std::string>::iterator i = defval_string.begin(); i!= defval_string.end(); i++)
		{
			if (i != defval_string.begin()) 
				xml << ';';
			
			//need some escapeing here,
			//we have to be DOM DataNetwork compliant,
			//regarding array strings
			//that means, the delimiter is ; unless escaped
			
			const std::string a_item = *i;
			std::string::const_iterator a_item_ci = a_item.begin();
			while (a_item_ci != a_item.end())
			{

				switch (*a_item_ci)
				{
				case ';':
					xml << "\\";		//escape the semicolon(;)
					xml << *a_item_ci;	//write the character
					break;
				case '\\':
					xml << "\\";		//escape the escape(\)
										//I think the grammar does not allow this
										//for the time being.
					xml << *a_item_ci;	//write the character
					break;
				case '"':
					break;				//just ignore the ending and beginning "-s
				default:
					xml << *a_item_ci;	//write the character

				}
				
				a_item_ci++;
			};  

		}
		xml << "\"";
	}
	
	return c_obj >> xml;
};