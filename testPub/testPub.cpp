// testPub.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

#include "ChannelPublish.h"
#include "ConnectionBase.h"
#include "ConnectionFactory.h"
#include "Message.h"
#include "DataDefine.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Rabbit::ConnectionBase *pConn = nullptr;
	pConn = Rabbit::ConnectionFactory::make("Rabbit","127.0.0.1",5672,"test","123456");
	
	Rabbit::ChannelPublish *pPubChan = new Rabbit::ChannelPublish(pConn);
	Rabbit::Message msg;
	std::string strMsg = "qwertyuiop";

	msg.setData(strMsg.c_str(),strMsg.size());
	msg.setRoutingKey("data.string");

	pPubChan->setExchange("PUBSUB_EXCHANGE_01",true);
	int nRet1 = pPubChan->open();

	int nLoop = 0;
	while(nLoop < 8000)
	{
		int nRet2 = pPubChan->publish(msg);

		nLoop++;
	}

	
	system("pause");
	return 0;
}

