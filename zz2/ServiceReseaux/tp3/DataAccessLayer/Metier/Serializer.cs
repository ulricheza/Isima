using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.IO;

namespace DataAccessLayer.Metier
{

    public class SaveForm
    {
        //attributs
        private int _weightform;
        private int _heightform;
        private int _splitterdistance;

        //constructeur
        public SaveForm()
        {
        }

        public SaveForm(int weight, int height, int splitterdistance)
        {
            _weightform = weight;
            _heightform = height;
            _splitterdistance = splitterdistance;
        }
        
        //Proprietes
        public int Weightform
        {
            get { return _weightform; }
            set { _weightform = value; }
        }

        public int Heightform
        {
            get { return _heightform; }
            set { _heightform = value; }
        }

        public int Splitterdistance
        {
            get { return _splitterdistance; }
            set { _splitterdistance = value; }
        }

    }

    /// <summary>
    /// Le but de cette classe est de serialiser l'apparance de la fenetre 
    /// - les dimensions de la fenetre
    /// - le rapport entre le treeview et le user control
    /// </summary>
      
    public class Serializer
    {
        //methodes
        public void SerialiserFenetre(int weight, int height, int splitterdistance)
        {
            SaveForm save = new SaveForm(weight,height,splitterdistance);

            XmlSerializer serializer = new XmlSerializer(typeof(SaveForm));
            TextWriter writer = new StreamWriter("fichier_temp.xml");

            serializer.Serialize(writer, save);
            writer.Close();
        }

        public SaveForm DeserialiserFenetre()
        {
            try
            {
                XmlSerializer serializer = new XmlSerializer(typeof(SaveForm));
                //tentative d'ouverture du fichier
                FileStream fs = new FileStream("fichier_temp.xml", FileMode.Open);
                TextReader reader = new StreamReader(fs);
                return ((SaveForm)serializer.Deserialize(reader));
            }
            catch (FileNotFoundException e)
            {
                return null;
            }

        }
    }
}
