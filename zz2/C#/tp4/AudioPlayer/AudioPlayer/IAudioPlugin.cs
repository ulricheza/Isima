using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AudioPlayer
{
    public interface IAudioPlugin
    {
        public void Decode(string str);
    }
}
