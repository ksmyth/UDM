#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include "../Udm/File2Code/File2Code.h"
//==================================
int main(int argc, char **argv)
{
 	if(argc < 3)
	{
		std::cerr << "Usage: " << argv[0] << " <text_filename> <namespace_name> <JAVA|CPP>" << std::endl;
		return(-1);
	}

	try
	{

    std::string infname(argv[1]);
    std::string outfname = std::string(argv[2]);
    std::string pn;
    std::string ext(".h");
    File2Code::GenModeType mode(File2Code::CPP);
    if (argc == 4)
    {
      std::string ar(argv[3]);
      if (ar == "JAVA")
      {
        if (argc != 5)
        {
          std::cerr << "Usage: " << argv[0] << " <text_filename> <namespace_name> <JAVA> <package_name>" << std::endl;
          return(-1);
        }
        pn = argv[4];
        ext = ".java";
        mode = File2Code::JAVA;
      }
      else
      if (ar == "CPP")
      {
        ext = ".h";
        mode = File2Code::CPP;
      }
    }
    outfname += ext;

    std::ofstream out(outfname.c_str());
    if (!out.good())
    {
      std::string err = outfname + std::string(" could not open.");
      throw std::runtime_error(err);
    }

    File2Code f2c(argv[2], infname, mode, pn);
    f2c.gen(out);

	}
 	catch(const std::exception &e)
	{
    std::cout << "Exception: " << e.what();
		return 1;

   }

  return 0;
}
