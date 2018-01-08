#include "E3DNet.h"

#define M_PI_2     1.57079632679489661923

void LogOutput(const char* log)
{
	NetCommand * cmd = new NetCommand;
	cmd->ID = LogOutputCMD;
	cmd->Content = log;
	Send(NetService::SerilizeCommand(cmd));
	delete cmd;
}

E3DNet::E3DNet()
{
	currentReadPool = 1;
	setDebugLogOutFunc(LogOutput);
	commandHandlerMap[EnginePause]		= new EnginePauseCommand();
	commandHandlerMap[GotoNextFrame]	= new GotoNextFrameCommand();
}

E3DNet::~E3DNet()
{
	for (auto & cmdHandler : commandHandlerMap)
	{
		delete cmdHandler.second;
	}
	commandHandlerMap.clear();
}

void E3DNet::Update(float deltaTiem)
{
	int frameSpeed = (1.0 / deltaTiem);
	NetCommand * cmd = new NetCommand;
	cmd->ID = FrameSpeed;
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%d", frameSpeed);
	cmd->Content = std::string(buffer);
	Send(NetService::SerilizeCommand(cmd));
	delete cmd;

	//boxElement->Update(deltaTiem);
	handleNetCmd();
}

void E3DNet::handleNetCmd()
{
	std::vector<NetCommand*> temp;
	if (currentReadPool == 1)
	{
		std::copy(msgPool1.begin(), msgPool1.end(), std::back_inserter(temp));
		for (auto & it : temp)
		{
			commandHandlerMap[it->ID]->Handler(it);
		}
		msgPool1.clear();
		currentReadPool = 2;
	}
	else
	{
		std::copy(msgPool2.begin(), msgPool2.end(), std::back_inserter(temp));
		for (auto & it : temp)
		{
			commandHandlerMap[it->ID]->Handler(it);
		}
		msgPool2.clear();
		currentReadPool = 1;
	}
}

void E3DNet::CreateNetLink()
{
	CreateTCP("127.0.0.1", 8800);
	NetCommand *login = new NetCommand;
	login->ID = Login;
	Send(NetService::SerilizeCommand(login));
}

void E3DNet::GetNetMsg(BYTE* msg, int &msgLength)
{
	NetCommand * cmd = NetService::DescCommand(&msg, msgLength);
	if (cmd == nullptr)
	{
		return;
	}
	if (currentReadPool == 1)
	{
		msgPool2.emplace_back(cmd);
	}
	else
	{
		msgPool1.emplace_back(cmd);
	}
	// ´¦ÀíÕ³°ü
	if (msg[0] == CMD_FRONT_CODE)
	{
		GetNetMsg(msg, msgLength);
	}
}

void E3DNet::Destory()
{

}

void GotoNextFrameCommand::Handler(NetCommand * cmd)
{
	
}
