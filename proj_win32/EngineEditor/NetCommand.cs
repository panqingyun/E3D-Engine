using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EngineEditor
{
    public class NetCommand
    {
        public byte FrontCode;
        public byte ID;
        public int Length;
        public string Content;
        public int GetLength()
        {
            byte[] b = Encoding.Default.GetBytes(Content);
            return 1 + 1 + 4 + b.Length;
        }
    }

    public class NetService
    {
        const byte CMD_FRONT_CODE = 0xf;
        public static NetCommand  DescCommand(ref byte[] msg)
	    {
            if (msg == null)
            {
                return null;
            }
            if (msg.Length == 0)
            {
                return null;
            }
            if (msg[0] != CMD_FRONT_CODE)
            {
                return null;
            }
		    if (msg.Length < 2)
		    {
			    return null;
		    }
		    NetCommand  cmd = new NetCommand();
            cmd.FrontCode = msg[0];
		    cmd.ID = msg[1];
            cmd.Length = EncodingTools.bytesToInt(new byte[] { msg[2], msg[3], msg[4], msg[5] }, 0);
            byte[] str = new byte[cmd.Length - 6];
            int idx = 0;
            for (int i = 6; i < cmd.Length; i++ )
            {
                str[idx] = msg[i];
                idx++;
            }
            cmd.Content = Encoding.Default.GetString(str);
            msg = EncodingTools.CopyBytes(msg, cmd.Length, msg.Length);
		    return cmd;
	    }

	    public static byte[] SerilizeCommand(NetCommand cmd)
	    {
            byte[] length = EncodingTools.intToBytes(cmd.GetLength());
            byte[] content = Encoding.Default.GetBytes(cmd.Content);
            byte[] bmsg = 
            {
                CMD_FRONT_CODE,
                cmd.ID,
                length[0],
                length[1],
                length[2],
                length[3],
            };

            byte[] bRet = new byte[bmsg.Length + content.Length];
            for (int i = 0; i < bmsg.Length; i++)
            {
                bRet[i] = bmsg[i];
            }
            for (int i = 0; i < content.Length; i++)
            {
                bRet[bmsg.Length + i] = content[i];
            }

            return bRet;
	    }
    }

    enum NetCommandEnum
    {
        CreateScenes = 0,
        ShowParticle = 1,
        ShowMagicWord = 2,
        ChangeScenes = 3,
        ClearScene = 4,
        Login = 5,
        PauseParticle = 6,
        PauseWord = 7,
        StopParticle = 8,
        StopeWord = 9,
        SelectParticle = 10,
        FrameSpeed = 11,
        SelectFilter = 12,
        PauseEngine = 13,
        GotoNextFrame = 14,
        LogOutputCMD = 15,
    };
}
