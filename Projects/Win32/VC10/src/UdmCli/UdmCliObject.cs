using System;
using System.Collections.Generic;
using System.Text;

namespace Udm.Cli
{
    public class UdmCliObject : IUdmCliObject
    {
        public Udm.Native.UdmObject backing;

        public UdmCliObject(Udm.Native.UdmObject o)
        {
            backing = o;
        }
        public UdmCliObject(Udm.Native.ObjectImpl o)
        {
            backing = new Udm.Native.UdmObject(o);
        }
        public static void CheckCast(Udm.Native.UdmObject a, Udm.Native.Uml.Class meta)
        {
            if (!Udm.Native.Udm.IsDerivedFrom(a.type(), meta))
            {
                throw new Udm.Native.UdmException("Invalid cast from type '" + a.type().name().Get() + "' to type '" + meta.name().Get() + "'");
            }
        }
        public int id
        {
            get { return backing.uniqueId(); }
        }
        public string type_name
        {
            get { return backing.type().name().Get(); }
        }
        public Udm.Native.Uml.Class type
        {
            get { return backing.type(); }
        }
        public IUdmCliObject parent
        {
            get { return new UdmCliObject(backing.GetParent()); }
        }
        public bool isInstance
        {
            get { return backing.isInstance(); }
        }
        public bool isSubtype
        {
            get { return backing.isSubtype(); }
        }
        public IUdmCliObject archetype
        {
            get
            {
                Udm.Native.UdmObject o = backing.archetype();
                if (o.uniqueId() == 0) return null;
                return new UdmCliObject(o);
            }
        }
        public System.Collections.Generic.IEnumerable<IUdmCliObject> instances
        {
            get
            {
                return System.Linq.Enumerable.ToList(
                    System.Linq.Enumerable.Select<Udm.Native.UdmObject, IUdmCliObject>
                    (backing.instances(), o => new UdmCliObject(o)));
            }
        }
        public System.Collections.Generic.IEnumerable<IUdmCliObject> derived
        {
            get
            {
                return System.Linq.Enumerable.ToList(
                    System.Linq.Enumerable.Select<Udm.Native.UdmObject, IUdmCliObject>
                    (backing.derived(), o => new UdmCliObject(o)));
            }
        }
    }
    public interface IUdmCliObject
    {
        int id { get; }
        // TODO: should be Class inherited from IUdmCliObject
        Udm.Native.Uml.Class type { get; }
        IUdmCliObject parent { get; }

        bool isInstance { get; }
        bool isSubtype { get; }
        IUdmCliObject archetype { get; }
        System.Collections.Generic.IEnumerable<IUdmCliObject> instances { get; }
        System.Collections.Generic.IEnumerable<IUdmCliObject> derived { get; }
    }
}
