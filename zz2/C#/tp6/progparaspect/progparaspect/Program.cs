using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using PostSharp.Aspects;
using PostSharp;
using System.Diagnostics;

namespace progparaspect
{

    class TestAOP
    {
        static void Main(string[] args)
        {
            
            Trace.Listeners.Add(new TextWriterTraceListener(Console.Out));
            TestAOP test = new TestAOP();
            test.GreetAll(new string[] { "toto", "tata", "toto", "tutu", "toto" });
            Console.WriteLine(test.GetGreetings(null));
            Console.ReadLine();
        }

        []
        void GreetAll(IEnumerable<string> names)
        {
            foreach (string name in names)
            {
                Console.WriteLine(GetGreetings(name));
            }
        }


        [Trace()]
        string GetGreetings(string name)
        {
            return String.Format("Hello {0}!", name);
        }
    }
}
