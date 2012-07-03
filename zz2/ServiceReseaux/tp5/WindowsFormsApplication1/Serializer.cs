using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.IO;
using System.Security.Cryptography;

namespace IHMBook
{
    /// <summary>
    /// Classe de stockage des informations sur l'ihm
    /// </summary>
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

        /// <summary>
        /// Sauvegarde la taille
        /// </summary>
        /// <param name="weight">LArgeur</param>
        /// <param name="height">Hauteur</param>
        /// <param name="splitterdistance">Taille du split</param>
        /// <param name="locX">localisationX</param>
        /// <param name="locY">localisation Y</param>
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
    /// Classe de stockage d'un connection a une base de donnée
    /// </summary>
    public class SaveConnection
    {
        private string _username;
        private string _password;
        private string _IV;
        private string _key;

        public SaveConnection()
        {
        }

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="user">Utilisateur</param>
        /// <param name="password">Mot de passe</param>
        public SaveConnection(string user, string password)
        {
            this._username = user;
            this._password = password;
        }

        public string Username
        {
            get { return _username; }
            set { _username = value; }
        }

        public string Password
        {
            get { return _password; }
            set { _password = value; }
        }

        public string IV
        {
            get { return _IV; }
            set { _IV = value; }
        }

        public string Key
        {
            get { return _key; }
            set { _key = value; }
        }
    }


    /// <summary>
    /// Le but de cette classe est de serialiser l'apparance de la fenetre 
    /// - les dimensions de la fenetre
    /// - le rapport entre le treeview et le user control
    /// </summary>

    public class Serializer
    {
        public void SerialiserFenetre(int weight, int height, int splitterdistance, int locX, int locY)
        {
            SaveForm save = new SaveForm(weight, height, splitterdistance, locX, locY);

            XmlSerializer serializer = new XmlSerializer(typeof(SaveForm));
            TextWriter writer = new StreamWriter("IHM_serialisation.xml");

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
                FileStream fs = new FileStream("IHM_serialisation.xml", FileMode.Open); //TODO modifier le fichier
                TextReader reader = new StreamReader(fs);
                save = (SaveForm)serializer.Deserialize(reader);
                reader.Close();
                return save;
            }
            catch (FileNotFoundException)
            {
                return null;
            }
        }

        public void SerialiserConnectBDD(string username, string password)
        {

            SaveConnection save = new SaveConnection(username, password);

            TripleDESCryptoServiceProvider sa = new TripleDESCryptoServiceProvider();
            save.IV = Convert.ToBase64String(sa.IV);
            save.Key = Convert.ToBase64String(sa.Key);
            save.Username = username;

            ICryptoTransform ct; MemoryStream ms; CryptoStream cs; byte[] byt;
            ct = sa.CreateEncryptor(sa.Key, sa.IV);
            byt = Encoding.UTF8.GetBytes(password);
            ms = new MemoryStream();
            cs = new CryptoStream(ms, ct, CryptoStreamMode.Write);
            cs.Write(byt, 0, byt.Length);
            cs.FlushFinalBlock();
            cs.Close();
            save.Password = Convert.ToBase64String(ms.ToArray());

            XmlSerializer serializer = new XmlSerializer(typeof(SaveConnection));
            TextWriter writer = new StreamWriter("Connection_serialisation.xml");

            serializer.Serialize(writer, save);
            writer.Close();
        }

        public SaveConnection DeserialiserConnectBDD()
        {
            try
            {
                SaveConnection save;
                XmlSerializer serializer = new XmlSerializer(typeof(SaveConnection));
                //tentative d'ouverture du fichier
                FileStream fs = new FileStream("Connection_serialisation.xml", FileMode.Open); //TODO modifier le fichier
                TextReader reader = new StreamReader(fs);
                save = (SaveConnection)serializer.Deserialize(reader);
                reader.Close();

                TripleDESCryptoServiceProvider sa = new TripleDESCryptoServiceProvider();
                ICryptoTransform ct; MemoryStream ms; CryptoStream cs; byte[] byt;
                sa.IV = Convert.FromBase64String(save.IV);
                sa.Key = Convert.FromBase64String(save.Key);

                ct = sa.CreateDecryptor(sa.Key, sa.IV);
                byt = Convert.FromBase64String(save.Password);
                ms = new MemoryStream();
                cs = new CryptoStream(ms, ct, CryptoStreamMode.Write);
                cs.Write(byt, 0, byt.Length);
                cs.FlushFinalBlock();
                cs.Close();
                save.Password = Encoding.UTF8.GetString(ms.ToArray());
                return save;
            }
            catch (FileNotFoundException)
            {
                return null;
            }
        }
    }
}
