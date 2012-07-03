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
    [TestClass]
    public class UnitTestConnexion
    {
        [TestMethod]
        public void TestMethodRegisterAndLogin()
        {
            DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();
            DSAParameters Publickey = mycrypto.ExportParameters(false);
            ASCIIEncoding encoding = new ASCIIEncoding();
            byte[] hash = mycrypto.SignData(encoding.GetBytes("Cuddy"));
            ServiceReference1.ServeurChatSoapClient a = new ServiceReference1.ServeurChatSoapClient();

            Assert.AreEqual(true, a.Register("Cuddy", "passbidon",hash, Publickey.Counter, Publickey.G, Publickey.J, Publickey.P, Publickey.Q, Publickey.Seed, Publickey.X, Publickey.Y));
            Assert.AreEqual(false, a.Register("Cuddy", "rate",hash, Publickey.Counter, Publickey.G, Publickey.J, Publickey.P, Publickey.Q, Publickey.Seed, Publickey.X, Publickey.Y));

            Assert.AreEqual(true,a.LogIn("Cuddy", "passbidon",hash, Publickey.Counter, Publickey.G, Publickey.J, Publickey.P, Publickey.Q, Publickey.Seed, Publickey.X, Publickey.Y));
            Assert.AreEqual(false, a.LogIn("Cuddy", "badpass",hash, Publickey.Counter, Publickey.G, Publickey.J, Publickey.P, Publickey.Q, Publickey.Seed, Publickey.X, Publickey.Y));

            //remise a zero du serveur
            File.Delete("C:\\Program Files\\Common Files\\microsoft shared\\DevServer\\10.0\\Message_serialization.xml");
            File.Delete("C:\\Program Files\\Common Files\\microsoft shared\\DevServer\\10.0\\User_serialization.xml");
            
        }
    }
}
