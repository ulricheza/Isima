using System;
using System.Security.Cryptography;

namespace Serveur
{
    /// <summary>
    /// Classe contenant les methodes statiques concerant le cryptage de donnees
    /// </summary>
    public class Security
    {
        public Security()
        {
        }

        /// <summary>
        /// Methode permetant de recreer une cle publique avec les arguments de la webmethod
        /// en effet il sera difficile de passer directement une instance DSAParameters
        /// car il y aura des conflits avec les classes utilisant directement le DSAParameters
        /// </summary>
        /// <param name="counter"></param>
        /// <param name="G"></param>
        /// <param name="J"></param>
        /// <param name="P"></param>
        /// <param name="Q"></param>
        /// <param name="Seed"></param>
        /// <param name="X"></param>
        /// <param name="Y"></param>
        /// <returns>
        /// La cle publique reconstitue
        /// </returns>
        public static DSAParameters RecreateKey(int counter, byte[] G, byte[] J, byte[] P, byte[] Q, byte[] Seed, byte[] X, byte[] Y)
        {
            //Regeneration de la cle publique
            DSAParameters key = new DSAParameters();
            key.Counter = counter;
            key.G = G;
            key.J = J;
            key.P = P;
            key.Q = Q;
            key.Seed = Seed;
            key.X = X;
            key.Y = Y;

            return key;
        }
    }
}