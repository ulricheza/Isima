using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace WSLivre
{
    public class VerificationBanque
    {
        
        public bool VerificationCarte(String numerocarte)
        {
            int numero;
            int carte = 0;
            bool retour = false;

            foreach (char i in numerocarte)
            {
                numero = Convert.ToInt32(i);
                if (numero % 2 == 1)
                {
                    numero = (numero * 2) % 10;
                }
                carte += numero;
            }

            if (carte % 10 == 0)
            {
                retour = true;
            }

            return retour;
        }
    }
}