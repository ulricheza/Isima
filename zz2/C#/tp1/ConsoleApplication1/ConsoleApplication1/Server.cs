using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Security.Cryptography;

namespace tp1_signature_message
{
    public class Server
    {

        private Dictionary<String, DSAParameters> _clients;

        public Server()
        {
            _clients = new Dictionary<string,DSAParameters>();
        }

        public bool ReceiveKey(byte[] pseudo,byte[] hash, DSAParameters key )
        {
            bool ret = false;
            ASCIIEncoding codage = new ASCIIEncoding();
            DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();
            mycrypto.ImportParameters(key);
            if(mycrypto.VerifyData(pseudo,hash))
            {
                
                string nick = codage.GetString(pseudo);
                _clients.Add(nick, key);
                ret = true;
            }


            return ret;
        }

        public bool ReceiveMessage(byte[] mess, byte[] hashMess, string pseudo)
        {
            DSAParameters key;
            ASCIIEncoding codage = new ASCIIEncoding();
            DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();

            bool ret = false;

            if (_clients.TryGetValue(pseudo,out key))
            {
                mycrypto.ImportParameters(key);
                if (mycrypto.VerifyData(mess, hashMess))
                {
                    Console.WriteLine(pseudo + " a ecrit: " + codage.GetString(mess));
                    ret = true;
                }
            }

            return ret;
        }



    }
}
