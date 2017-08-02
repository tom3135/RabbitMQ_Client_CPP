#pragma once

#include <string>
#include <map>
#include "amqp.h"
#include <functional>
#include "DataDefine.h"

namespace Rabbit
{
	template class RABBIT_API std::allocator<char>;
	template class RABBIT_API std::basic_string<char>;
	class RABBIT_API Message
	{
	public:
		Message(void);
		~Message(void);

		void setChannelId(int nChanId);
		int getChanId()const;

		std::string getMessage();
		char* getMessageChar();
		int   getMessageLen() const;

		//set message content wait for publish
		void setData(const char* dataBuff,int nDataLen);

		void setConsumerTag( amqp_bytes_t consumer_tag);
		std::string getConsumerTag() const;
		void setExchange(amqp_bytes_t exchange);
		void setExchange(std::string exchange);
		std::string getExchange()const;

		void setRoutingKey(amqp_bytes_t routing_key);
		void setRoutingKey(std::string routing_key);
		std::string getRoutingKey()const;

	public:
		amqp_envelope_t m_envelope;
		char*           m_pGetData;
		const char*     m_pSendData;
		uint32_t        m_nMsgLen;
		int             m_nChannId;
		std::string     m_strConsumerTag;
		std::string     m_strExchange;
		std::string     m_strRouting_key;

	};
}// end namespece Rabbit

