using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace tp3
{
    class Pair<Type1,Type2>
    {
        //Element 1
        private Type1 el1;
        public Type1 El1
        {
            get { return el1; }
            set { el1 = value; }
        }

        //Element 2
        private Type2 el2;
        public Type2 El2
        {
            get { return el2; }
            set { el2 = value; }
        }

        public Pair(Type1 e1, Type2 e2)
        {
            el1 = e1;
            el2 = e2;
        }

    }
}
