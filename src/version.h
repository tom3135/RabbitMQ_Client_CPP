#pragma once
#define RELEASE_VER 1			  // 0: beta version; 1: release version
#define RELEASE_DATE "2017-07-27"

#define RELEASE_VER_MAIN  0
#define RELEASE_VER_MAIN2 9
#define RELEASE_VER_SUB   0 

// version number (string)
#define TOSTRING2(arg) #arg
#define TOSTRING(arg) TOSTRING2(arg)

#define FILE_VER_STR TOSTRING(RELEASE_VER_MAIN) "." TOSTRING(RELEASE_VER_MAIN2) "." TOSTRING(RELEASE_VER_SUB)
