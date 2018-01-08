#pragma once
#include "NetService.h"
#include <process.h>
#include <include/EngineAPI.h>

class E3DNet
{
	E3DNet();
public:
	~E3DNet();
	static E3DNet &GetInstance()
	{
		static E3DNet _ins;
		return _ins;
	}
	void GetNetMsg(BYTE* msg, int &msgLength);
	void CreateNetLink();
	void Update(float deltaTiem);
	void handleNetCmd();
	void Destory();
	void ApplicationShutdown()
	{
		NetService::Close();
	}

public:
	std::vector<NetCommand*> msgPool1;
	std::vector<NetCommand*> msgPool2;
	int currentReadPool;
	std::map<DWORD, CommandHandler*> commandHandlerMap;
public:
	void InitLogic()
	{
		InitializeCriticalSection(&p_NetCS);		
		CreateNetLink();	
	}

	CRITICAL_SECTION            p_NetCS;
};

/************************************************************************/
/*        命令模式 
/*	网络是发送者，以下都是接收者																		
/************************************************************************/

class FrameSpeedCommand : public CommandHandler
{
public:
	virtual void Handler(NetCommand * cmd) override
	{

	}
};

class EnginePauseCommand : public CommandHandler
{
public:
	virtual void Handler(NetCommand * cmd) override
	{
		bool bPause = atoi(cmd->Content.c_str()) == 1 ? true : false;
		PauseEngine(bPause);
	}
};

class GotoNextFrameCommand : public CommandHandler
{
public:
	virtual void Handler(NetCommand * cmd) override;
};