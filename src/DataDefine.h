/**
* @file     
* @brief  definition header file
*                        
* @author   TangC
* @version  1.0.0   
* @date     2017-07-26.
*/
#pragma once
#include <stdio.h>
#include <string>

typedef unsigned char byte;

#ifdef RABBITMQ_CLIENT_EXPORTS
  #define RABBIT_API __declspec(dllexport)
#else
  #define RABBIT_API __declspec(dllimport)
#endif

/**
** @brief error code and description
*/
typedef struct ErrorMsg{
	int nErrorCode;         
	std::string strErrorMsg;
	ErrorMsg()
	{
		nErrorCode = 0;
		strErrorMsg = "";
	}

	ErrorMsg& operator=(ErrorMsg& other)
	{
		nErrorCode = other.nErrorCode;
		strErrorMsg = other.strErrorMsg;
		return *this;
	}
}ErrorMsg;

/**
* @enum   E_MSG_TYPE
* @brief  data type of message when publish them
*/
enum E_MSG_TYPE
{
	E_BINARY = 0,  //!< as binary
	E_STREAM,      //!< as byte stream
	E_XML,         //!< as xml
	E_JSON,        //!< as json
	E_TXT,         //!< as text
};

typedef enum LMQErrorCode{
	LMQ_UNKOWN_EXCEPTION = 0x0313,       //!< 787 unknown error
	LMQ_NET_CONNECTING_ERR = 0x01F4,     //!< 500 can not connect to rabbit server
	LMQ_NET_CONNECED_ERR = 0x01F5,       //!< 501 disconnect from rabbit server
	LMQ_CONNECTION_NOT_EXIST = 0x0302,   //!< 770 the connection pointer is null
	LMQ_CONFIG_FILE_READ_ERR = 0x0303,   //!< 771 the configuration file failed to read
	LMQ_DECLARE_EXCHANGE_ERR = 0x0304,   //!< 772 declare exchange failed
	LMQ_DECLARE_QUEUE_ERR = 0x0305,      //!< 773 declare queue failed
	LMQ_BING_ERR = 0x0306,               //!< 774 queue and exchange binding failed
	LMQ_BUF_TOO_LONG = 0x0307,           //!< 775 buffer too long
	LMQ_BUF_TOO_SMALL = 0x0308,          //!< 776 buffer too small
	LMQ_BUF_EMPTY_WITH_SEND = 0x0309,    //!< 777 buffer is empty
	LMQ_WAIT_SIMPLE_FRAME_ERR = 0x030A,  //!< 778 wait simple frame failed
	LMQ_CHANNEL_CLOSE = 0x030B,          //!< 779 the channel closed
	LMQ_CONNECTION_CLOSE = 0x030C,       //!< 780 the connection closed
	LMQ_CALLBACK_METHOD_NULL = 0x030D,   //!< 781 The callback function pointer is null
	LMQ_SET_PROPERTY_ERR = 0x030F,       //!< 783 set amqp property failed
	LMQ_RPC_CALL_REQUEST_ERR = 0x0310,   //!< 784 RPC rquest failded
	LMQ_RPC_CALL_RESPONSE_ERR = 0x0311,  //!< 785 RPC response failed
	LMQ_GET_EMPTYDATA_ERR = 0x0312,      //!< 786 received empty message
	LMQ_QUEUE_EXCHANGE_EMPTY = 0x0314,   //!< 788 queue name or exchange name is empty
	LMQ_CONSUMER_ERR = 0x0315,			 //!< 789 start consumer failed
	LMQ_OPERATION_TIME_OUT = 0x0316,     //!< 790 operation timeout
	LMQ_PUBLISH_ERR = 0x0317             //!< 791 
}LMQErrorCode;