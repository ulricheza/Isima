using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using UnitTest.ServiceIsimaBook;

namespace UnitTest
{
    [TestClass]
    public class TestVerifyCreditCard
    {
        [TestMethod]
        public void TestMethodVerifyCreditCard()
        {
            ServiceIsimaBook.ServiceIsimaBookSoapClient service = new ServiceIsimaBook.ServiceIsimaBookSoapClient();
            Assert.AreEqual(true, service.VerifyCreditCard("4970402494684638"));
            Assert.AreEqual(true, service.VerifyCreditCard("4975786139455718"));
            Assert.AreEqual(false, service.VerifyCreditCard("4975402499654738"));
            Assert.AreEqual(false, service.VerifyCreditCard("1234ABCD"));
        }
    }
}
