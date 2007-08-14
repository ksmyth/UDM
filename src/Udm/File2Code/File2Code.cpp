#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

#include ".\file2code.h"

File2Code::File2Code(const std::string& name, 
                    const std::string& infname, 
                    const GenModeType& mode):
  m_name(name),
  m_infname (infname),
  m_mode(mode)
{
}

File2Code::~File2Code(void)
{
}

//==================================
void File2Code::gen(std::ostream& out)
{
  if (m_mode == JAVA)
  {
    genJava(out);
  }
  else
  if (m_mode == CPP)
  {
    genCpp(out);
  }

}

//==================================
void File2Code::genJava(std::ostream& out)
{
  
  genJavaHeader(out);
  genBody(out);
  genJavaTail(out);
}
//==================================
void  File2Code::genCpp(std::ostream& out)
{

  genCppHeader(out);
  genBody(out);
  genCppTail(out);
}
//==================================
void File2Code::genJavaHeader(std::ostream& out)
{
      out << "class " << m_name << "{" << std::endl;
      out << "private static String str = new String("");" << std::endl;
      out << "public static String getString()" << std::endl;
      out << "{" << std::endl;
      out << "if (str.length() == 0)" << std::endl;
      out << "{" << std::endl;

}
//==================================
void File2Code::genJavaTail(std::ostream& out)
{
    out << "}" << std::endl;
}

//==================================
void File2Code::genCppHeader(std::ostream& out)
{
  /*
      out << "#ifndef " <<  m_name << "_H" << std::endl;
      out << "#define " << getter_func_name << "_H" << std::endl;
      out << "#include <string>" << std::endl;
      out << "#pragma warning( disable : 4010)" << std::endl << std::endl;
      out << "const std::string& " << getter_func_name << "()" << std::endl;
      out << "{" << std::endl;
      out << "static std::string str;" << std::endl;
      out << "if (str.empty())" << std::endl;
      out << "{" << std::endl;
      */
}
//==================================
void File2Code::genCppTail(std::ostream& out)
{
    out << "}" << std::endl;
    out << "#endif" << std::endl;
}

//==================================
void File2Code::genBody(std::ostream& out)
{

    std::ifstream in(m_infname.c_str());
    if (!in.good())
    {
      std::string err = m_infname + std::string(" could not open.");
      throw std::runtime_error(err);
    }

    std::string str;
    while(in.good())
    {
      std::getline(in, str);
              //str = "bb\"a\"bb";
      out << "str +=";   
      out << "\"";   
      std::string::size_type p = str.find_first_of("\"",0);
      if (p == std::string::npos)
        out << str;
      else
      {

        std::string::size_type oldp = 0;
        std::string lofax;
        while(p != std::string::npos)
        {
          out << str.substr(oldp,p-oldp);
          out << "\\\"";
          oldp = p + 1;
          p = str.find_first_of("\"", oldp);
        }
        out << str.substr(oldp,str.size() - oldp);
      }
      out << "\\n\"";  
      out << ";" << std::endl;   
    }
    out << "}" << std::endl;
    out << "return str;" << std::endl;
    out << "}" << std::endl;
}
