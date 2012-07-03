using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Reflection;
namespace tp3
{
    class HashTableReflection
    {

        public Hashtable table;

        public HashTableReflection()
        {
            table = new Hashtable();
        }

        public void Remplir()
        {
            foreach (Assembly asm in AppDomain.CurrentDomain.GetAssemblies())
            {
                if (asm.GetName().Name == "tp3")
                {
                    foreach (Type ty in asm.GetTypes())
                    {
                        foreach (MethodInfo mi in ty.GetMethods())
                        {
                            if(mi.GetParameters().Count<ParameterInfo>() == 0)
                                table.Add(mi.Name, new Pair<MethodInfo, Object>(mi,new ));
                        } 
                    }
                }
            }
        }


    }
}
