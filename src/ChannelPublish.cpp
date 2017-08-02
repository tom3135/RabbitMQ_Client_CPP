#include "ChannelPublish.h"
#include "RabbitConfig.h"
#include "ErrorParse.h"
#include "ConnectionBase.h"
#include "Message.h"



Rabbit::ChannelPublish::ChannelPublish(void):ChannelBase()
{
}

Rabbit::ChannelPublish::ChannelPublish(ConnectionBase* pConn):ChannelBase()
{
	attachConnection(pConn);
}

Rabbit::ChannelPublish::~ChannelPublish(void)
{
}

/**
* @brief declare a exchange type of "topic" for publish
*/
int Rabbit::ChannelPublish::declareExchange()
{
	if (m_strExchange.empty())
	{
		return LMQ_QUEUE_EXCHANGE_EMPTY;
	}
	m_strExchangeType = "topic";
	int nRet = getConnection()->declareExchange(getId());
	return nRet;
}

int Rabbit::ChannelPublish::open()
{
	//first of all open channel
	int nRet1 = getConnection()->openChannel(getId());
	if (0 != nRet1)
	{
		return nRet1;
	}
	//then declare exchange.
	//note:exchange name is ChannelBase::m_strExchange
	int nRet = declareExchange();
	if (0 != nRet)
	{
		return nRet;
	}

	return 0;
}

int Rabbit::ChannelPublish::publish( Message& msgObj )
{
	if (msgObj.getRoutingKey().empty())
	{
		return LMQ_PUBLISH_ERR;
	}

	if(msgObj.getMessageLen() < 1){
		return LMQ_BUF_EMPTY_WITH_SEND;
	}

	if(msgObj.getMessageLen() > 10*1024*1024){
		return LMQ_BUF_TOO_LONG;
	}

	msgObj.setChannelId(this->getId());
	return getConnection()->publish(getId(),msgObj.m_pSendData,msgObj.m_nMsgLen,msgObj.getRoutingKey());

}
/**
* @brief reopen channel
*/
int Rabbit::ChannelPublish::reOpen()
{
	//first close the present channel id with ChannelBase::m_nChanId
	closeChannel();
	//reopen ChannelBase::m_nChanId
	int nRet1 = getConnection()->openChannel(getId());
	if (0 != nRet1)
	{
		return nRet1;
	}
	//declare exchange after reopen channel successful
	int nRet = declareExchange();
	if (0 != nRet)
	{
		return nRet;
	}

	return 0;
}







