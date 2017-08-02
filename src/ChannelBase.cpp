#include "ChannelBase.h"
#include "ConnectionBase.h"
#include "RabbitConfig.h"
#include "Message.h"

Rabbit::ChannelBase::ChannelBase(void)
{
	m_nChanId = RabbitConfig::getInstance()->m_nChannelIndex;
	RabbitConfig::getInstance()->m_nChannelIndex++;

}


Rabbit::ChannelBase::~ChannelBase(void)
{
	//call own method
	int nRet = closeChannel();
	if (0 == nRet) 
	{
		//remove the given channel from connection
		getConnection()->removeChannel(getId());
	}
}

int Rabbit::ChannelBase::getId()
{
	return m_nChanId;
}

int Rabbit::ChannelBase::getMessage(Message& msg )
{
	return m_MsgCallBak(msg);
}
/**
* @brief the derived class will override this method
*/
int Rabbit::ChannelBase::declareExchange()
{
	return 0;
}

int Rabbit::ChannelBase::declareQueue()
{
	if (m_strQueue.empty())
	{
		return LMQ_QUEUE_EXCHANGE_EMPTY;
	}

	return getConnection()->declareQueue(getId());

}

int Rabbit::ChannelBase::bindQueueToExchange()
{
	if (m_strBindingKey.empty())
	{
		return LMQ_BING_ERR;
	}

	return getConnection()->bindQueueToExchange(getId());
}


int Rabbit::ChannelBase::attachConnection( ConnectionBase* pConn )
{
	m_pConn = pConn;
	m_pConn->registerChannels(this);
	return 0;
}


Rabbit::ConnectionBase* Rabbit::ChannelBase::getConnection()
{
	return m_pConn;
}
/**
*  @brief close the given channel but do not remove it from connection
*/
int Rabbit::ChannelBase::closeChannel()
{
	return getConnection()->closeChannel(getId());
}
/**
* @brief open channel 
* @details the derived class will override this method
*/
int Rabbit::ChannelBase::open()
{
	return 0;
}

int Rabbit::ChannelBase::setExchange( const std::string& strExchange,bool isPersist )
{
	m_strExchange = strExchange;
	m_bExchangePersist = isPersist;
	return 0;
}

int Rabbit::ChannelBase::setQueue( const std::string& strQueue,bool isPersist )
{
	m_strQueue = strQueue;
	m_bQueuePersist = isPersist;
	return 0;
}

int Rabbit::ChannelBase::setBindingKey( const std::string& strBindingKey )
{
	m_strBindingKey = strBindingKey;
	return 0;
}

int Rabbit::ChannelBase::reOpen()
{
	return 0;
}




