
#ifndef MOBIES_MGA_DEFS_H
#define MOBIES_MGA_DEFS_H

#define SmartBSTR _bstr_t


//MGA macros
//GME 003 macros
#define MGACOLL_ITERATE(iftype, collifptr) \
{ \
	ASSERT( collifptr != NULL ); \
	long iter_count = 0; \
	COMTHROW( collifptr->get_Count(&iter_count) ); \
	ASSERT( iter_count >= 0 ); \
	iftype##Ptr *arrptr, *arrend, *array = new iftype##Ptr[iter_count]; \
	if(iter_count > 0) \
		COMTHROW( collifptr->GetAll(iter_count, &(*array)) ); \
	arrend = array+iter_count; \
	for(arrptr = array; arrptr != arrend; arrptr++)

#define MGACOLL_ITER (*arrptr)

#define MGACOLL_AT_END (arrptr == arrend)

#define MGACOLL_ITERATE_END \
	delete[] array; \
}




//so-called error handling 

void SetErrorInfo(long,unsigned short *) { UDM_ASSERT("NotYet Implemented"); }
void comthrow(HRESULT res, char *e, int l);
#define COMTHROW(expr) comthrow(expr, #expr, __LINE__)
#define CASSERT(x) if(!(x)) COMTHROW( ((x), -1))


class gme_exc : public udm_exception 
{ 
	char excbuf[20];
public:
	gme_exc(long l) : udm_exception(std::string("GME error: ")+ _ltoa(l, excbuf, 16)) { ; }
};


static void comthrow(HRESULT res, char *e, int l) 
{
	if ((res) != S_OK) throw gme_exc(res);
}

//GmeObject class helper macros
#define objself (folderself? (IMgaObject *) folderself : (IMgaObject *)self)
#define testself (self ? self : (COMTHROW(("Invalid method on folders", -1)), NULL))
#define NAMEGET(x) (((string)((x).name())).c_str())
#define PATHGET(x) (((x).getPath2("::", false)).c_str())
#define foldiffold (folderself ? folderself : self)
#endif