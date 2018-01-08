using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AsyncSocketServer
{
    public interface IServerLogic
    {
        void BuildingSocketInvokeElement(ref AsyncSocketUserToken userToken);
        void ErrorResponseToClient(AsyncSocketUserToken userToken);
        void CloseClientSocket(AsyncSocketUserToken userToken);
    }
}
