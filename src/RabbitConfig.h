#pragma once
#include <stdio.h>
#include <string.h>

#include "Util.h"

using namespace std;
using namespace Util;
class RabbitConfig
{
public:
	class Garbage
	{
	public:
		~Garbage() {
			if(m_instance != NULL) {
				delete m_instance;
			}
		}
	};

	static RabbitConfig* getInstance();

	void initConfig();
	bool readBool(Util::IniFile &iniFile,const std::string &strKey);

	~RabbitConfig(void);
private:
	RabbitConfig(void);
	static RabbitConfig *m_instance;
	static Util::Mutex m_mutex;
	static Garbage m_gc;

public:
	string m_hostIp;
	string m_userName;
	string m_password;
	string m_strTempFolder;
	int    m_nPort;
	bool   m_bAutoAck;
	bool   m_bAutoDelete;

	int    m_nChannelIndex;
	
};

