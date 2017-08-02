// testSub.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <memory.h>

#include "ConnectionBase.h"
#include "ConnectionFactory.h"
#include "ChannelSubscribe.h"
#include "Message.h"

#include <iostream>
using namespace std;
int nCount = 0;

int msgCallBak(Rabbit::Message &message)
{
	//std::cout<<message.getExchange()<<" "<<message.getRoutingKey()<<std::endl;
	nCount++;
	cout<<"msg : "<<message.getMessage()<<" "<<nCount<<endl;
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Rabbit::ConnectionBase *pConn = nullptr;
	pConn = Rabbit::ConnectionFactory::make("Rabbit","127.0.0.1",5672,"test","123456");

	Rabbit::ChannelSubscribe *pChan = new Rabbit::ChannelSubscribe(pConn);
	pChan->setCallBack(msgCallBak);

	pChan->setExchange("PUBSUB_EXCHANGE_01",true);
	pChan->setQueue("tangc_01",true);
	pChan->setBindingKey("*.string");
	int nRet = pChan->open();

	while(1)
	{
		Sleep(5000000);
	}
	system("pause");
	return 0;
}

