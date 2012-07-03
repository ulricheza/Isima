using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Serveur;
using System.Security.Cryptography;
using System.IO;

namespace UnitTest
{
    /// <summary>
    /// Description résumée pour UnitTestSendMessage
    /// </summary>
    [TestClass]
    public class UnitTestSendMessage
    {
        [TestMethod]
        public void TestMethodSendMessage()
        {
            DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();
            DSAParameters publickey = mycrypto.ExportParameters(false);
            DSACryptoServiceProvider petitmalin = new DSACryptoServiceProvider();
            DSAParameters Clemoisi = petitmalin.ExportParameters(false);

            ASCIIEncoding encoding = new ASCIIEncoding();
            ServiceReference1.ServeurChatSoapClient a = new ServiceReference1.ServeurChatSoapClient();

            byte[] hash = mycrypto.SignData(encoding.GetBytes("Cuddy"));
            string message = "je suis jalouse de Cameron";
            
            
            a.Register("Cuddy", "iluvhouse", hash, publickey.Counter, publickey.G, publickey.J, publickey.P, publickey.Q, publickey.Seed, publickey.X, publickey.Y);

            byte[] messagesigned = mycrypto.SignData(encoding.GetBytes(message));
            Assert.AreEqual(true, a.SendMessage("Cuddy", message, messagesigned));

            byte[] hashmoisi = petitmalin.SignData(encoding.GetBytes(message));
            Assert.AreEqual(false, a.SendMessage("Cuddy",message,hashmoisi));

            File.Delete("C:\\Program Files\\Common Files\\microsoft shared\\DevServer\\10.0\\Message_serialization.xml");
            File.Delete("C:\\Program Files\\Common Files\\microsoft shared\\DevServer\\10.0\\User_serialization.xml");
        }
    }
}
