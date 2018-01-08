using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AsyncSocketServer
{
    public class LogOutputSocketProtocol : BaseSocketProtocol
    {
        private LogFixedBuffer m_logFixedBuffer;
        public LogFixedBuffer LogFixedBuffer { get { return m_logFixedBuffer; } }
        private AsyncSocketServer socketServer;
        public LogOutputSocketProtocol(AsyncSocketServer asyncSocketServer, AsyncSocketUserToken asyncSocketUserToken)
            : base(asyncSocketServer, asyncSocketUserToken)
        {
            m_socketFlag = "LogOutput";
            m_logFixedBuffer = new LogFixedBuffer();
            lock (asyncSocketServer.LogOutputSocketProtocolMgr)
            {
                asyncSocketServer.LogOutputSocketProtocolMgr.Add(this);
            }
            socketServer = asyncSocketServer;
            SendResponse();
        }

        public override void Close()
        {
            lock (socketServer.LogOutputSocketProtocolMgr)
            {
                socketServer.LogOutputSocketProtocolMgr.Remove(this);
            }
        }

        public override bool ProcessReceive(byte[] buffer, int offset, int count)
        {
            m_activeDT = DateTime.UtcNow;
            if (count == 1)
            {
                if (buffer[0] == (byte)Keys.Escape)
                    return false;
                else
                    return SendResponse();
            }
            else
                return SendResponse();
        }

        public override bool SendCallback()
        {
            bool result = base.SendCallback();
            if (m_logFixedBuffer.DataCount > 0)
            {
                result = DoSendBuffer(m_logFixedBuffer.FixedBuffer, 0, m_logFixedBuffer.DataCount);
                m_logFixedBuffer.Clear();
            }
            return result;
        }

        //主动发送，如果没有回调的时候，需要主动下发，否则等待回调
        public bool InitiativeSend()
        {
            if (!m_sendAsync)
            {
                return SendCallback();
            }
            else
                return true;
        }

        public bool SendResponse()
        {
            m_logFixedBuffer.WriteString("\r\nLongChengTieJi NET IOCP Server");
            m_logFixedBuffer.WriteString("Press ESC to exit\r\n");
            return InitiativeSend();
        }
    }

    public class LogOutputSocketProtocolMgr : Object
    {
        private List<LogOutputSocketProtocol> m_list;

        public LogOutputSocketProtocolMgr()
        {
            m_list = new List<LogOutputSocketProtocol>();
        }

        public int Count()
        {
            return m_list.Count;
        }

        public LogOutputSocketProtocol ElementAt(int index)
        {
            return m_list.ElementAt(index);
        }

        public void Add(LogOutputSocketProtocol value)
        {
            m_list.Add(value);
        }

        public void Remove(LogOutputSocketProtocol value)
        {
            m_list.Remove(value);
        }
    }

    public class LogFixedBuffer : Object
    {
        private byte[] m_fixedBuffer;
        public byte[] FixedBuffer { get { return m_fixedBuffer; } }
        private int m_dataCount;
        public int DataCount { get { return m_dataCount; } }

        public LogFixedBuffer()
        {
            m_fixedBuffer = new byte[1024 * 16]; //申请大小为16K
            m_dataCount = 0;
        }

        public void WriteBuffer(byte[] buffer, int offset, int count)
        {
            if ((m_fixedBuffer.Length - m_dataCount) >= count) //如果长度够，则复制内存
            {
                Array.Copy(buffer, offset, m_fixedBuffer, m_dataCount, count);
                m_dataCount = m_dataCount + count;
            }
        }

        public void WriteBuffer(byte[] buffer)
        {
            WriteBuffer(buffer, 0, buffer.Length);
        }

        public void WriteString(string value)
        {
            byte[] tmpBuffer = Encoding.ASCII.GetBytes(value);
            WriteBuffer(tmpBuffer);
        }

        public void Clear()
        {
            m_dataCount = 0;
        }
    }
    
}
