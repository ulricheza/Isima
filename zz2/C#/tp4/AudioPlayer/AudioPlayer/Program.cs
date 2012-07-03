using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AudioPlayer
{
    class Program
    {
        static void Main(string[] args)
        {
            Player p = new Player();
            p.Play(".\\AudioTest.xml");
            Console.ReadLine();
        }
    }
}
