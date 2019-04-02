#ifndef __E3D_DEBUG_H__
#define __E3D_DEBUG_H__
#include "Interface.h"

#ifdef __ANDROID__
#include <android/log.h>
#define LOGDEBUG(...) __android_log_print(ANDROID_LOG_DEBUG,"", __VA_ARGS__)
#define LOGINFO(...) __android_log_print(ANDROID_LOG_INFO,"", __VA_ARGS__)
#define LOGWARNING(...) __android_log_print(ANDROID_LOG_WARN,"", __VA_ARGS__)
#define LOGERROR(...) __android_log_print(ANDROID_LOG_ERROR,"", __VA_ARGS__)
#endif

typedef enum 
{
	ell_Info,
	ell_Error,
	ell_Debug,
	ell_Warning,
	ell_None
} LogLevel;

#ifdef WIN32
using DebugOutput = void(*)(const char * log);
#endif

namespace E3DEngine
{
	class StreamBuffer : public std::streambuf
	{
		enum
		{
			BUFFER_SIZE = 1024,
		};

	public:
		StreamBuffer()
		{
			buffer_[BUFFER_SIZE] = '\0';
			setp(buffer_, buffer_ + BUFFER_SIZE - 1);
		}

		virtual ~StreamBuffer() override
		{
			sync();
		}

	protected:
		virtual int_type overflow(int_type c) override
		{
			if (c != EOF)
			{
				*pptr() = c;
				pbump(1);
			}
			flush_buffer();
			return c;
		}

		virtual int sync() override
		{
			flush_buffer();
			return 0;
		}

	private:
		int flush_buffer();

	private:
		char buffer_[BUFFER_SIZE + 1];
	};

	class Logger : public IObject
	{
	public:
		Logger() = default;
		Logger(LogLevel level, Logger * nextLogger);

	public:
		void showLog(LogLevel ll, const char * log);
	protected:
		virtual void Log(const char * log);
		void setLogLevel(LogLevel level, Logger * nextLogger);

	protected:
		LogLevel logLevel;
		Logger * nextDebugLogger;
	};

	class E3D_EXPORT_DLL Debug : public IObject
	{
	public:
		Debug();
		~Debug();
		void static Init();
	public: 
		static void Log(LogLevel ll, const char * param, ...);
		static StreamBuffer * m_MyStreamBuf;
		static DebugOutput OutputLogFunc;
	protected:
		static Logger * infoLogger;
		static Logger * errorLogger;
		static Logger * debugLogger;
		static Logger * warningLogger;
	};

	//////////////////////////////////////////////////////////////////////////
	// debug warning error info
	//////////////////////////////////////////////////////////////////////////

	/************************************************************************/
	/* ‘»Œ¡¥
	/************************************************************************/
	class DebugLogger : public Logger
	{
	public:
		DebugLogger(LogLevel level, Logger * nextLogger)
			: Logger(level, nextLogger)
		{
		}
	protected:
		virtual void Log(const char * log) override;
	};

	class WarningLogger : public Logger
	{
	public:
		WarningLogger(LogLevel level, Logger * nextLogger)
			: Logger(level, nextLogger)
		{

		}
	protected:
		virtual void Log(const char * log) override;
	};

	class ErrorLogger : public Logger
	{
	public:
		ErrorLogger(LogLevel level, Logger * nextLogger)
			: Logger(level, nextLogger)
		{

		}
	protected:
		virtual void Log(const char * log) override;
	};

	class InfoLogger : public Logger
	{
	public:
		InfoLogger(LogLevel level, Logger * nextLogger)
			: Logger(level, nextLogger)
		{

		}
	protected:
		virtual void Log(const char * log) override;
	};
}

#endif