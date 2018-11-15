#include "E3DDebug.h"
#include "../Object/E3DGameObject.h"

namespace E3DEngine
{
	DebugOutput Debug::OutputLogFunc = nullptr;
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
		if (Debug::OutputLogFunc != nullptr)
		{
			Debug::OutputLogFunc(buffer_);
		}
		pbump(-len);
		return len;
	}

	void DebugLogger::Log(const char * log)
	{
		std::string outLog = StringBuilder::Format("[debug]%s\n", log);

		if (Debug::OutputLogFunc != nullptr)
		{
			Debug::OutputLogFunc(outLog.c_str());
		}
	}

	void WarningLogger::Log(const char * log)
	{
		std::string outLog = StringBuilder::Format("[warning]%s\n", log);

		if (Debug::OutputLogFunc != nullptr)
		{
			Debug::OutputLogFunc(outLog.c_str());
		}
	}

	void ErrorLogger::Log(const char * log)
	{
		/*std::string outLog = StringBuilder::Format("[error]%s\n", log);
		if (Debug::OutputLogFunc != nullptr)
		{
			Debug::OutputLogFunc(outLog.c_str());
		}*/
	}

	void InfoLogger::Log(const char * log)
	{
		std::string outLog = StringBuilder::Format("%s\n", log);

		if (Debug::OutputLogFunc != nullptr)
		{
			Debug::OutputLogFunc(outLog.c_str());
		}
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

