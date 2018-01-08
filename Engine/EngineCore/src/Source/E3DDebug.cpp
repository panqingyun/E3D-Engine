#include "E3DDebug.h"
#include "../Object/E3DGameObject.h"

namespace E3DEngine
{
#ifdef WIN32
	DebugOutput Debug::OutputLogFunc = nullptr;
#endif
	StreamBuffer * Debug::m_MyStreamBuf = nullptr;
	Debug::Debug() = default;
	Logger * Debug::infoLogger = nullptr;
	Logger * Debug::errorLogger = nullptr;
	Logger * Debug::warningLogger = nullptr;
	Logger * Debug::debugLogger = nullptr;
	Debug::~Debug()
	{
		SAFE_DELETE(infoLogger);
		SAFE_DELETE(errorLogger);
		SAFE_DELETE(warningLogger);
		SAFE_DELETE(debugLogger);
	}

	void Debug::Init()
	{
		m_MyStreamBuf = new StreamBuffer();
		std::cout.rdbuf(m_MyStreamBuf);
		infoLogger		= new InfoLogger(ell_Info, nullptr);
		errorLogger		= new ErrorLogger(ell_Error, infoLogger);
		warningLogger	= new WarningLogger(ell_Warning, errorLogger);
		debugLogger		= new DebugLogger(ell_Debug, warningLogger);
	}

	void Debug::Log(LogLevel ll, const char * format, ...)
	{
		if (debugLogger == nullptr)
		{
			return;
		}
#define MAX_STRING_LENGTH (10240)
		va_list ap;
		va_start(ap, format);

		char* buf = (char*)malloc(MAX_STRING_LENGTH);
		if (buf != nullptr)
		{
			vsnprintf(buf, MAX_STRING_LENGTH, format, ap);
		}
		va_end(ap);

		debugLogger->showLog(ll, buf);
		free(buf);
	}

	int StreamBuffer::flush_buffer()
	{
		int len = int(pptr() - pbase());
		if (len <= 0)
			return 0;

		if (len <= BUFFER_SIZE)
			buffer_[len] = '\0';

#ifdef __ANDROID__    
		LOGERROR("%s", buffer_);
#endif
#ifdef WIN32
		Debug::OutputLogFunc( buffer_);
#endif
#ifdef __IOS__    
		printf("%s\n", buffer_);
#endif    
		pbump(-len);
		return len;
	}

	void DebugLogger::Log(const char * log)
	{
		std::string outLog = StringBuilder::Format("[debug]:\t%s", log);
#ifdef __IOS__
		printf("%s\n", outLog.c_str());
#endif 
#ifdef __ANDROID__
		LOGDEBUG("%s", outLog.c_str());
#endif
#ifdef WIN32
		if (Debug::OutputLogFunc != nullptr)
		{
			Debug::OutputLogFunc(outLog.c_str());
		}
#endif
	}

	void WarningLogger::Log(const char * log)
	{
		std::string outLog = StringBuilder::Format("[warning]:\t%s", log);
#ifdef __IOS__
		printf("%s\n", outLog.c_str());
#endif 
#ifdef __ANDROID__
		LOGWARNING("%s", outLog.c_str());
#endif
#ifdef WIN32
		if (Debug::OutputLogFunc != nullptr)
		{
			Debug::OutputLogFunc(outLog.c_str());
		}
#endif
	}

	void ErrorLogger::Log(const char * log)
	{
		std::string outLog = StringBuilder::Format("[error]:\t%s", log);
#ifdef __IOS__
		printf("%s\n", outLog.c_str());
#endif 
#ifdef __ANDROID__
		LOGERROR("%s", outLog.c_str());
#endif
#ifdef WIN32
		if (Debug::OutputLogFunc != nullptr)
		{
			Debug::OutputLogFunc(outLog.c_str());
		}
#endif
	}

	void InfoLogger::Log(const char * log)
	{
		std::string outLog = StringBuilder::Format("[info]:\t%s", log);
#ifdef __IOS__
		printf("%s\n", outLog.c_str());
#endif 
#ifdef __ANDROID__
		LOGINFO("%s", outLog.c_str());
#endif
#ifdef WIN32
		if (Debug::OutputLogFunc != nullptr)
		{
			Debug::OutputLogFunc(outLog.c_str());
		}
#endif
	}

	Logger::Logger(LogLevel level, Logger * nextLogger)
	{
		setLogLevel(level, nextLogger);
	}

	void Logger::showLog(LogLevel ll, const char * log)
	{
		if (ll == logLevel)
		{
			Log(log);
		}
		else if (nextDebugLogger != nullptr)
		{
			nextDebugLogger->showLog(ll, log);
		}
	}

	void Logger::Log(const char * log)
	{

	}

	void Logger::setLogLevel(LogLevel level, Logger * nextLogger)
	{
		logLevel = level;
		nextDebugLogger = nextLogger;
	}

}

