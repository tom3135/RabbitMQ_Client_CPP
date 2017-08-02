#pragma once

#include "Util.h"
#include <map>
#include <string>
#include "DataDefine.h"

namespace Rabbit
{
	class ChannelBase; //forward declaration
	class Message;
	class RABBIT_API ConnectionBase: public Util::Thread
	{
	public:
		ConnectionBase(void);
		virtual ~ConnectionBase(void);
		//receive work thread
		void run();	
		int  isRunning();
		void setStartFlag();
		void setStopFlag();
		//register channel
		void registerChannels(ChannelBase* pChan);
		ChannelBase* getChan(int nChanId);
		int  removeChannel(int nChanId);
		//Set the member variable
		int setLogin(const string& host,const string& userName
			                 ,const string& password,int port);
		//override method
		virtual int consumeData(Message& msg);
		virtual int connectServer();

		virtual int reConnect();
		virtual int publish(int nChanId,const char* pBuf,const int nLen
			                     ,const string& routingKey);
		virtual int declareExchange(int nChanId);
		virtual int declareQueue(int nChanId);
		virtual int bindQueueToExchange(int nChanId);
		virtual int openChannel(int nChanId);
		virtual int startConsumer(int nChanId);
		virtual int closeChannel(int nChanId);
	protected:
		virtual int openSocket();
		//reopen all channels
		int  reOpenChannels();
		int  closeChannels();
		
		virtual int closeConn();
		
	protected:
		std::string m_strHostIp;
		std::string m_strUser;
		std::string m_strPassword;
		int m_nPort;
	private:
		std::map<int,ChannelBase*> m_mapChannels;
		int m_nRunning; //0 for stop,1 for running

	};
} //end namespace Rabbit,semicolon is not necessary

