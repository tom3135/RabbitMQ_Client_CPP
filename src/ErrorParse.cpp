#include "ErrorParse.h"
#include <iostream>


Rabbit::ErrorParse::ErrorParse(void)
{
}


Rabbit::ErrorParse::~ErrorParse(void)
{
}

int Rabbit::ErrorParse::getReplyCode( amqp_rpc_reply_t replyRet )
{
	ErrorMsg amqpErr;
	amqpErr.nErrorCode = 0;
	amqpErr.strErrorMsg = "";
	if (AMQP_RESPONSE_SERVER_EXCEPTION ==replyRet.reply_type)
	{
		if (AMQP_CONNECTION_CLOSE_METHOD == replyRet.reply.id)
		{
			amqp_connection_close_t *conCloseResult =  (amqp_connection_close_t *)replyRet.reply.decoded;
			int replyCode = conCloseResult->reply_code;//AMQP_ACCESS_REFUSED,AMQP_NOT_ALLOWED
			string strMsg((char*)conCloseResult->reply_text.bytes,conCloseResult->reply_text.len);
			int nFind = strMsg.find_first_of("-",0);
			string strErrorName = strMsg.substr(0,nFind);
			amqpErr.nErrorCode = replyCode;
			amqpErr.strErrorMsg = strErrorName;
		}
		else if(AMQP_CHANNEL_CLOSE_METHOD == replyRet.reply.id)
		{
			amqp_channel_close_t *conCloseResult =  (amqp_channel_close_t *)replyRet.reply.decoded;
			int replyCode = conCloseResult->reply_code;//AMQP_PRECONDITION_FAILED
			string strMsg((char*)conCloseResult->reply_text.bytes,conCloseResult->reply_text.len);
			int nFind = strMsg.find_first_of("-",0);
			string strErrorName = strMsg.substr(0,nFind);
			amqpErr.nErrorCode = replyCode;
			amqpErr.strErrorMsg = strErrorName;
		}
	}
	else if(AMQP_RESPONSE_LIBRARY_EXCEPTION == replyRet.reply_type)
	{
		amqpErr.nErrorCode = replyRet.library_error;
		amqpErr.strErrorMsg = amqp_error_string2(replyRet.library_error);
	}
	else
	{
		//get empyt method under put/get mode
		if (AMQP_BASIC_GET_EMPTY_METHOD == replyRet.reply.id)
		{
			amqp_basic_get_empty_t *reEmpty = (amqp_basic_get_empty_t*)replyRet.reply.decoded;
			amqp_bytes_t strClusterId = amqp_bytes_malloc_dup(reEmpty->cluster_id);
			amqp_bytes_free(strClusterId);
			amqpErr.nErrorCode = LMQ_GET_EMPTYDATA_ERR;
		}
	}
	
	return reDefineCode(amqpErr.nErrorCode);
	
}
/**
*@brief redefine amqp error code
*/
int Rabbit::ErrorParse::reDefineCode( int amqpCode )
{
	int nLmqCode = 0; //normal
	switch(amqpCode)
	{
	case 0:           //many error code not catach yet, put them in defalt case
		nLmqCode = 0; //this one is to prevent 0 as an unknown error.
		break;        
	case AMQP_ACCESS_REFUSED:
		nLmqCode = amqpCode;
		break;
	case AMQP_CHANNEL_ERROR:
		nLmqCode = LMQ_CHANNEL_CLOSE;
		break;
	case AMQP_NOT_ALLOWED:
		nLmqCode = amqpCode;
		break;
	case AMQP_STATUS_TIMEOUT:
		nLmqCode = LMQ_OPERATION_TIME_OUT;
		break;
	case AMQP_STATUS_UNEXPECTED_STATE:
		nLmqCode = LMQ_UNKOWN_EXCEPTION; 
		break;
	case AMQP_STATUS_SOCKET_ERROR:
		nLmqCode = LMQ_NET_CONNECED_ERR; // as 501
		break;
	case AMQP_STATUS_CONNECTION_CLOSED:
		nLmqCode = LMQ_NET_CONNECED_ERR; // as 501
		break;
	case LMQ_GET_EMPTYDATA_ERR:
		nLmqCode = LMQ_GET_EMPTYDATA_ERR;// already redefine
		break;
	default:
		nLmqCode = LMQ_UNKOWN_EXCEPTION;
		break;
	}

	return nLmqCode;
}

