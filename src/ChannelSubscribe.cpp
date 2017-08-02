#include "ChannelSubscribe.h"
#include "ConnectionBase.h"


Rabbit::ChannelSubscribe::ChannelSubscribe(void):ChannelBase()
{
}

Rabbit::ChannelSubscribe::ChannelSubscribe(ConnectionBase* pConn):ChannelBase()
{
	attachConnection(pConn);
}


Rabbit::ChannelSubscribe::~ChannelSubscribe(void)
{
}


int Rabbit::ChannelSubscribe::declareExchange()
{
	if (m_strExchange.empty())
	{
		return LMQ_QUEUE_EXCHANGE_EMPTY;
	}
	m_strExchangeType = "topic";
	int nRet = getConnection()->declareExchange(getId());
	return nRet;
}


int Rabbit::ChannelSubscribe::open()
{
	int nChanId = getId();
	int nRet = getConnection()->openChannel(getId());
	if (0 != nRet)
	{
		return nRet;
	}

	nRet = declareExchange();
	if (0 != nRet)
	{
		return nRet;
	}

	nRet = declareQueue();
	if (0 != nRet)
	{
		return nRet;
	}

	nRet = bindQueueToExchange();
	if (0 != nRet)
	{
		return nRet;
	}


	//start the work thread that receives message
	getConnection()->setStartFlag();
	getConnection()->start();

	//start a consumer(the broker start send message)
	nRet = startConsumer();
	if (0 != nRet)
	{
		return nRet;
	}
	return 0;
}

int Rabbit::ChannelSubscribe::startConsumer()
{
	return getConnection()->startConsumer(getId());
}

int Rabbit::ChannelSubscribe::setCallBack( MessageCallBack msgCallBak )
{
	m_MsgCallBak = msgCallBak;
	return 0;
}

int Rabbit::ChannelSubscribe::reOpen()
{
	closeChannel();
	int nRet = getConnection()->openChannel(getId());
	if (0 != nRet)
	{
		return nRet;
	}

	nRet = declareExchange();
	if (0 != nRet)
	{
		return nRet;
	}

	nRet = declareQueue();
	if (0 != nRet)
	{
		return nRet;
	}

	nRet = bindQueueToExchange();
	if (0 != nRet)
	{
		return nRet;
	}

	getConnection()->setStartFlag();
	getConnection()->start();

	nRet = startConsumer();
	if (0 != nRet)
	{
		return nRet;
	}
	return 0;
}
