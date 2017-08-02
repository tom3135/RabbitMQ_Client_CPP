/**
* @file     
* @brief    publish/subscribe test cases can not running at the same time
* @details  
*                        
* @author   TangC. goko-712@163.com.  
* @version  1.0.0
* @date     2017-08-01.
*/
#include "stdafx.h"
#include "gtest/gtest.h"
#include <Windows.h>


//#include "testPublish.h"
#include "testSubscribe.h"


int main(int argc, _TCHAR* argv[])
{
	  testing::InitGoogleTest(&argc, argv); 	
	  RUN_ALL_TESTS();

	  system("pause");
}
