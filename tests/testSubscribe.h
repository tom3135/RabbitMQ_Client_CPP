/**
* @file     
* @brief    subscribe side test cases
* @details
*                        
* @author   TangC. goko-712@163.com.  
* @version  1.0.0  
* @date     2017-08-01.
*/
#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

#include "ChannelSubscribe.h"
#include "ConnectionBase.h"
#include "ConnectionFactory.h"
#include "Message.h"
#include "DataDefine.h"

int nCount = 0;
int msgCallBak1(Rabbit::Message &message)
{
	std::cout<<message.getMessage();
	EXPECT_EQ("PUBSUB_EXCHANGE_01",message.getExchange());
	return 0;
}

int msgCallBak2(Rabbit::Message &message)
{
	std::cout<<message.getMessage();
	EXPECT_EQ("PUBSUB_EXCHANGE_01",message.getExchange());
	return 0;
}

TEST(Subscribe, goSuccess) 
{
	Rabbit::ConnectionBase *pConn = nullptr;
	pConn = Rabbit::ConnectionFactory::make("Rabbit","127.0.0.1",5672,"test","123456");

	Rabbit::ChannelSubscribe *pChan = new Rabbit::ChannelSubscribe(pConn);
	pChan->setCallBack(msgCallBak1);

	pChan->setExchange("PUBSUB_EXCHANGE_01",true);
	pChan->setQueue("tangc_01",true);
	pChan->setBindingKey("*.string");
	EXPECT_EQ(0,pChan->open());
}

TEST(Subscribe, goFailure) 
{
	Rabbit::ConnectionBase *pConn = nullptr;
	pConn = Rabbit::ConnectionFactory::make("Rabbit","127.0.0.1",5672,"test","123456");

	Rabbit::ChannelSubscribe *pChan = new Rabbit::ChannelSubscribe(pConn);
	pChan->setCallBack(msgCallBak2);

	pChan->setExchange("",true);
	pChan->setQueue("",true);
	pChan->setBindingKey("");
	EXPECT_NE(0,pChan->open());
}

