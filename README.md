# RabbitMQ_Client_CPP

RabbitMQ_Client is a C ++ version of the client based on the RabbitMQ-C package;
The client with experimental nature, incomplete, currently only support the publish/subscribe mode, 
support tcp reconnection, the architecture is divided into 2 layer(channel and connection).

class ChannelPublish and class ChannelSubscribe was inherited from the ChannelBase.
connection implementation class ConnectionRabbit inherited from ConnectionBase.
because when channel and connection call each other it's better use interface rather than the specific implementation method.

this client uses the configuration file class and thread class in the ICE Util。

ChannelBase is a thread，use thread can simulate asynchronous receive mechanisms, 
also can support multiple channels work on the same connection, and channels do not interfere with each other。
we know RabbitMQ-C when multiple channels shared connection, the connection layer does not distinguish between which channel the message belongs to.

all channel objects are registered to the thread (ConnectionBase), the thread loop to receive the message, 
and put message into the corresponding channel.
then the channel will call the callback function which already set, emit the message to the final customer.in accordance with this process, 
channel does not blocking the main thread。the developer client does not need to create a worker thread for it。

RabbitMQ_Client redefines part of the RabbitMQ-C error code, which is serviced by a parsing class.
Provides two sample programs testPub and testSub, its easy to use。

due to the lack of time and capacity, did not provide CMake configuration, only VS2010 project files, 
I didn't test if it can compiled through in Linux. 
thanks! and excuse my poor english.