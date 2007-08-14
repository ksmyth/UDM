// test_ns2.cpp : Defines the entry point for the console application.
//

#include "CHost.h"

void writeTest(const std::string& fname)
{

	Udm::SmartDataNetwork  out(CHost::diagram);
	out.CreateNew(fname.c_str(), "CHost", CHost::RootFolder::meta, Udm::CHANGES_PERSIST_ALWAYS);

	CHost::RootFolder rf = CHost::RootFolder::Cast( out.GetRootObject() );
	rf.name() = "hello, this is rf!";

	CHost::C::CModel cm = CHost::C::CModel::Create(rf);
	cm.name() = "C::CModel obj";

	CHost::A::DAtom d = CHost::A::DAtom::Create(cm);
	d.name() = "A::DAtom obj";

	out.CloseWithUpdate();
}

//==========================================
void readTest(const std::string& fname)
{

	Udm::SmartDataNetwork  out(CHost::diagram);
	out.OpenExisting(fname.c_str());

	out.CloseNoUpdate();
}
//=========================================

int main()
{
	try
	{
		std::string fn = "test1.mga";
		writeTest(fn);
		readTest(fn);
	}
	catch(udm_exception& e)
	{
	    std::cout << e.what();
	    return 1;
	}

	return 0;
}

