#include "RabbitConfig.h"

#ifdef WIN32
#include <Windows.h>
#include <direct.h>
#include <io.h>
#else
#include <stdarg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#endif

Util::Mutex RabbitConfig::m_mutex;
RabbitConfig::Garbage RabbitConfig::m_gc;
RabbitConfig* RabbitConfig::m_instance = NULL;
RabbitConfig* RabbitConfig::getInstance()
{
	if(NULL == m_instance)
	{
		m_mutex.lock();
		if(NULL == m_instance)
		{
			m_instance = new RabbitConfig();
		}
		m_mutex.unlock();
	}
	return m_instance;
}
RabbitConfig::RabbitConfig(void)
{
	m_hostIp = "";
	m_userName = "";
	m_password = "";
	m_strTempFolder ="";
	m_nPort = 0;
	m_bAutoAck = true;
	m_bAutoDelete = true;
	m_nChannelIndex = 1;

	initConfig();
}


RabbitConfig::~RabbitConfig(void)
{
}

void RabbitConfig::initConfig()
{
	string strFileName = "../lib/RabbitConfig.ini";
	Util::IniFile iniFile(strFileName);
	iniFile.setSection("ServerInfo");

	m_hostIp = iniFile.readStr("host", "127.0.0.1");
	m_nPort = iniFile.readInt("port", 5672);
	m_userName = iniFile.readStr("username", "test");
	m_password = iniFile.readStr("password", "123456");
	m_bAutoAck = readBool(iniFile,"auto_ack");
	m_bAutoDelete = readBool(iniFile,"auto_delete");

	int n = 0;
}

bool RabbitConfig::readBool(Util::IniFile &iniFile,const std::string &strKey)
{
	int nGet = iniFile.readInt(strKey,1);
	if (0 == nGet)
	{
		return false;
	}
	else
	{
		return true;
	}

}
