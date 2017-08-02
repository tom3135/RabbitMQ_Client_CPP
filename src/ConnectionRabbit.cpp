#include "ConnectionRabbit.h"
#include "RabbitConfig.h"
#include "amqp_framing.h"
#include "amqp_tcp_socket.h"
#include "DataDefine.h"
#include "ErrorParse.h"
#include "ChannelBase.h"
#include "Message.h"


Rabbit::ConnectionRabbit::ConnectionRabbit(void):ConnectionBase()
{
	m_pConnState = NULL;
	m_pSocket = NULL;
}


Rabbit::ConnectionRabbit::~ConnectionRabbit(void)
{
	closeConn();
}


void Rabbit::ConnectionRabbit::initFromConfig()
{
	m_strHostIp = RabbitConfig::getInstance()->m_hostIp;
	m_nPort = RabbitConfig::getInstance()->m_nPort;
	m_strUser = RabbitConfig::getInstance()->m_userName;
	m_strPassword = RabbitConfig::getInstance()->m_password;
}

int Rabbit::ConnectionRabbit::connectServer()
{
	//first of all open a tcp socket
	int nOpenSocket = openSocket();
	if (0 != nOpenSocket)
	{
		return nOpenSocket;
	}
	//second login with usrname and password
	amqp_rpc_reply_t loginRet = amqp_login(m_pConnState,"/",0,131072,0
						,AMQP_SASL_METHOD_PLAIN
						,m_strUser.c_str()
						,m_strPassword.c_str());

	return ErrorParse::getReplyCode(loginRet);
}

int Rabbit::ConnectionRabbit::openSocket()
{
	m_pConnState = amqp_new_connection();
	m_pSocket = amqp_tcp_socket_new(m_pConnState);
	if (NULL == m_pSocket)
	{
		return LMQ_NET_CONNECTING_ERR;
	}

	struct timeval timeInterVal;
	timeInterVal.tv_usec = 0;
	timeInterVal.tv_sec = 2;
	int nStatus;
	nStatus = amqp_socket_open_noblock(m_pSocket,m_strHostIp.c_str()
										,m_nPort,&timeInterVal);
	if (AMQP_STATUS_OK != nStatus)
	{
		//open socket failed,return 500 error code
		return LMQ_NET_CONNECTING_ERR;
	}
	return 0;
}

amqp_connection_state_t Rabbit::ConnectionRabbit::getConn()
{
	if (NULL == m_pConnState)
	{
		connectServer();
	}

	return m_pConnState;
}

int Rabbit::ConnectionRabbit::closeConn()
{
	amqp_rpc_reply_t ret = amqp_connection_close(m_pConnState, AMQP_REPLY_SUCCESS);
	amqp_destroy_connection(m_pConnState);
	m_pConnState = nullptr;

	return ErrorParse::getReplyCode(ret);
}
/** 
* @brief tcp connection closed,start reconnect
*       
* @return 0 for reconnect success, not 0 stand for failed
*/
int Rabbit::ConnectionRabbit::reConnect()
{
	//close all channel and tcp connection
	closeChannels();
	closeConn();

	//reconnect rabbitmq server
	int nRet = connectServer();

	//reopen all channel
	if (0 == nRet)
	{
		reOpenChannels();
	}
	return nRet;
}
/** 
* @brief declare exchange using rabbitmq-c api
*       
* @return 0 for successed, not 0 stand for failed
*/
int Rabbit::ConnectionRabbit::declareExchange(int nChanId)
{
	ChannelBase* pChan = getChan(nChanId);
	if (NULL == pChan)
	{
		return LMQ_DECLARE_EXCHANGE_ERR;
	}
	if (NULL == m_pConnState)
	{
		return LMQ_CONNECTION_NOT_EXIST;
	}
	//now set exchange peropty is durable and not auto delete
	bool bAutoDelete = false;
	bool bNeedDurable = true;
	//call amqp_exchange_declare api
	amqp_exchange_declare_ok_t *declareOK = 
		amqp_exchange_declare(m_pConnState, pChan->getId()
		,amqp_cstring_bytes(pChan->m_strExchange.c_str())
		,amqp_cstring_bytes(pChan->m_strExchangeType.c_str())
		,0,bNeedDurable,bAutoDelete,0,amqp_empty_table);
	if (!declareOK)
	{
		int nRet = ErrorParse::getReplyCode(amqp_get_rpc_reply(m_pConnState));
		return LMQ_DECLARE_EXCHANGE_ERR;
	}
	//! get rpc response, judge whether declare is successful or not.
	return ErrorParse::getReplyCode(amqp_get_rpc_reply(m_pConnState));
}

int Rabbit::ConnectionRabbit::declareQueue(int nChanId)
{
	ChannelBase* pChan = getChan(nChanId);
	if (NULL == pChan)
	{
		return LMQ_DECLARE_QUEUE_ERR;
	}
	if (NULL == m_pConnState)
	{
		return LMQ_CONNECTION_NOT_EXIST;
	}
	//durable means not auto delete
	bool bAutoDelete = !pChan->m_bQueuePersist;
	bool bNeedDurable = pChan->m_bQueuePersist;
	//declare queue
	amqp_queue_declare_ok_t *pDeclareOk = NULL;
	pDeclareOk = amqp_queue_declare(m_pConnState, pChan->getId()
		                           ,amqp_cstring_bytes(pChan->m_strQueue.c_str())
		                           ,0, bNeedDurable, false,bAutoDelete, amqp_empty_table);
	if (NULL == pDeclareOk)
	{
		int nCode = ErrorParse::getReplyCode(amqp_get_rpc_reply(m_pConnState));
		return LMQ_DECLARE_QUEUE_ERR;
	}
	return 0;
}

