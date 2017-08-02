#include "ConnectionBase.h"
#include "ChannelBase.h"
#include "Message.h"
#include "version.h"

Rabbit::ConnectionBase::ConnectionBase(void):Util::Thread()
{
	printf("Version    : %s\n",FILE_VER_STR);
	printf("Build time : %s\n",RELEASE_DATE);
}


Rabbit::ConnectionBase::~ConnectionBase(void)
{
	closeConn();
}

void Rabbit::ConnectionBase::run()
{
	while(1 == m_nRunning)
	{
		Message msg;
		int nRet = consumeData(msg);
		if (0 != nRet)
		{	
			if (LMQ_CHANNEL_CLOSE == nRet)
			{
				//reopen channel after appear channel close method
				openChannel(msg.getChanId());
			}
			else if (LMQ_CONNECTION_CLOSE == nRet)
			{
				//reconnect server after appear connection close mothod
				reConnect();
			}
			//std::cout<<"Debug:"<<"thread running"<<std::endl;
			continue;
		}

		ChannelBase* pTmpChan = getChan(msg.getChanId());
		pTmpChan->getMessage(msg);
	}


}

void Rabbit::ConnectionBase::registerChannels(ChannelBase* pChan )
{
	int nChannelIndex = pChan->getId();
	m_mapChannels.insert(pair<int,ChannelBase*>(nChannelIndex,pChan));
}

Rabbit::ChannelBase* Rabbit::ConnectionBase::getChan( int nChanId )
{
	ChannelBase* pTempChan = NULL;
	map<int,ChannelBase*>::iterator iter;
	iter = m_mapChannels.find(nChanId);
	if (iter == m_mapChannels.end())
	{
		return pTempChan;
	}
	pTempChan = iter->second;
	return pTempChan;
}

int Rabbit::ConnectionBase::isRunning()
{
	return m_nRunning;
}

void Rabbit::ConnectionBase::setStartFlag()
{
	m_nRunning = 1;
}

void Rabbit::ConnectionBase::setStopFlag()
{
	m_nRunning = 0;
}

int Rabbit::ConnectionBase::consumeData( Message& msg )
{
	msg.m_nMsgLen = 1023;
	msg.m_nChannId = 1;

	return 0;
}


int Rabbit::ConnectionBase::setLogin( const string& host,const string& userName,
	                                  const string& password,int port )
{
	m_strHostIp = host;
	m_strUser   = userName;
	m_strPassword = password;
	m_nPort = port;

	return 0;
}

//override
int Rabbit::ConnectionBase::closeConn()
{
	return 0;
}
//override
int Rabbit::ConnectionBase::reConnect()
{
	return 0;
}
//override
int Rabbit::ConnectionBase::openSocket()
{
	return 0;
}


int Rabbit::ConnectionBase::declareExchange(int nChanId)
{
	return 0;
}


int Rabbit::ConnectionBase::declareQueue(int nChanId)
{
	return 0;
}

int Rabbit::ConnectionBase::bindQueueToExchange(int nChanId)
{
	return 0;
}

int Rabbit::ConnectionBase::openChannel(int nChanId)
{
	return 0;
}

int Rabbit::ConnectionBase::publish( int nChanId,const char* pBuf,const int nLen 
	                         ,const string& routingKey)
{
	return 0;
}

int Rabbit::ConnectionBase::connectServer()
{
	return 0;
}

int Rabbit::ConnectionBase::startConsumer(int nChanId)
{
	return 0;
}

int Rabbit::ConnectionBase::removeChannel(int nChanId)
{
	ChannelBase *pTempChan = nullptr;
	map<int,ChannelBase*>::iterator iter;
	iter = m_mapChannels.find(nChanId);
	m_mapChannels.erase(iter);

	if (iter == m_mapChannels.end())
	{
		return 0;
	}
	pTempChan = iter->second;
	delete pTempChan;

	return 0;
}
/**
* @brief reopen all channels which management by m_mapChannels
*/
int Rabbit::ConnectionBase::reOpenChannels()
{
	map<int,ChannelBase*>::iterator iter;
	for(auto iter = m_mapChannels.begin(); iter != m_mapChannels.end(); /*it++*/)
	{
		openChannel(iter->second->getId());
	}

	return 0;
}

int Rabbit::ConnectionBase::closeChannel(int nChanId)
{
	return 0;
}
/**
* @brief close all channels which management by m_mapChannels
*/
int Rabbit::ConnectionBase::closeChannels()
{
	map<int,ChannelBase*>::iterator iter;
	for(auto iter = m_mapChannels.begin(); iter != m_mapChannels.end(); /*it++*/)
	{
		closeChannel(iter->second->getId());
	}

	return 0;
}
