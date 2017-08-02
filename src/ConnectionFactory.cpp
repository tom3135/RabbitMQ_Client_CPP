#include "ConnectionFactory.h"
#include "ErrorParse.h"
#include "ConnectionRabbit.h"

using namespace Rabbit;

Util::Mutex ConnectionFactory::m_mutex;
ConnectionFactory::Garbage ConnectionFactory::m_gc;
ConnectionFactory* ConnectionFactory::m_instance = NULL;
ConnectionFactory* ConnectionFactory::getInstance()
{
	if(NULL == m_instance)
	{
		m_mutex.lock();
		if(NULL == m_instance)
		{
			m_instance = new ConnectionFactory();
		}
		m_mutex.unlock();
	}
	return m_instance;
}

ConnectionFactory::ConnectionFactory(void)
{

}


ConnectionFactory::~ConnectionFactory(void)
{
}

ConnectionBase* ConnectionFactory::make(const string &strConnType 
	                                           ,const string &strHostIp 
											   ,int nPort
											   ,const string &strUser 
											   ,const string &strPassword )
{
	int nRet = 0;
	ConnectionBase* pConn = nullptr;
	if ("Rabbit" == strConnType)
	{
		pConn = new ConnectionRabbit();
		pConn->setLogin(strHostIp,strUser,strPassword,nPort);
		int nRet = pConn->connectServer();
		if (0 != nRet)
		{
			pConn = nullptr;
		}
	}

	return pConn;
}


