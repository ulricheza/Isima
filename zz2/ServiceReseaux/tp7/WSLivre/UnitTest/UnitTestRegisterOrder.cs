using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace UnitTest
{
    [TestClass]
    public class UnitTestRegisterOrder
    {
        [TestMethod]
        public void TestMethodRegisterOrder()
        {
            ServiceIsimaBook.ServiceIsimaBookSoapClient service = new ServiceIsimaBook.ServiceIsimaBookSoapClient();
            ServiceIsimaBook.Book[] libtest = service.AllBooks();
            ServiceIsimaBook.Book[] libtopurchase = new ServiceIsimaBook.Book[3];
            libtopurchase[0] = libtest[0];
            libtopurchase[1] = libtest[1];
            libtopurchase[2] = libtest[2];
            ServiceIsimaBook.ContactDetails address = new ServiceIsimaBook.ContactDetails();
            address.Name = "Maxime Escourbiac";
            address.Adress = "37 Rue Gonod";
            address.City = "Clermont-Ferrand";
            address.Zipcode = "63000";
            
            //test correct
            Assert.AreNotEqual(null,service.RegisterOrder(libtopurchase, "4975786139455718", address, address));

            //test avec mauvaise carte de credit
            Assert.AreEqual(null, service.RegisterOrder(libtopurchase, "4975786139455729", address, address));
            
            //test livre non present dans la bibliotheque
            libtopurchase[0].Title = "Faux Titre ;)";
            Assert.AreEqual(null, service.RegisterOrder(libtopurchase, "4975786139455718", address, address));

           
        }
    }
}
