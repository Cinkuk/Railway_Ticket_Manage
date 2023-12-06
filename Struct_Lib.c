// 本文件用以存放项目所需的结构体定义和常量定义
//
// Test Status: Undo
// Code Status: Working

#define OK 1
#define ERROR 0
#define OVERFLOW -10
#define EMPTY -11
#define NOSPACE -12

#define True 1
#define False 0

#define STATIONNAME 20

// 存储途径站点名字的链式串
typedef struct StopName {
	char name[STATIONNAME];
	struct StopName* next;
}StopName;



}SUB_TrainInfo;
