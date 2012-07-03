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
    public class UnitTestChangeNick
    {
        [TestMethod]
        public void TestMethodCHangeNick()
        {
            DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();
            DSAParameters Publickey = mycrypto.ExportParameters(false);
            ASCIIEncoding encoding = new ASCIIEncoding();
            byte[] hash = mycrypto.SignData(encoding.GetBytes("Cuddy"));
            ServiceReference1.ServeurChatSoapClient a = new ServiceReference1.ServeurChatSoapClient();

            a.Register("Cuddy", "passbidon", hash, Publickey.Counter, Publickey.G, Publickey.J, Publickey.P, Publickey.Q, Publickey.Seed, Publickey.X, Publickey.Y);
            Assert.AreEqual(true, a.ChangeNick("Cuddy", "MissC", mycrypto.SignData(encoding.GetBytes("MissC"))));
            hash = mycrypto.SignData(encoding.GetBytes("MissC"));
            Assert.AreEqual(true, a.LogIn("MissC", "passbidon", hash, Publickey.Counter, Publickey.G, Publickey.J, Publickey.P, Publickey.Q, Publickey.Seed, Publickey.X, Publickey.Y));
        }
    }
}
