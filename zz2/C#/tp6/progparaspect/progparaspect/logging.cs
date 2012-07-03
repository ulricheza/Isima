using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using PostSharp.Aspects;
using System.Diagnostics;

namespace progparaspect
{
    /// <summary>
    /// Aspect that, when applied on a method, emits a trace message before and
    /// after the method execution.
    /// </summary>
    [Serializable]
    public class TraceAttribute : OnMethodBoundaryAspect
    {
        /// <summary>
        /// Method invoked before the execution of the method to which the current
        /// aspect is applied.
        /// </summary>
        /// <param name="args">Information about the method being executed.</param>
        public override void OnEntry(MethodExecutionArgs args)
        {
            Trace.TraceInformation("{0}.{1}: Enter",
                                    args.Method.DeclaringType.FullName, args.Method.Name);
            Trace.Indent();
        }

        /// <summary>
        /// Method invoked after successfull execution of the method to which the current
        /// aspect is applied.
        /// </summary>
        /// <param name="args">Information about the method being executed.</param>
        public override void OnSuccess(MethodExecutionArgs args)
        {
            Trace.Unindent();
            Trace.TraceInformation("{0}.{1}: Success",
                                    args.Method.DeclaringType.FullName, args.Method.Name);
        }

        /// <summary>
        /// Method invoked after failure of the method to which the current
        /// aspect is applied.
        /// </summary>
        /// <param name="args">Information about the method being executed.</param>
        public override void OnException(MethodExecutionArgs args)
        {
            Trace.Unindent();
            Trace.TraceInformation("{0}.{1}: Exception {2}",
                                    args.Method.DeclaringType.FullName, args.Method.Name,
                                    args.Exception.Message);
        }
    }
}
