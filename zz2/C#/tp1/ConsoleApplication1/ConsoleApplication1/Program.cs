using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace tp1_signature_message
{
    class Program
    {
        static void Main(string[] args)
        {
            Server s = new Server();
            Client cl = new Client("Jc", s);
            Client c2 = new Client("Max", s);
            Client c3 = new Client("Gui", s);
            cl.Envoyer("salut");
            c2.Envoyer("salut");
            c3.Envoyer("Salut a vous!!!");
            c2.Envoyer("Ca va les copains?");
            Console.Read();

        }
    }
}
