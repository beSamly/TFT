#pragma once
#include <concepts>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <regex>
#include <string>
#include <map>
#include <queue>
#include <mutex>

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#include <windows.h>

//#pragma comment(lib, "ws2_32.lib")
//
//#define _SILENCE_CXX20_CISO646_REMOVED_WARNING
//#define _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS
//
//#ifdef _DEBUG
//#pragma comment(lib, "Protobuf\\_Debug\\libprotobufd.lib")
//#pragma comment(lib, "ServerCoreLibrary\\Debug\\ServerCoreLibrary.lib")
//#pragma comment(lib, "SharedProtobuf\\Debug\\SharedProtobuf.lib")
//#pragma comment(lib, "PhysicsEngine\\Debug\\PhysicsEngine.lib")
//#else
//#pragma comment(lib, "Protobuf\\_Release\\libprotobuf.lib")
//#pragma comment(lib, "ServerCoreLibrary\\Release\\ServerCoreLibrary.lib")
//#pragma comment(lib, "ServerCoreLibrary\\Release\\SharedProtobuf.lib")
//#pragma comment(lib, "PhysicsEngine\\Release\\PhysicsEngine.lib")
//#endif

#define STR(arg) string(arg)

using std::function;
using std::list;
using std::make_pair;
using std::make_shared;
using std::make_unique;
using std::map;
using std::mutex;
using std::queue;
using std::shared_ptr;
using std::string;
using std::vector;

template <typename T>
using sptr = std::shared_ptr<T>;

template <typename T>
using uptr = std::unique_ptr<T>;

template <typename T>
using wptr = std::weak_ptr<T>;

/*-------------------------
|		  ∏≈≈©∑Œ		      |
--------------------------*/
#define USE_MUL_LOCK(count) std::shared_mutex _locks[count];
#define USE_LOCK USE_MUL_LOCK(1)

#include "SharedMutexGuard.h"
#define READ_LOCK_IDX(idx) SMReadLockGuard readLockGuard_##idx(_locks[idx]);
#define WRITE_LOCK_IDX(idx) SMWriteLockGuard writeLockGuard_##idx(_locks[idx]);

#define WRITE_LOCK WRITE_LOCK_IDX(0)
#define READ_LOCK READ_LOCK_IDX(0)

/*---------------
          Crash
---------------*/

#define CRASH(cause)                                                                                                   \
    {                                                                                                                  \
        uint32* crash = nullptr;                                                                                       \
        __analysis_assume(crash != nullptr);                                                                           \
        *crash = 0xDEADBEEF;                                                                                           \
    }

#define ASSERT_CRASH(expr)                                                                                             \
    {                                                                                                                  \
        if (!(expr))                                                                                                   \
        {                                                                                                              \
            CRASH("ASSERT_CRASH");                                                                                     \
            __analysis_assume(expr);                                                                                   \
        }                                                                                                              \
    }