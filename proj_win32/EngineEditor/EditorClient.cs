using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AsyncSocketServer;

namespace EngineEditor
{
    public delegate void FPSChange(int fps);
    public delegate void LogOutput(string log);
    public class EditorClient
    {
        public AsyncSocketServer.TCPProtocol TCPHandle = null;
        public FPSChange FrameSpeedChange;
        public LogOutput LogOutputEvent;

        public void HandleMsg(NetCommand cmd)
        {
            if (cmd  == null)
            {
                return;
            }
            switch(cmd.ID)
            {
                case (int)NetCommandEnum.FrameSpeed:
                    {
                        int fps = Convert.ToInt32(cmd.Content);
                        if (FrameSpeedChange != null)
                        {
                            FrameSpeedChange(fps);
                        }
                    }
                    break;
                case (int)NetCommandEnum.LogOutputCMD:
                    {
                        if (LogOutputEvent != null)
                        {
                            LogOutputEvent(cmd.Content);
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        public void SendMsg(NetCommand cmd)
        {
            byte[] msg = NetService.SerilizeCommand(cmd);
            TCPHandle.sendMessage(msg);
        }
    }
}
