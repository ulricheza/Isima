using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Security.Cryptography;
using System.IO;
using Serveur;

namespace UnitTest
{
    [TestClass]
    public class UnitTestReceiveMessageUnread
    {
        [TestMethod]
        public void TestMethodReceiveMessageUnread()
        {
            DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();
            DSAParameters publickey = mycrypto.ExportParameters(false);

            ASCIIEncoding encoding = new ASCIIEncoding();
            byte[] hash = mycrypto.SignData(encoding.GetBytes("Cuddy"));
            ServiceReference1.ServeurChatSoapClient a = new ServiceReference1.ServeurChatSoapClient();

            string message = "je suis jalouse de Cameron";
            byte[] messagesigned = mycrypto.SignData(encoding.GetBytes(message));
            
            a.Register("Cuddy", "iluvhouse", hash, publickey.Counter, publickey.G, publickey.J, publickey.P, publickey.Q, publickey.Seed, publickey.X, publickey.Y);
            a.SendMessage("Cuddy", message, messagesigned);

            UnitTest.ServiceReference1.Message[] b = a.ReceiveMessageNonRead("Cuddy", hash);
            
            Assert.AreEqual("je suis jalouse de Cameron", b[0].Text); //meme commentaire que pour les messages prives
            Assert.AreEqual("Cuddy", b[0].Auteur);

            File.Delete("C:\\Program Files\\Common Files\\microsoft shared\\DevServer\\10.0\\Message_serialization.xml");
            File.Delete("C:\\Program Files\\Common Files\\microsoft shared\\DevServer\\10.0\\User_serialization.xml");
        }
    }
}
