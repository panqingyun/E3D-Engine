#pragma once

#ifdef WIN32
#include <winsock2.h>
#include <MMSystem.h>
#include <windows.h>
#include <process.h>
#include <WS2tcpip.h>
#else

#endif
#include <stdio.h>
#include <string>
#include "Interface.h"

namespace E3DEngine
{
	class Http : public IObject
	{
	public:
		Http();
		~Http();

	public:
		static Http &GetInstance()
		{
			static Http ins;
			return ins;
		}
		static void Post(std::string host, std::string path, std::string post_content);
		static void Get(std::string host, std::string path, std::string get_content);

	private:
		void socketHttp(std::string host, std::string request);
	};
}


