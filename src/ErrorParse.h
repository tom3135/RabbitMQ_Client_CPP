#pragma once
#include "DataDefine.h"
#include "amqp.h"
#include <string>

namespace Rabbit
{
	using namespace std;
	class ErrorParse
	{
	public:
		ErrorParse(void);
		~ErrorParse(void);
		/**
		* @brief parse rabbitmq rpc reply in amqp_rpc_reply_t
		*/
		static int getReplyCode(amqp_rpc_reply_t replyRet);
		static int reDefineCode(int amqpCode);

		ErrorMsg getErrorMsg(int nErrorCode);
		void showErrorMsg(ErrorMsg errorMsg);
		void showErrorMsgByCode(int nErrorCode);
	};

} //end namespace