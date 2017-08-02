/**
* @file     
* @brief    RabbitMQ connection implementation class, inherited from
*           ConnectionBase
*                        
* @author   TangC
* @version  1.0.0.   
* @date     2017-07-28.
*/
#pragma once

#include <string>
#include "amqp.h"
#include "ConnectionBase.h"
using namespace std;

namespace Rabbit
{
	class RABBIT_API ConnectionRabbit : public ConnectionBase
	{
	public:
		ConnectionRabbit(void);
		~ConnectionRabbit(void);
		/**
		* @brief the information for connecting come from configuration file
		*/
		void initFromConfig();
		amqp_connection_state_t getConn();

		virtual int connectServer();
		virtual int reConnect();

		virtual int closeChannel(int nChanId);
		virtual int closeConn();
		

		virtual int declareExchange(int nChanId);
		virtual int declareQueue(int nChanId);
		virtual int bindQueueToExchange(int nChanId);
		virtual int openChannel(int nChanId);
		virtual int consumeData(Message& msg);
		virtual int startConsumer(int nChanId);
		virtual int publish(int nChanId,const char* pBuf,const int nLen ,const string& routingKey);
	protected:		
		virtual int openSocket();
	private:
		amqp_connection_state_t m_pConnState;
		amqp_socket_t *m_pSocket;
	};

}