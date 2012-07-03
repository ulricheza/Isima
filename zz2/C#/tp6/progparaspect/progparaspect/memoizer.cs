using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using PostSharp.Aspects;

namespace progparaspect
{
    [SerializableAttribute]
    public abstract class MethodInterceptionAspect : IMethodInterceptionAspect
    {

        #region IMethodInterceptionAspect Membres

        void IMethodInterceptionAspect.OnInvoke(MethodInterceptionArgs args)
        {
            throw new NotImplementedException();
        }

        #endregion
    }

}
