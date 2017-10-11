#ifdef _WIN32
#include <direct.h>

void chdir_udm_test(const char* name)
{
    CPPUNIT_ASSERT(_chdir((std::string(getenv("UDM_PATH")) + "\\tests\\" + name).c_str()) == 0);
}
#else
void chdir_udm_test(const char* name)
{
}
#endif
