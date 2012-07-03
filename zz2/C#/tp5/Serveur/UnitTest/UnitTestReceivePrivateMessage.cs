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
    public class UnitTestReceivePrivateMessage
    {
        [TestMethod]
        public void TestMethodReceivePrivateMessage()
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

            a.SendPrivateMessage("Cuddy", "Wilson", message, messagesigned);
            UnitTest.ServiceReference1.Message[] b = a.ReceivePrivateMessage("Wilson", hashW);

            Assert.AreEqual("Cuddy", b[0].Auteur); //j'avoue les test sont moisi... mais je voulais juste verifier si le retour par une classe implemente dans le webservice etait possible
            Assert.AreEqual("je suis jalouse de Cameron", b[0].Text);

            File.Delete("C:\\Program Files\\Common Files\\microsoft shared\\DevServer\\10.0\\Message_serialization.xml");
            File.Delete("C:\\Program Files\\Common Files\\microsoft shared\\DevServer\\10.0\\User_serialization.xml");
            
        }
    }
}
