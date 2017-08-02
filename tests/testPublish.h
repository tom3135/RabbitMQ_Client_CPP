/**
* @file     
* @brief    publish side test cases
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

#include "ChannelPublish.h"
#include "ConnectionBase.h"
#include "ConnectionFactory.h"
#include "Message.h"
#include "DataDefine.h"

TEST(ConnectionMake, goSuccess) 
{
	Rabbit::ConnectionBase *pConn1 = nullptr;
	pConn1 = Rabbit::ConnectionFactory::make("Rabbit","127.0.0.1",5672,"test","123456");
	EXPECT_NE(nullptr, pConn1);
}

TEST(ConnectionMake, goFailure) 
{
	Rabbit::ConnectionBase *pConn1 = nullptr;
	Rabbit::ConnectionBase *pConn2 = nullptr;
	Rabbit::ConnectionBase *pConn3 = nullptr;
	Rabbit::ConnectionBase *pConn4 = nullptr;
	Rabbit::ConnectionBase *pConn5 = nullptr;

	pConn1 = Rabbit::ConnectionFactory::make("XXXXXX","127.0.0.1",5672,"test","123456");
	pConn2 = Rabbit::ConnectionFactory::make("Rabbit","192.168.9.2",5672,"test","123456");
	pConn3 = Rabbit::ConnectionFactory::make("Rabbit","127.0.0.1",1234,"test","123456");
	pConn4 = Rabbit::ConnectionFactory::make("Rabbit","127.0.0.1",5672,"wrong","123456");
	pConn5 = Rabbit::ConnectionFactory::make("Rabbit","127.0.0.1",1234,"test","654321");

	EXPECT_EQ(nullptr, pConn1);
	EXPECT_EQ(nullptr, pConn2);
	EXPECT_EQ(nullptr, pConn3);
	EXPECT_EQ(nullptr, pConn4);
	EXPECT_EQ(nullptr, pConn5);
}

TEST(Publish,PublishSuccess)
{
	Rabbit::ConnectionBase *pConn1 = nullptr;
	pConn1 = Rabbit::ConnectionFactory::make("Rabbit","127.0.0.1",5672,"test","123456");
	EXPECT_NE(nullptr, pConn1);

	Rabbit::ChannelPublish *pPubChan = new Rabbit::ChannelPublish(pConn1);
	Rabbit::Message msg;
	std::string strMsg = "qwertyuiop test string";
	msg.setData(strMsg.c_str(),strMsg.size());
	msg.setRoutingKey("data.string");

	pPubChan->setExchange("PUBSUB_EXCHANGE_01",true);
	EXPECT_EQ(0,pPubChan->open());
	EXPECT_EQ(0,pPubChan->publish(msg));
}

TEST(Publish,PublishFailureOne)
{
	Rabbit::ConnectionBase *pConn1 = nullptr;
	pConn1 = Rabbit::ConnectionFactory::make("Rabbit","127.0.0.1",5672,"test","123456");
	EXPECT_NE(nullptr, pConn1);

	Rabbit::ChannelPublish *pPubChan = new Rabbit::ChannelPublish(pConn1);
	Rabbit::Message msg;
	std::string strMsg = "qwertyuiop test string";
	msg.setData(strMsg.c_str(),strMsg.size());
	msg.setRoutingKey("");  //routing key is empty

	pPubChan->setExchange("PUBSUB_EXCHANGE_01",true);
	EXPECT_EQ(0,pPubChan->open());
	EXPECT_NE(0,pPubChan->publish(msg));
}


TEST(Publish,PublishFailureTwo)
{
	Rabbit::ConnectionBase *pConn1 = nullptr;
	pConn1 = Rabbit::ConnectionFactory::make("Rabbit","127.0.0.1",5672,"test","123456");
	EXPECT_NE(nullptr, pConn1);

	Rabbit::ChannelPublish *pPubChan = new Rabbit::ChannelPublish(pConn1);
	Rabbit::Message msg1;
	std::string strMsg1 = "qwertyuiop test string";
	msg1.setData(strMsg1.c_str(),strMsg1.size());
	msg1.setRoutingKey("data.string");

	pPubChan->setExchange("",true); //didn't judgment if exchange name is empty
	EXPECT_NE(0,pPubChan->open());
	//open failed but still call publish
	EXPECT_NE(0,pPubChan->publish(msg1))<<"publish failed";
}