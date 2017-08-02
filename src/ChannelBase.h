#pragma once

#include <string>
#include <functional>
#include "DataDefine.h"

namespace Rabbit
{
	class ConnectionBase;
	class Message;
	typedef std::function<int(Message &message)> RABBIT_API MessageCallBack;
	//export the template to avoid the 4251 warning
	template class RABBIT_API std::allocator<char>;
	template class RABBIT_API std::basic_string<char>;
	template class RABBIT_API std::tr1::function<int(Message &message)>;

	//base class for channel
	class RABBIT_API ChannelBase
	{
	public:
		ChannelBase(void);
		virtual ~ChannelBase(void);

		virtual int open();
		virtual int reOpen();
		int getId();
		int getMessage(Message& msg);	
		int setExchange(const std::string& strExchange,bool isPersist);
		int setQueue(const std::string& strQueue,bool isPersist);
		int setBindingKey(const std::string& strBindingKey);
		
	protected:
		ConnectionBase* getConnection();
		int closeChannel();		
		int declareQueue();
	    int bindQueueToExchange();
		int attachConnection(ConnectionBase* pConn);

		virtual int declareExchange();

	public:
		std::string m_strExchange;
		std::string m_strExchangeType;
		std::string m_strQueue;
		std::string m_strBindingKey;

		int    m_nChanId;

		bool   m_bQueuePersist;
		bool   m_bExchangePersist;	
	protected:
		MessageCallBack m_MsgCallBak;
	private:
		ConnectionBase* m_pConn;

	};
}// end namepace Rabbit

