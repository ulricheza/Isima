using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace UnitTest
{
    [TestClass]
    public class UnitTestConvertEuroTo
    {
        [TestMethod]
        public void TestMethodConvertEuroTo()
        {
            ServiceIsimaBook.ServiceIsimaBookSoapClient service = new ServiceIsimaBook.ServiceIsimaBookSoapClient();
            CurrencyConvertorUnitTest.CurrencyConvertorSoapClient serv = new CurrencyConvertorUnitTest.CurrencyConvertorSoapClient();
            double priceSterling = 10 * serv.ConversionRate(CurrencyConvertorUnitTest.Currency.EUR, CurrencyConvertorUnitTest.Currency.GBP);
            double priceDollar = 10 * serv.ConversionRate(CurrencyConvertorUnitTest.Currency.EUR, CurrencyConvertorUnitTest.Currency.USD);
            Assert.AreEqual(priceSterling, service.ConvertEuroTo(10.0, ServiceIsimaBook.Currency.GBP));
            Assert.AreEqual(priceDollar, service.ConvertEuroTo(10.0, ServiceIsimaBook.Currency.USD));
        }
    }
}
