#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <time.h>

#include "File2Code.h"

File2Code::File2Code(const std::string& name, // the name of the generated source file
                    const std::string& infname, // the input xsd file
                    const GenModeType& mode,   // mode = java or cpp
                    const std::string& pn): // package name for java
  m_name(name),
  m_infname (infname),
  m_mode(mode),
  m_packageName(pn)
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
  if (!m_packageName.empty())
    out << "package " << m_packageName << ";" << std::endl << std::endl;

  out << "public class " << m_name << "{" << std::endl;
  out << "\tprivate static String str = new String("");" << std::endl << std::endl;
  out << "\tpublic static String getString()" << std::endl;
  out << "\t{" << std::endl;
  out << "\t\tif (str.length() == 0)" << std::endl;
  out << "\t\t{" << std::endl;

}
//==================================
void File2Code::genJavaTail(std::ostream& out)
{
    out << "}" << std::endl;
}

//==================================
void File2Code::genCppHeader(std::ostream& out)
{
  
    out << "#ifndef " <<  m_name << "_H" << std::endl;
    out << "#define " << m_name << "_H" << std::endl;
    out << "#include <string>" << std::endl;
    out << "#pragma warning( disable : 4010)" << std::endl << std::endl;
    out << "namespace " << m_name << std::endl;
    out << "{" << std::endl;
    out << "const std::string& getString()" << std::endl;
    out << "{" << std::endl;
    out << "\tstatic std::string str;" << std::endl;
    out << "\tif (str.empty())" << std::endl;
    out << "\t{" << std::endl;
  
}
//==================================
void File2Code::genCppTail(std::ostream& out)
{
    out << "} //namespace" << std::endl;
    out << "#endif" << std::endl;
}
//==================================
void File2Code::replace(std::string& out,
                        const std::string& str,
                        const std::string& s1,
                        const std::string& s2)
{
    out.clear();
      std::string::size_type p = str.find_first_of(s1,0);
      if (p == std::string::npos)
        out += str;
      else
      {

        std::string::size_type oldp = 0;
        while(p != std::string::npos)
        {
          out += str.substr(oldp,p-oldp);
          out += s2;
          oldp = p + 1;
          p = str.find_first_of(s1, oldp);
        }
        out += str.substr(oldp,str.size() - oldp);
      }
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
      out << "\t\t\tstr +=";   
      out << "\"";   

      std::string tmp;
      replace(tmp, str, "\\", "\\\\");
      std::string tmp1;
      replace(tmp1, tmp, "\"", "\\\"");
      /*std::string tmp;
      replace(tmp, str, "\\&quot;", "\\\\&quot;");
      std::string tmp1;
      replace(tmp1, tmp, "\\n", "\\\\n");*/

      int b_eol = tmp1.find_last_not_of("\r\n");
      if (b_eol != std::string::npos)
        tmp1.erase(b_eol + 1);
      if (!tmp1.empty() && (tmp1.at(0) == '\r' || tmp1.at(0) == '\n'))
        tmp1.erase();

      out << tmp1;
      out << "\\n\"";  
      out << ";" << std::endl;   
    }
    out << "\t\t}" << std::endl;
    out << "\t\treturn str;" << std::endl;
    out << "\t}" << std::endl;
}
