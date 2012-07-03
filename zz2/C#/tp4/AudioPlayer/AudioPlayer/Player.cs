using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace AudioPlayer
{
    public class Player
    {
        public Player()
        {

        }

        public void Play(string fichier)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(fichier);
            XmlElement elmnt = doc.DocumentElement;
            XmlNode data = elmnt.FirstChild;
            XmlNode flux = data.FirstChild;
            Console.WriteLine(flux.Value);
        }
    }
}