ErrorMsg Rabbit::ErrorParse::getErrorMsg( int nErrorCode )
{
	ErrorMsg errorMsg;
	errorMsg.nErrorCode = nErrorCode;
	switch(nErrorCode)
	{
	case AMQP_ACCESS_REFUSED:
		errorMsg.strErrorMsg = "Access Refused";
		break;
	case AMQP_NOT_ALLOWED:
		errorMsg.strErrorMsg = "Not Allowed";
		break;
	case AMQP_CHANNEL_ERROR:
		errorMsg.strErrorMsg = "Channel Error";
		break;
	case LMQ_NET_CONNECTING_ERR:
		errorMsg.strErrorMsg = "network error or connection not init";
		break;
	case LMQ_CONNECTION_NOT_EXIST:
		errorMsg.strErrorMsg = "connection handle not exist";
		break;
	case LMQ_CONFIG_FILE_READ_ERR:
		errorMsg.strErrorMsg = "config file read error";
		break;
	case LMQ_DECLARE_EXCHANGE_ERR:
		errorMsg.strErrorMsg = "declare exchange error";
		break;
	case LMQ_DECLARE_QUEUE_ERR:
		errorMsg.strErrorMsg = "declare queue error";
		break;
	case LMQ_BING_ERR:
		errorMsg.strErrorMsg = "bing exchange and queue error";
		break;
	case LMQ_BUF_TOO_LONG:
		errorMsg.strErrorMsg = "the buffer too long for send";
		break;
	case LMQ_BUF_TOO_SMALL:
		errorMsg.strErrorMsg = "the buffer too smal for receive";
		break;
	case LMQ_BUF_EMPTY_WITH_SEND:
		errorMsg.strErrorMsg = "the buffer is empty for send";
		break;
	case LMQ_WAIT_SIMPLE_FRAME_ERR:
		errorMsg.strErrorMsg = "waite simple frame error";
		break;
	case LMQ_CHANNEL_CLOSE:
		errorMsg.strErrorMsg = "channel closed";
		break;
	case LMQ_CONNECTION_CLOSE:
		errorMsg.strErrorMsg = "connection closed";
		break;
	case LMQ_CALLBACK_METHOD_NULL:
		errorMsg.strErrorMsg = "call back method point is null";
		break;
	case LMQ_SET_PROPERTY_ERR:
		errorMsg.strErrorMsg = "error occured when set property";
		break;
	case LMQ_RPC_CALL_REQUEST_ERR:
		errorMsg.strErrorMsg = "error occured when rpc caller send request";
		break;
	case LMQ_RPC_CALL_RESPONSE_ERR:
		errorMsg.strErrorMsg = "error occured when rpc caller get response";
		break;
	case LMQ_OPERATION_TIME_OUT:
		errorMsg.strErrorMsg = "Operation timed out";
		break;
	case LMQ_NET_CONNECED_ERR:
		errorMsg.strErrorMsg = "connection time out or frame error";
		break;
	case LMQ_GET_EMPTYDATA_ERR:
		errorMsg.strErrorMsg = "server has no data";
		break;
	case LMQ_QUEUE_EXCHANGE_EMPTY:
		errorMsg.strErrorMsg = "queue name(exchange name) is empty(NULL)";
		break;
	case LMQ_CONSUMER_ERR:
		errorMsg.strErrorMsg = "basic consumer start error";
		break;
	default:
		errorMsg.strErrorMsg = "unkown exception";
		break;
	}

	return errorMsg;
}

void Rabbit::ErrorParse::showErrorMsg( ErrorMsg errorMsg )
{
	std::cout<<"error : "<<errorMsg.nErrorCode;
	std::cout<<" :"<<errorMsg.strErrorMsg<<std::endl;
}

void Rabbit::ErrorParse::showErrorMsgByCode( int nErrorCode )
{
	ErrorMsg errorMsg = getErrorMsg(nErrorCode);
	showErrorMsg(errorMsg);
}
