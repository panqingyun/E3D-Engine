using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AsyncSocketServer
{
    public interface IPageProcess
    {
        void ProcessPage(HttpClientProtocol http, string htm, params string[] message);
    }
}
