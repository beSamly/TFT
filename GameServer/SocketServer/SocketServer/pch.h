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

#define _SILENCE_CXX20_CISO646_REMOVED_WARNING
#define _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS

#ifdef _DEBUG
#pragma comment(lib, "Protobuf\\_Debug\\libprotobufd.lib")
#pragma comment(lib, "ServerCoreLibrary\\Debug\\ServerCoreLibrary.lib")
#pragma comment(lib, "SharedProtobuf\\Debug\\SharedProtobuf.lib")
#pragma comment(lib, "PhysicsEngine\\Debug\\PhysicsEngine.lib")
#else
#pragma comment(lib, "Protobuf\\_Release\\libprotobuf.lib")
#pragma comment(lib, "ServerCoreLibrary\\Release\\ServerCoreLibrary.lib")
#pragma comment(lib, "ServerCoreLibrary\\Release\\SharedProtobuf.lib")
#pragma comment(lib, "PhysicsEngine\\Release\\PhysicsEngine.lib")
#endif

#define STR(arg) string(arg)

using std::function;
using std::list;
using std::make_pair;
using std::make_shared;
using std::make_unique;
using std::map;
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

#include "GlobalPch.h"
#include "OperationType.h"
#include "SocketServer.h"
#include "TLS.h"
#include "TargetType.h"
#include "TriggerType.h"

// using ColumnRef = std::shared_ptr<class Column>;
// using JobQueueRef = std::shared_ptr<class JobQueue>;
// using JobRef = std::shared_ptr<class Job>;
// using JobDataRef = std::shared_ptr<class JobData>;
// using CallbackType = std::function<void()>;

// template<typename T>
// using EquipItemRef = std::shared_ptr<class EquipItem>;
//
// using PlayerRef = std::shared_ptr<class Player>;
// using AccountRef = std::shared_ptr<class Account>;
// using DBConnectionGaurdRef = std::shared_ptr<class DBConnectionGaurd>;

//게임플레이 관련
