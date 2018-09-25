#pragma once
#include <string>
#include "NetCommand.h"

void Send(std::string msg);
void Close();
void CreateTCP(const char *ip, int port);

#define CMD_FRONT_CODE 0xFF
#define CMD_HEADER_LENGTH 6
#define CMD_BUFFER_LENGTH 4096

class EncodingTools
{
public:
	static void  intToByte(int i, BYTE *bytes, int size = 4)
	{
		memset(bytes, 0, sizeof(BYTE)*  size);
		bytes[3] = (BYTE)(0xff & i);
		bytes[2] = (BYTE)((0xff00 & i) >> 8);
		bytes[1] = (BYTE)((0xff0000 & i) >> 16);
		bytes[0] = (BYTE)((0xff000000 & i) >> 24);
	}

	//byteתint
	static int bytesToInt(BYTE* bytes, int size = 4)
	{
		int addr = bytes[3] & 0xFF;
		addr |= ((bytes[2] << 8) & 0xFF00);
		addr |= ((bytes[1] << 16) & 0xFF0000);
		addr |= ((bytes[0] << 24) & 0xFF000000);
		return addr;
	}


};

class NetService
{
public:
	static NetCommand * DescCommand(BYTE * *msg, int &length)
	{
		if (*msg == nullptr)
		{
			return nullptr;
		}
		if ((*msg)[0] != CMD_FRONT_CODE)
		{
			return nullptr;
		}
		NetCommand * cmd = new NetCommand;
		cmd->FrontCode = (*msg)[0];
		cmd->ID = (*msg)[1];
		BYTE content[] = 
		{
			(*msg)[2],
			(*msg)[3],
			(*msg)[4],
			(*msg)[5]
		};
		cmd->Length = EncodingTools::bytesToInt(content);
		std::string message = std::string((char*)*msg);
		cmd->Content = message.substr(CMD_HEADER_LENGTH, cmd->Length - CMD_HEADER_LENGTH);
		std::string subMsg = message.substr(cmd->Length);

		length = length - cmd->Length;
		BYTE * bRet = new BYTE[length];
		memcpy(bRet, subMsg.c_str(), length);
		*msg = bRet;
		return cmd;
	}

	static std::string SerilizeCommand(NetCommand *cmd)
	{
		BYTE * length = new BYTE[4];
		EncodingTools::intToByte(cmd->GetLength(), length);

		BYTE bmsg[] =
		{
			CMD_FRONT_CODE,
			cmd->ID,
			length[0],
			length[1],
			length[2],
			length[3],
		};
		int size_byte = cmd->Content.length();
		std::string bRet = std::string((char*)bmsg);

		bRet.append(cmd->Content);

		return bRet;
	}

	static void Close()
	{
		::Close();
	}
};