int Rabbit::ConnectionRabbit::bindQueueToExchange(int nChanId)
{
	ChannelBase* pChan = getChan(nChanId);
	if (NULL == pChan)
	{
		return LMQ_BING_ERR;
	}
	if (NULL == m_pConnState)
	{
		return LMQ_CONNECTION_NOT_EXIST;
	}
	amqp_queue_bind_ok_t* pBindOk = NULL;
	pBindOk = amqp_queue_bind(m_pConnState,pChan->getId()
							,amqp_cstring_bytes(pChan->m_strQueue.c_str())
							,amqp_cstring_bytes(pChan->m_strExchange.c_str())
							,amqp_cstring_bytes(pChan->m_strBindingKey.c_str())
							, amqp_empty_table);
	if (NULL == pBindOk)
	{
		int nCode = ErrorParse::getReplyCode(amqp_get_rpc_reply(m_pConnState));
		return LMQ_BING_ERR;
	}
	return 0;
}

int Rabbit::ConnectionRabbit::openChannel(int nChanId)
{
	ChannelBase* pChan = getChan(nChanId);
	if (NULL == pChan)
	{
		return LMQ_NET_CONNECTING_ERR;
	}
	if (NULL == m_pConnState)
	{
		return LMQ_CONNECTION_NOT_EXIST;
	}
	amqp_channel_open_ok_t *isOk = amqp_channel_open(m_pConnState,pChan->getId());
	if (NULL == isOk)
	{
		return LMQ_NET_CONNECTING_ERR;
	}
	amqp_rpc_reply_t reply = amqp_get_rpc_reply(m_pConnState);
	return ErrorParse::getReplyCode(reply);
}

int Rabbit::ConnectionRabbit::publish( int nChanId,const char* pBuf,const int nLen 
	                            ,const string& routingKey)
{
	if (NULL == m_pConnState)
	{
		return LMQ_CONNECTION_NOT_EXIST;
	}
	ChannelBase* pChan = getChan(nChanId);
	if (pChan->m_strExchange.empty())
	{
		return LMQ_QUEUE_EXCHANGE_EMPTY;
	}

	amqp_basic_properties_t props;
	// set headers flag
	props._flags = AMQP_BASIC_HEADERS_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
	props.content_type = amqp_cstring_bytes("text/plain");
	props.delivery_mode = 2; /* persistent delivery mode */
	props.reply_to = amqp_cstring_bytes(pChan->m_strQueue.c_str());
	if (props.reply_to.bytes == NULL){
		fprintf(stderr, "Out of memory while copying queue name");
		return -1;
	}
	
	amqp_bytes_t message_bytes;
	message_bytes.len = nLen;
	message_bytes.bytes = (void *)pBuf;

	// rabbitmq-c will report error if routingKey is empty or NULL
	int nRet = amqp_basic_publish(m_pConnState,
		pChan->getId(),
		amqp_cstring_bytes(pChan->m_strExchange.c_str()),
		amqp_cstring_bytes(routingKey.c_str()),
		0,
		0,
		&props,
		message_bytes);
	//redefine error code
	//if some error not being catched will be set as 787 
	return ErrorParse::reDefineCode(nRet);
}
//receive message and put in Message object
int Rabbit::ConnectionRabbit::consumeData( Message& msg )
{
    amqp_rpc_reply_t ret;
	amqp_maybe_release_buffers(m_pConnState);

	struct timeval timeVal;
	timeVal.tv_usec = 0;
	timeVal.tv_sec = 2;
	ret = amqp_consume_message(m_pConnState, &msg.m_envelope, &timeVal, 0);

    if (AMQP_RESPONSE_NORMAL == ret.reply_type)
    { 
		msg.m_nChannId = msg.m_envelope.channel;
		msg.m_nMsgLen = msg.m_envelope.message.body.len;

		msg.setConsumerTag(msg.m_envelope.consumer_tag);
		msg.setRoutingKey(msg.m_envelope.routing_key);
		msg.setExchange(msg.m_envelope.exchange);

		//amqp_destroy_envelope(&envelope);
    }
    else
    {
		msg.m_nChannId = msg.m_envelope.channel;
		return ErrorParse::getReplyCode(ret);
    }
    return 0;
}

int Rabbit::ConnectionRabbit::startConsumer(int nChanId)
{
	ChannelBase* pChan = getChan(nChanId);
	if (NULL == pChan)
	{
		return LMQ_CONSUMER_ERR;
	}
	if (NULL == m_pConnState)
	{
		return LMQ_CONNECTION_NOT_EXIST;
	}

	bool no_ack = RabbitConfig::getInstance()->m_bAutoAck;
	amqp_basic_consume(m_pConnState,pChan->getId(), amqp_cstring_bytes(pChan->m_strQueue.c_str())
		,amqp_empty_bytes, 0, no_ack, 0, amqp_empty_table);

	int nReplyCode = ErrorParse::getReplyCode(amqp_get_rpc_reply(m_pConnState));
	if (0 != nReplyCode)
	{
		return LMQ_CONSUMER_ERR;
	}
	return 0;

}
/**
* @brief close channel 
*/
int Rabbit::ConnectionRabbit::closeChannel(int nChanId)
{
	ChannelBase* pChan = getChan(nChanId);
	if (NULL == pChan)
	{
		return 0;
	}
	if (NULL == m_pConnState)
	{
		return LMQ_CONNECTION_NOT_EXIST;
	}
	amqp_rpc_reply_t reply = amqp_channel_close(m_pConnState,nChanId,AMQP_REPLY_SUCCESS);

	return ErrorParse::getReplyCode(reply);
}
