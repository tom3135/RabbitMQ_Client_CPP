/**
* @file     
* @brief    factory for RabbitMQ connection;only hsa one static method --"make"
*                        
* @author   TangC
* @version  1.0.0.   
* @date     2017-07-28.
*/
#pragma once
#include "Mutex.h"
#include "Util.h"
#include <string.h>
#include "ConnectionBase.h"


using namespace std;
using namespace Util;

namespace Rabbit
{
	class Rabbit::ConnectionBase;
	class RABBIT_API ConnectionFactory
	{
	public:
		class Garbage
		{
		public:
			~Garbage() {
				if(m_instance != NULL) {
					delete m_instance;
				}
			}
		};

		static ConnectionFactory* getInstance();
		~ConnectionFactory(void);

		static Rabbit::ConnectionBase* make(const string &strConnType
			,const string &strHostIp
			,int nPort,const string &strUser
			,const string &strPassword);


	private:
		ConnectionFactory(void);
		static ConnectionFactory *m_instance;

		static Util::Mutex m_mutex;
		static Garbage m_gc;

	};

}// end namespace Rabbit

