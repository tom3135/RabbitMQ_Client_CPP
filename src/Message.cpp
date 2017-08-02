#include "Message.h"


Rabbit::Message::Message(void)
{
	m_pGetData = nullptr;
	m_pSendData = nullptr;

	m_envelope.exchange = amqp_empty_bytes;
}

Rabbit::Message::~Message(void)
{
	// m_envelope has nothing when publish data
	// it's has value only when we get comsume data
	if (m_envelope.exchange.bytes)
	{
		amqp_destroy_envelope(&m_envelope);
	}

	if (m_pGetData)
	{
		delete[] m_pGetData;
	}
}

int Rabbit::Message::getChanId()const
{
	return m_nChannId;
}

void Rabbit::Message::setConsumerTag( amqp_bytes_t consumer_tag )
{
	m_strConsumerTag.assign( (char*)consumer_tag.bytes, consumer_tag.len );
}

std::string Rabbit::Message::getConsumerTag()const
{
	return m_strConsumerTag;
}

void Rabbit::Message::setExchange( amqp_bytes_t exchange )
{
	if (exchange.len)
		m_strExchange.assign( (char*)exchange.bytes, exchange.len );
}

void Rabbit::Message::setExchange(std::string exchange)
{
	m_strExchange = exchange;
}

std::string Rabbit::Message::getExchange()const
{
	return m_strExchange;
}

void Rabbit::Message::setRoutingKey( amqp_bytes_t routing_key )
{
	if (routing_key.len)
		m_strRouting_key.assign( (char*)routing_key.bytes, routing_key.len );
}

void Rabbit::Message::setRoutingKey(std::string routing_key)
{
	if (routing_key.empty())
	{
		m_strRouting_key = m_strExchange;
	}
	m_strRouting_key = routing_key;
}

std::string Rabbit::Message::getRoutingKey()const
{
	return m_strRouting_key;
}

int Rabbit::Message::getMessageLen()const
{
	return m_nMsgLen;
}

std::string Rabbit::Message::getMessage()
{
	std::string strData;
	strData.assign((const char*)m_envelope.message.body.bytes,m_nMsgLen);

	return strData;
}

char* Rabbit::Message::getMessageChar()
{
	m_pGetData = new char[m_nMsgLen];
	memset(m_pGetData, 0 , m_nMsgLen);

	memcpy(m_pGetData,m_envelope.message.body.bytes,m_nMsgLen);
	return m_pGetData;
}

void Rabbit::Message::setData(const char* dataBuff,int nDataLen )
{
	m_pSendData = dataBuff;
	m_nMsgLen = nDataLen;
}

void Rabbit::Message::setChannelId( int nChanId )
{
	m_nChannId = nChanId;
}

