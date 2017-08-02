#pragma once
#include <string>
#include "ChannelBase.h"

using namespace std;

namespace Rabbit
{
	class Message;
	class RABBIT_API ChannelPublish : public ChannelBase
	{
	public:
		ChannelPublish(void);
		ChannelPublish(ConnectionBase* pConn);

		virtual ~ChannelPublish(void);
		/**
		* @brief open channel when set exchange name
		*/
		virtual int open();
		virtual int reOpen();
		virtual int declareExchange();
		/**
		*  @brief special method for publish
		*/
		int publish(Message& msgObj);

	};

}

