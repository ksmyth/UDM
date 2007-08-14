    /*
     *	Copyright (c) Vanderbilt University, 2000-2001
     *	ALL RIGHTS RESERVED
     *
     *	Vanderbilt University disclaims all warranties with regard to this
     *	software, including all implied warranties of merchantability
     *	and fitness.  In no event shall Vanderbilt University be liable for
     *	any special, indirect or consequential damages or any damages
     *	whatsoever resulting from loss of use, data or profits, whether
     *	in an action of contract, negligence or other tortious action,
     *	arising out of or in connection with the use or performance of
     *	this software.
     */
/*
CHANGELOG
=========
	-	27/02/04	-	endre
				
		-	added the call GetPackage() for CClassBuilder and CClassCopyBuilder and the abstract method for CClassBase

  
	-	24/02/04	-	endre
	
		-	Added the CPackageBuilder and CPackageBuilderList custom BON classes to reflect the newly introduced Package model
		-	Changed the Gather* functions to work with CPackageBuilder-s instead of folders.

*/

    
    #ifndef UML_INTERPRETER_H
    #define UML_INTERPRETER_H
    
    #include "Builder.h"
    #include <strstream>
    #include "CardinalityObject.h"
    #include "AttributeObject.h"
    
    class CClassDiagramBuilder;
    
    class CClassBuilder;
    class CClassCopyBuilder;
    class CClassBase;
    class CCompositeClass;
    class CAttribute;
	class CPackageBuilder;
    
    class CCompositionBuilder;
    class CAssociationBase;
    class CAssociationBuilder;
    class CDirectAssociationBuilder;
    
    class CConstraintBuilder;
    class CConstraintDefinitionBuilder;
    
    typedef CTypedPtrList<CPtrList, CClassDiagramBuilder*>		CClassDiagramList;
    
    typedef CTypedPtrList<CPtrList, CClassBase*>				CClassBaseList;
    typedef CTypedPtrList<CPtrList, CCompositeClass*>			CCompositeClassList;
    typedef CTypedPtrList<CPtrList, CClassCopyBuilder*>			CClassCopyList;
    typedef CTypedPtrList<CPtrList, CClassBuilder*>				CClassList;
    typedef CTypedPtrList<CPtrList, CAttribute*>				CAttributeList;
    
    typedef CTypedPtrList<CPtrList, CCompositionBuilder*>		CCompositionList;
    
    typedef CTypedPtrList<CPtrList, CAssociationBase*>			CAssociationBaseList;
    typedef CTypedPtrList<CPtrList, CDirectAssociationBuilder*>	CDirectAssociationList;
    typedef CTypedPtrList<CPtrList, CAssociationBuilder*>		CAssociationList;
    
    typedef CTypedPtrList<CPtrList, CConstraintBuilder*>		CConstraintBuilderList;
    typedef CTypedPtrList<CPtrList, CConstraintDefinitionBuilder*>	CConstraintDefinitionBuilderList;
    typedef CTypedPtrList<CPtrList, CPackageBuilder*>	CPackageBuilderList;

    #define NEW_BON_INVOKE
    //#define DEPRECATED_BON_INVOKE_IMPLEMENTED
    //#define IMPLEMENT_OLD_INTERFACE_ONLY
    
    class CComponent{
    public:
    	virtual ~CComponent();
    	CComponent() : focusfolder(NULL) { ; }
    	CBuilderFolder *focusfolder;
    	CBuilderFolderList selectedfolders;
    	void InvokeEx(CBuilder &builder,CBuilderObject *focus, CBuilderObjectList &selected, long param);
    //	void Invoke(CBuilder &builder, CBuilderObjectList &selected, long param);
    protected:
    	CString name;
		//CBuilderFolderList packageList;
		CPackageBuilderList packageList;

    	CClassDiagramList sheets;
    	CCompositeClassList compositeClasses;
    	CCompositionList compositions;
    	CAssociationBaseList associations;
    public:
    	static CComponent *theInstance;
    public:
    
    	void AddComposition(CCompositionBuilder *comp);
    	void AddAssociation(CAssociationBase *ass);
  		int  GatherPackageFolders(CBuilderFolder *folder,CPackageBuilderList &packages);
  		void GatherSheets(CBuilderFolder *folder,CClassDiagramList &sheets, bool rp_too = false);
  		void GatherAllSheets(CClassDiagramList &sheets);
  		void GatherPackageSheets(CPackageBuilder *package,CClassDiagramList &sheets);
    	void BuildInheritance();
    	bool CheckInheritance();
    	void BuildCompositions();
    	void BuildAssociations();
		void BuildIsoAssociations();
    	void DumpXML(std::strstream&, const CString & version);
    	void DumpIsolatedXML(std::strstream &, const CString & version);
    	void DumpCrossXML(std::strstream &, const CString & version);
    	void DumpProjectXML(CBuilderFolder *root, std::strstream &, const CString& version);
    	void DumpClasses(std::strstream &xml, const CString& ns);
    	void DumpCrossClasses(std::strstream &xml);	
    	void DumpCompositions(std::strstream &xml, const CString& ns);
    	void DumpAssociations(std::strstream &xml, const CString& ns);
    	void DumpCrossAssociations(std::strstream &xml, const CString& ns);
    	bool HasCrossAssociations();
    	void DumpIsolatedAssociations(std::strstream &xml, const CString& ns);
    	static CString GetID();

	protected:
		CString GetFilePath(CBuilder &builder, CBuilderObject *focus, char *FILE_EXT, char *UDM_FILTER);
		bool isUMT;
    };
    
    
    class CClassDiagramBuilder : public CBuilderModel
    {
    	DECLARE_CUSTOMMODEL(CClassDiagramBuilder, CBuilderModel)
    public:
    protected:
    public:
		CString GetNamespace() const;
    	void Build(CCompositeClassList &compositeClasses);
    };
    
	
	class CPackageBuilder : public CBuilderModel
    {
    	DECLARE_CUSTOMMODEL(CPackageBuilder, CBuilderModel)
    public:
		CString GetVersion() const;
    protected:
    public:
    };
    
    
    class CCompositeClass
    {
    	friend class CAssociationBase;
    public:
    	CCompositeClass(CClassBuilder *cls,CBuilderObjectList &copies);
    	
    protected:
    	CClassBuilder *cls;
    	CClassBaseList parts;						// contains cls and all copies
    	CCompositeClassList baseClasses;
    	CCompositeClassList subClasses;
    	CCompositionList childCompositions;			// contains all compositions where this is the parent
    	CCompositionList parentCompositions; 		// contains all compositions where this is a child
    	CAssociationBaseList srcAssociations;
    	CAssociationBaseList dstAssociations;
    	CAssociationBase *association;				// if this is an associationClass
    	bool flag;
    	CString id;

	public:
    	CString GetName();
    	CString GetID()		{ return id; }
    	bool IsAbstract();
    	void SetAssociation(CAssociationBase *assoc)	{ association = assoc; }
    	void FindSubClasses(CBuilderObjectList &triangles);
    	void FindSubClasses();
    	void RegisterSubClasses(CBuilderObjectList &subs);
    	void AddBaseClass(CCompositeClass *base);
    	void AddSubClass(CCompositeClass *sub);
    	bool CheckInheritance(CStringList &trace);
    	void DumpInheritance();
    	void BuildCompositions();
    	CCompositionBuilder *FindEquivalentComposition(CCompositionBuilder *composition);
    	void BuildAssociations();
		void BuildIsoAssociations();
    	void RegisterAssociation(CAssociationBase *assoc,CCompositeClass *dst);
    	void DumpXML(std::strstream &xml, const CString& ns);
    	bool DumpCrossXML(std::strstream &xml, CString& composition_id);
		bool IsCrossClass();				
    };
    
    class CClassBase
    {
    	friend class CCompositeClass;
    public:
    	CClassBase() : composite(0), builder(0), flag(false) {}
	CCompositeClass *composite;
    protected:
    //	CCompositeClass *composite;
    	CBuilderObject *builder;
    	bool flag;
    public:
    	CCompositeClass *GetComposite()		{ return composite; }
    	bool GetFlag()						{ return flag; }
    	void SetFlag(bool val)				{ flag = val; }
		virtual dummy(){};
		virtual CPackageBuilder * GetPackage() = 0;
    
    };
    
    class CClassBuilder : public CBuilderAtom, public CClassBase
    {
    	friend class CCompositeClass;
    	DECLARE_CUSTOMATOM(CClassBuilder, CBuilderAtom)
    protected:
    	CString stereotype;
    	//CAttributeList attrs;
    	//list of attributes parsed by ANTLR
    	std::vector<AttributeObject> attributes;
    	CConstraintBuilderList constraints;
    	CConstraintDefinitionBuilderList constraintdefs;
    
    public:
    	void GetUMLAttributes();
    	void GetConstraints();
    	void GetConstraintDefinitions();
    	virtual void Initialize();
		CPackageBuilder * GetPackage();
		CClassDiagramBuilder * GetClassDiagram();

    };
    
    class CClassCopyBuilder : public CBuilderAtomReference, public CClassBase
    {
    	friend class CCompositeClass;
    	DECLARE_CUSTOMATOMREF(CClassCopyBuilder, CBuilderAtomReference)
    public:
    	virtual void Initialize();
		CPackageBuilder * GetPackage();
    };
    
    class CRole
    {
    public:
    
    	int minc;
    	int maxc;
    	CString cardinality;
    
    	CardinalityObject card;
    	CCompositeClass *cls;
    	CString name;
    	void ParseCardinality();
    	CRole();
    public:
    	CString id;
    public:
    };
    
    class CAttribute
    {
    public:
    	CAttribute() {}
    public:
    	CString attrType;
    	CString defValue;
    public:
    };
    
    class CCompositionBuilder : public CBuilderConnection
    {
    	friend class CCompositeClass;
    	DECLARE_CUSTOMCONNECTION(CCompositionBuilder, CBuilderConnection)
    protected:
    	CRole parent;
    	CRole child;
    public:
    //	CString GetRoleID(CCompositeClass *cls);	//removed, replaced by the next two
    
    	CString GetParentRoleID();
    	CString GetChildRoleID();
    
    	void DumpXML(std::strstream &xml, const CString& ns);
    	virtual void Initialize();
    };
    
    class CAssociationBase
    {
    public:
    	CAssociationBase();
    protected:
    	CRole source;
    	CRole dest;
    	CCompositeClass *associationClass;
    	CString association;
    	CString id;
		const CBuilderModel* parent_classdgr;
    public:
    	CString GetID()		{ return id; }
    	CString GetSrcID()	{ return source.id; }
    	CString GetDstID()	{ return dest.id; }
    	CString GetSrcRoleID(CCompositeClass *cls);
    	CString GetDstRoleID(CCompositeClass *cls);
    	bool IsEquivalent(CAssociationBase *ass);
    	bool IsCrossPackage();
		void DumpXML(std::strstream &xml, const CString& ns);
    	virtual void SetSourceAndDestination(CCompositeClass *s,CCompositeClass *d) = 0;
    	virtual void SetRolesAndCardinalities() = 0;
    };
    
    class CDirectAssociationBuilder : public CBuilderConnection, public CAssociationBase
    {
    	DECLARE_CUSTOMCONNECTION(CDirectAssociationBuilder, CBuilderConnection)
    protected:
    public:
    	virtual void Initialize();
    	void SetSourceAndDestination(CCompositeClass *s,CCompositeClass *d);
    	void SetRolesAndCardinalities();
    };
    
    class CAssociationBuilder : public CBuilderAtom, public CAssociationBase
    {
    	DECLARE_CUSTOMATOM(CAssociationBuilder, CBuilderAtom)
    protected:
    public:
    	virtual void Initialize();
    	void SetSourceAndDestination(CCompositeClass *s,CCompositeClass *d);
    	void SetRolesAndCardinalities();
    };
    
    /*
    class CConstraintBase
    {
    	CString expr;
    	CString desc;
    };
    */
    
    class CConstraintBuilder : public CBuilderAtom
    {
    	DECLARE_CUSTOMATOM(CConstraintBuilder, CBuilderAtom)
    public:
    	CString expr;
    	CString desc;
    	virtual void Initialize();
    	std::strstream& operator >>(std::strstream& out);
    };
    
    class CConstraintDefinitionBuilder : public CBuilderAtom
    {
    	DECLARE_CUSTOMATOM(CConstraintDefinitionBuilder, CBuilderAtom)
    public :
    	CString expr;
    	CString retType;
    	bool stereo;
    	CString paramList;
    	virtual void Initialize();
    	std::strstream& operator >>(std::strstream& out);
    };
    
    #endif // whole file