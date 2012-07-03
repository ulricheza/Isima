using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;


namespace tp1_signature_message
{
    public class Client
    {
        //attribut
        private string _pseudo;
        private DSAParameters _publicKey;
        private Server _myServer;
        private String _signature;
        private DSACryptoServiceProvider mycrypto;

        //constructeur
        public Client(string pseudo, Server s)
        {
            _pseudo = pseudo;
            _myServer = s;
            Enregister();
        }

        private void Enregister()
        {
            mycrypto = new DSACryptoServiceProvider();
            ASCIIEncoding encoding = new ASCIIEncoding();

            _publicKey = mycrypto.ExportParameters(false);
            byte[] tab = encoding.GetBytes(_pseudo);
            byte[] hash = mycrypto.SignData(tab);
            _myServer.ReceiveKey(tab, hash, _publicKey);

        }

        public void Envoyer(string message)
        {
            ASCIIEncoding encoding = new ASCIIEncoding();

            byte[] tabMess = encoding.GetBytes(message);
            byte[] hashMess = mycrypto.SignData(tabMess);

            _myServer.ReceiveMessage(tabMess, hashMess,_pseudo);


        }
    }
}
