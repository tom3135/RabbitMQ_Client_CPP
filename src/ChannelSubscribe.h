#pragma once
#include <string>
#include "ChannelBase.h"

using namespace std;

namespace Rabbit
{
	class RABBIT_API ChannelSubscribe: public ChannelBase
	{
	public:
		ChannelSubscribe(void);
		ChannelSubscribe(ConnectionBase* pConn);
		virtual ~ChannelSubscribe(void);
		/**
		* @brief open channel when set exchange name,queue name,and binding key
		*/
        virtual int open();
		virtual int reOpen();
		virtual int declareExchange();
		/**
		*  @brief unique method to turn on the consumer
		*/
		int startConsumer();
		/**
		*  @brief unique method to set callback function
		*         but the msgCallBak is not Thread safety
		*         cannot set the same function to diffrent channels
		*/
		int setCallBack(MessageCallBack msgCallBak);

	};

}

