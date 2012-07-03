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
    /// Description résumée pour UnitTestSendPrivateMessage
    /// </summary>
    [TestClass]
    public class UnitTestSendPrivateMessage
    {
        [TestMethod]
        public void TestMethodSendPrivateMessage()
        {
            ASCIIEncoding encoding = new ASCIIEncoding();
            
            DSACryptoServiceProvider mycryptoC = new DSACryptoServiceProvider();
            DSAParameters publickeyC = mycryptoC.ExportParameters(false);

            DSACryptoServiceProvider mycryptoW = new DSACryptoServiceProvider();
            DSAParameters publickeyW = mycryptoW.ExportParameters(false);

            byte[] hashC = mycryptoC.SignData(encoding.GetBytes("Cuddy"));
            byte[] hashW = mycryptoW.SignData(encoding.GetBytes("Wilson"));

            ServiceReference1.ServeurChatSoapClient a = new ServiceReference1.ServeurChatSoapClient();
            

            a.Register("Cuddy", "iluvhouse", hashC, publickeyC.Counter, publickeyC.G, publickeyC.J, publickeyC.P, publickeyC.Q, publickeyC.Seed, publickeyC.X, publickeyC.Y);
            a.Register("Wilson", "ihatehouse", hashW, publickeyW.Counter, publickeyW.G, publickeyW.J, publickeyW.P, publickeyW.Q, publickeyW.Seed, publickeyW.X, publickeyW.Y);

            string message = "je suis jalouse de Cameron";
            byte[] messagesigned = mycryptoC.SignData(encoding.GetBytes(message));
            
            Assert.AreEqual(true,a.SendPrivateMessage("Cuddy", "Wilson", message, messagesigned));
            Assert.AreEqual(false, a.SendPrivateMessage("Cuddy", "Foreman", message, messagesigned));
            
            File.Delete("C:\\Program Files\\Common Files\\microsoft shared\\DevServer\\10.0\\Message_serialization.xml");
            File.Delete("C:\\Program Files\\Common Files\\microsoft shared\\DevServer\\10.0\\User_serialization.xml");
        }
    }
}
