using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.IO;

namespace IHMBook
{

    public class SaveForm
    {
        //attributs
        private int _weightform;
        private int _heightform;
        private int _splitterdistance;
        private int _localisationX;
        private int _localisationY;


        //TODO Rajouter d'autres elements de serialisation

        //constructeur
        public SaveForm()
        {
        }

        public SaveForm(int weight, int height, int splitterdistance, int locX, int locY)
        {
            _weightform = weight;
            _heightform = height;
            _splitterdistance = splitterdistance;
            _localisationX = locX;
            _localisationY = locY;
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

        public int LocalisationX
        {
            get { return _localisationX; }
            set { _localisationX = value; }
        }

        public int LocalisationY
        {
            get { return _localisationY; }
            set { _localisationY = value; }
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
        public void SerialiserFenetre(int weight, int height, int splitterdistance, int locX, int locY)
        {
            SaveForm save = new SaveForm(weight,height,splitterdistance,locX,locY);

            XmlSerializer serializer = new XmlSerializer(typeof(SaveForm));
            TextWriter writer = new StreamWriter("fichier_temp.xml"); //TODO modifier le fichier
             
            serializer.Serialize(writer, save);

            writer.Close();
        }

        public SaveForm DeserialiserFenetre()
        {
            try
            {
                SaveForm save;
                XmlSerializer serializer = new XmlSerializer(typeof(SaveForm));
                //tentative d'ouverture du fichier
                FileStream fs = new FileStream("fichier_temp.xml", FileMode.Open); //TODO modifier le fichier
                TextReader reader = new StreamReader(fs);
                save = (SaveForm)serializer.Deserialize(reader);
                reader.Close();
                return save;
            }
            catch (FileNotFoundException e)
            {
                return null;
            }

        }
    }
}
