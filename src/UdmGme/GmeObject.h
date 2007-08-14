

/*

22/11/04	-	endre

			-	VC7.1 .net porting issues

24/09/04	-	endre

			- removed global variable amap and global function amapInitialize and placed as a member of GmeDataNetwork.
			Each GmeDataNetwork has it's own version of amap. This was required because GME wanted to have the meta objects released
			at the time of closing the project.


13/07/04	-	endre

			-   addressed feature request UDM-6 regarding reference ports.

05/05/04	-	endre

		changing assocmapitem structure to include metaobjs and metaobjs_count,
		if an association can not be mapped to one GME connection 
		(case of abstract supertype association classes)

03/15/04	-	endre
		
		  Changing the syntax of createchild() as required by Udm::ObjectImpl
*/
#ifndef MOBIES_GME_OBJECT_H
#define MOBIES_GME_OBJECT_H



namespace UdmGme 
{
	typedef Udm::Object Object;
	typedef Udm::ObjectImpl ObjectImpl;
	typedef Udm::DataNetwork DataNetwork;
	typedef ObjectImpl::uniqueId_type uniqueId_type;

	typedef list<GmeDataNetwork *> gdnmap; 


	static gdnmap GDNMap;


	void com_exception(HRESULT a, IUnknown *b, REFIID c);
	string getnameforassoc(const ::Uml::Uml::Association &ass, bool generate_name);

	//class GmeObject

	class GmeObject : public ObjectImpl 
	{
		friend void GmeDataNetwork::CreateNew(const string &systemname, 
			const string &metalocator, const ::Uml::Uml::Class &rootclass, 
									enum Udm::BackendSemantics sem);
		IMgaFCOPtr self;
		IMgaFolderPtr folderself;
		::Uml::Uml::Class m_type;
		uniqueId_type __uniqueId;
		bool __uniqueId_set;
		const DataNetwork * mydn;
		
		void RemoveHelperConnections();

	public:
		GmeObject(const ::Uml::Uml::Class &meta, IMgaFCO *obj, const DataNetwork * dn);
		GmeObject( IMgaFCO *obj, const DataNetwork * dn);
		GmeObject(const ::Uml::Uml::Class &meta, IMgaFolder *obj, const DataNetwork * dn);	
		GmeObject( IMgaFolder *obj, const DataNetwork * dn);

	// --- reference counting

		virtual ObjectImpl *clone();
		virtual void release();
		virtual Udm::DataNetwork *__getdn();

	// --- lookup

		//Uml::Class findClass(const set<Uml::Class> &classes);
		::Uml::Uml::Class findClass();
		IMgaMetaFCOPtr MetaFCO() const;
		IMgaMetaBasePtr Meta() const;
		virtual const ::Uml::Uml::Class &type() const;

	// --- order

		uniqueId_type __set_uniqueId(uniqueId_type id) const;
		virtual uniqueId_type uniqueId() const;
		
	// --- attributes, single values

		virtual string getStringAttr(const ::Uml::Uml::Attribute &meta) const;
		virtual void setStringAttr(const ::Uml::Uml::Attribute &meta, const string &a, const bool direct = true);
		virtual bool getBooleanAttr(const ::Uml::Uml::Attribute &meta) const;
		virtual void setBooleanAttr(const ::Uml::Uml::Attribute &meta, bool a, const bool direct = true);
		virtual __int64 getIntegerAttr(const ::Uml::Uml::Attribute &meta) const;
		virtual void setIntegerAttr(const ::Uml::Uml::Attribute &meta, __int64 a, const bool direct = true);
		virtual double getRealAttr(const ::Uml::Uml::Attribute &meta) const;
		virtual void setRealAttr(const ::Uml::Uml::Attribute &meta, double a, const bool direct = true);
	
	
	// array attribute setters/getters are wrapped in ObjectImpl 
	// relaying on set/get StringAttr




		static IMgaMetaRolePtr GetMetaRoleForChildRole(::Uml::Uml::CompositionChildRole meta, IMgaMetaModelPtr mmodel);
//		static IMgaMetaRolePtr GetMetaRoleForKind(Uml::Class kind, IMgaMetaModelPtr mmodel);		
		static IMgaMetaRolePtr GetMetaRole(::Uml::Uml::Class kind, ::Uml::Uml::CompositionChildRole meta, IMgaMetaModelPtr mmodel);

	// --- containment

		virtual ObjectImpl *getParent(const ::Uml::Uml::CompositionParentRole &role) const;		
		virtual void setParent(ObjectImpl *a, const ::Uml::Uml::CompositionParentRole &role, const bool direct = true);
		virtual void detach();


// if meta is given, return only those which have that role
// if meta is not given, return all children, which are compatible with kind
		virtual vector<ObjectImpl*> getChildren(const ::Uml::Uml::CompositionChildRole &role, const ::Uml::Uml::Class &kind) const;
		virtual void setChildren(const ::Uml::Uml::CompositionChildRole &role, const vector<ObjectImpl*> &a, const bool direct = true); 
		virtual ObjectImpl *createChild(
			const ::Uml::Uml::CompositionChildRole &role,	
			const ::Uml::Uml::Class &kind, 
			const Udm::ObjectImpl* archetype = NULL, 
			const bool subtype = false,
			const bool real_archetype = true,
			const bool need_safetype = false);		//this is not used, since this call
										//does not recurse when a a derived/instace
										//object is created with an archetype that has children
										//(this is done by the underlaying MGA layer
	// --- associations


//prepare:  we have 2 MetaFCO-s
//			go through all metaconnections
//				that have matching tokens in sName dName
//				check if ends specified by the joints are all derived from the end specified by the UML end class roles
//				check if any of the joints match
// only one valid can exist

		virtual vector<ObjectImpl*> getAssociation(const ::Uml::Uml::AssociationRole &meta, int mode) const ;
		virtual void setAssociation(const ::Uml::Uml::AssociationRole &meta, const vector<ObjectImpl*> &nvect, int mode, const bool direct = true);
	// ---- archetype/derived/instances

		virtual vector<ObjectImpl*> getDerived() const;
		virtual vector<ObjectImpl*> getInstances() const;
		virtual ObjectImpl* getArchetype() const;
		virtual bool hasRealArchetype() const;
		virtual bool isSubtype() const;

		virtual bool isInstance() const;
	
	
	// ---- connection through refport - hack
		IMgaFCOsPtr FindReferencesToFCO(const IMgaFCOPtr& peer, const IMgaFCOPtr& preffered_ref = NULL) const;

	};

};
	
#endif 