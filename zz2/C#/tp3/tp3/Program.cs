using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace tp3
{
    class Program
    {
        static void Main(string[] args)
        {
            // Question 1
            foreach (Assembly asm in AppDomain.CurrentDomain.GetAssemblies())
            {
                if (asm.GetName().Name == "tp3")
                {
                    foreach (Type ty in asm.GetTypes())
                    {
                        Console.WriteLine(" Classe : " + ty);
                        foreach (MethodInfo mi in ty.GetMethods())
                        {
                            Console.WriteLine(" Methode : " + mi);
                            foreach (ParameterInfo pi in mi.GetParameters())
                                Console.WriteLine("Parametre : " + pi.GetType());
                        }
                    }
                }
            }

            // Question 2
            Console.WriteLine();
            Pair<int, char> p = new Pair<int, char>(5, 'c');
            Console.WriteLine("Paire:" + p.El1 + " " + p.El2);

            // Question 3

            HashTableReflection tab = new HashTableReflection();

            Console.ReadLine();
        }
    }
}
