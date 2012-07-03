using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Serveur;
using System.Security.Cryptography;

namespace UnitTest
{
    [TestClass]
    public class TestSerialisation
    {
        [TestMethod]
        public void TestMethodSerialization()
        {
            //on simule l'ajout d'auteur
            User aut1 = new User("Toto", "mypass1");
            User aut2 = new User("JC", "mypass2");
            User aut3 = new User("Max", "mypass3");
            User aut4 = new User("Titi", "clearstream");
            User aut5 = new User("Toadd", "serie");

            DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();
            DSAParameters key = mycrypto.ExportParameters(false);
            aut1.Publickey = key;
            aut2.Publickey = key;
            aut3.Publickey = key;
            aut4.Publickey = key;
            aut5.Publickey = key;


            Message mess1 = new Message(aut1.Login, "Coucou ca va?");
            Message mess2 = new Message(aut2.Login, "oue et toi?");
            Message mess3 = new Message(aut3.Login, "tranquille!");
            Message mess4 = new Message(aut1.Login, "ca va ca va");
            Message mess5 = new Message(aut5.Login, "Test fifi");
            Message mess6 = new Message(aut5.Login, "MessagePrive: cool ma poule?");

            aut1.AddPrivateMessage(mess6);

            //on simule
            Chat toTest = new Chat();
            Chat toOut =  new Chat();
            toTest.AddUser(aut1);
            toTest.AddUser(aut2);
            toTest.AddUser(aut3);
            toTest.AddUser(aut4);
            toTest.AddMessage(mess1);
            toTest.AddMessage(mess2);
            toTest.AddMessage(mess3);
            toTest.AddMessage(mess4);

            toTest.Serialiser();
            toOut.Deserialiser();
            toOut.AddUser(aut5);
            toOut.AddMessage(mess5);
            toOut.Serialiser();
            //l'analyse du test se fera manuellement dans le fichier de sortie
        }
    }
}