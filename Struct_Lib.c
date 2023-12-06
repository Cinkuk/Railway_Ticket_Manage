// 本文件用以存放项目所需的结构体定义和常量定义
//
// Test Status: Undo
// Code Status: Undo

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

// 存储各个站点发车时间
typedef struct LeaveTime {
	char name[STATIONNAME]; // 站点名称
	int hour; // 发车xia
}LeaveTime;
// 存储车次信息
typedef struct SUB_TrainInfo {
	char TrainNum[6]; // 车次
	char Start[STATIONNAME]; // 始发站
	struct StopName Stop; // 途经站
	char End[STATIONNAME]; // 终到站

}SUB_TrainInfo;
