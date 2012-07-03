using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AudioPlayer
{
    public class FormatAttribute
    {
        public FormatAttribute(String format)
        {
            this.format = format;
        }

        String format;
    }
}
