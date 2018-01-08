using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace EngineEditor
{
    public class EncodingTools
    {
        /// <summary>
        /// 内存复制
        /// </summary>
        /// <param name="dest">目标</param>
        /// <param name="src">源</param>
        /// <param name="count">数目</param>
        /// <returns></returns>
        [DllImport("msvcrt.dll", EntryPoint = "memcpy", CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        public static extern IntPtr memcopy(byte[] dest, byte[] src, int count);

        /// <summary>
        /// 内存赋值
        /// </summary>
        /// <param name="dest">目标</param>
        /// <param name="value">值</param>
        /// <param name="count">数目</param>
        /// <returns></returns>
        [DllImport("msvcrt.dll", EntryPoint = "memset", CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        public static extern IntPtr memset(byte[] dest, int value, int count);

        /**  
          * 将int数值转换为占四个字节的byte数组，本方法适用于(高位在前，低位在后)的顺序 
          */
        public static byte[] uintToBytes(uint value)
        {
            byte[] src = new byte[4];
            src[0] = (byte)((value >> 24) & 0xFF);
            src[1] = (byte)((value >> 16) & 0xFF);
            src[2] = (byte)((value >> 8) & 0xFF);
            src[3] = (byte)(value & 0xFF);
            return src;
        }

        /**  
           * 将int数值转换为占四个字节的byte数组，本方法适用于(高位在前，低位在后)的顺序 
           */
        public static byte[] intToBytes(int value)
        {
            byte[] src = new byte[4];
            src[0] = (byte)((value >> 24) & 0xFF);
            src[1] = (byte)((value >> 16) & 0xFF);
            src[2] = (byte)((value >> 8) & 0xFF);
            src[3] = (byte)(value & 0xFF);
            return src;
        }

        public static byte intToByte(int value)
        {
            byte src = (byte)(value & 0xFF);

            return src;
        }

        /**  
           * byte数组中取int数值，本方法适用于(低位在后，高位在前)的顺序 
           */
        public static uint bytesToUInt(byte[] src, int offset)
        {
            uint value;
            value = (uint)(((src[offset] & 0xFF) << 24)
                    | ((src[offset + 1] & 0xFF) << 16)
                    | ((src[offset + 2] & 0xFF) << 8)
                    | (src[offset + 3] & 0xFF));
            return value;
        }

        /**  
           * byte数组中取int数值，本方法适用于(低位在后，高位在前)的顺序 
           */
        public static int bytesToInt(byte[] src, int offset)
        {
            int value;
            value = (int)(((src[offset] & 0xFF) << 24)
                    | ((src[offset + 1] & 0xFF) << 16)
                    | ((src[offset + 2] & 0xFF) << 8)
                    | (src[offset + 3] & 0xFF));
            return value;
        }

        /**  
           * 将UInt16数值转换为占四个字节的byte数组，本方法适用于(高位在前，低位在后)的顺序 
           */
        public static byte[] shortToBytes(int value)
        {
            byte[] src = new byte[2];
            src[0] = (byte)((value >> 8) & 0xFF);
            src[1] = (byte)(value & 0xFF);
            return src;
        }

        public static byte[] ushortToBytes(ushort value)
        {
            byte[] src = new byte[2];
            src[0] = (byte)((value >> 8) & 0xFF);
            src[1] = (byte)(value & 0xFF);
            return src;
        }

        /**  
           * byte数组中取UInt16数值，本方法适用于(低位在后，高位在前)的顺序 
           */
        public static UInt16 bytesToShort(byte[] src, int offset)
        {
            UInt16 value;
            value = (UInt16)(
                ((src[offset + 0] & 0xFF) << 8)
                    | (src[offset + 1] & 0xFF));
            return value;
        }

        public static byte[] CopyBytes(byte[] source, int length)
        {
            if (length > source.Length)
            {
                return null;
            }
            byte[] Ret = new byte[length];
            memcopy(Ret, source, length);
            return Ret;
        }

        public static byte[] CopyBytes(byte[] source, int start, int length)
        {
            if (start + length > source.Length)
            {
                return null;
            }
            return source.Skip(start).Take(length).ToArray();
        }
        public static byte[] stringToBytes(string source, int destByteLength = 0)
        {
            byte[] bRet = null;
            if (destByteLength != 0)
            {
                bRet = new byte[destByteLength];
                byte[] convertByte = Encoding.ASCII.GetBytes(source);
                if (convertByte.Length < destByteLength)
                {
                    memcopy(bRet, convertByte, convertByte.Length);
                }
                else
                {
                    memcopy(bRet, convertByte, destByteLength);
                }
                return bRet;
            }
            else
            {
                bRet = Encoding.ASCII.GetBytes(source);
                return bRet;
            }
        }

        public static string bytesToString(byte[] bytes)
        {
            int stringLength = 0;
            for (int i = 0; i < bytes.Length; i++)
            {
                if (bytes[i] == 0)
                {
                    stringLength = i;
                    break;
                }
            }
            return Encoding.Default.GetString(bytes, 0, stringLength);
        }

        public static string outPut16Number(byte[] b, int length)
        {
            StringBuilder outStr = new StringBuilder();
            outStr.Capacity = length * 2;
            for (int i = 0; i < length; i++)
            {
                outStr.Append(Convert.ToString(b[i], 16) + " ");
            }
            return outStr.ToString().ToUpper();
        }
    }
}
