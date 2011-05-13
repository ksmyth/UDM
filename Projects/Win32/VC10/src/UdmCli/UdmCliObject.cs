using System;
using System.Collections.Generic;
using System.Text;
using Udm.Native;
using Udm.Native.Uml;

namespace Udm.Native
{
    public class UdmCliObject : IUdmObject
    {
        public UdmObject backing;

        public UdmCliObject(UdmObject o)
        {
            backing = o;
        }
        public UdmCliObject(ObjectImpl o)
        {
            backing = new UdmObject(o);
        }
        public static void CheckCast(UdmObject a, Uml.Class meta)
        {
            if (!Udm.IsDerivedFrom(a.type(), meta))
            {
                throw new UdmException("Invalid cast from type '" + a.type().name().Get() + "' to type '" + meta.name().Get() + "'");
            }
        }
        public int id
        {
            get { return backing.uniqueId(); }
        }
        public bool Equals(UdmCliObject that)
        {
            return this.id == that.id;
        }
        public override bool Equals(object that)
        {
            if (that as UdmCliObject != null)
            {
                return Equals((UdmCliObject)that);
            }
            return false;
        }
        public override int GetHashCode()
        {
            return id;
        }
        public string type_name
        {
            get { return backing.type().name().Get(); }
        }
        public Uml.Class type
        {
            get { return backing.type(); }
        }
        public IUdmObject parent
        {
            get { return new UdmCliObject(backing.GetParent()); }
        }
        public System.Collections.Generic.IEnumerable<IUdmObject> children
        {
            get
            {
                return System.Linq.Enumerable.ToList(
                    System.Linq.Enumerable.Select<UdmObject, IUdmObject>
                    (backing.GetChildObjects(), o => new UdmCliObject(o)));
            }
        }
        public bool isInstance
        {
            get { return backing.isInstance(); }
        }
        public bool isSubtype
        {
            get { return backing.isSubtype(); }
        }
        public IUdmObject archetype
        {
            get
            {
                UdmObject o = backing.archetype();
                if (o.uniqueId() == 0) return null;
                return new UdmCliObject(o);
            }
        }
        public System.Collections.Generic.IEnumerable<IUdmObject> instances
        {
            get
            {
                return System.Linq.Enumerable.ToList(
                    System.Linq.Enumerable.Select<UdmObject, IUdmObject>
                    (backing.instances(), o => new UdmCliObject(o)));
            }
        }
        public System.Collections.Generic.IEnumerable<IUdmObject> derived
        {
            get
            {
                return System.Linq.Enumerable.ToList(
                    System.Linq.Enumerable.Select<UdmObject, IUdmObject>
                    (backing.derived(), o => new UdmCliObject(o)));
            }
        }
    }
}
namespace Udm
{
public interface IUdmObject
    {
        int id { get; }
        // TODO: should be Class inherited from IUdmObject
        Udm.Native.Uml.Class type { get; }
        IUdmObject parent { get; }
        System.Collections.Generic.IEnumerable<IUdmObject> children { get; }

        bool isInstance { get; }
        bool isSubtype { get; }
        IUdmObject archetype { get; }
        System.Collections.Generic.IEnumerable<IUdmObject> instances { get; }
        System.Collections.Generic.IEnumerable<IUdmObject> derived { get; }
    }
}
