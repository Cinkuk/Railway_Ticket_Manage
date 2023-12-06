// 本文件用于存放车票、车次管理的函数
// 所依赖的关键变量存放于Variables_Lib.c中
// 本文件的函数名以'TM_'开头
//
// Test Status: Undo
// Code Status: Working
//
// 函数与功能对应：
// 
// 初始化VL_Ti_Lib
// Status InitTicket(char* _TrainNum, char* _Start, StopName* _Stop, char* _End,
//	LeaveTime* _LeaveTime, int _OccuQuota, int _SurpTick)
// 返回值：OK, NOSPACE
// 
// 返回VL_Ti_Lib中对应车次开头的头指针
// SUB_TrainInfo * TM_GetHeadPointer(char)
// 返回值：对应车次的SUB_TrainInfo指针
// 
// 新增车次
// Status TM_NewTrain()
// 返回值：NOSPACE, OK, ERROR
// 
// 将车次信息结点依照升序插入到对应位置
// Status TM_InsertTrainNode (SUB_TrainInfo*)
// 返回值：
// 
// 更新该车次类别下，头结点FIrstNum指针数组内的结点指针
// Status TM_UpdateFirstNumPointer(char*)
// 返回值
//

#include "V_Lib.h"
#include <stdlib.h>

// 初始化VL_Ti_Lib
Status TM_InitTicket()
{
	// 可能的异常：
	// p q sn lt无可用空间分配

	int index; // 循环变量

	// 申请空间存储车次信息结构体
	TOP_TrainInfo* p;
	p = (struct TOP_TrainInfo*)malloc(sizeof(struct TOP_TrainInfo));
	if (!p) return NOSPACE; // 无可用空间分配
	VL_Ti_Lib = p; // 赋值初始化VL_Ti_Lib

	// 逐个初始化VL_Ti_Lib下的结点
	for (index = 0; index < 11; index++)
	{
		// 申请SUB_TrainInfo结点
		SUB_TrainInfo* q;
		q = (struct SUB_TrainInfo*)malloc(sizeof(struct SUB_TrainInfo));
		if (!q) return NOSPACE; // 无可用空间分配
		// 申请StopName结点
		StopName* sn;
		sn = (struct StopName*)malloc(sizeof(struct StopName));
		if (!sn) return NOSPACE; // 无可用空间分配
		// 申请LeaveTime结点
		LeaveTime* lt;
		lt = (struct LeaveTime*)malloc(sizeof(struct LeaveTime));
		if (!lt) return NOSPACE; // 无可用分配空间
		// 初始化sn结点信息
		sn->name = "HeadNode";
		sn->next = NULL;
		// 初始化lt结点信息
		lt->name = "HeadNode";
		lt->hour = 0; lt->min = 0; lt->ToNextMin = 0;
		lt->next = NULL;
		// 初始化SUB_TrainInfo结点信息
		q->NodeKind = "H";
		// FirstNum指针数组置空
		for (int i = 0; i < 10; i++) q->FirstNum[i] = NULL;

		q->TrainNum = "HeadNode";
		q->Start = "HeadNode";
		q->Stop = sn;
		q->End = "HeadNode";
		q->StationLeaveTime = lt;
		q->OccupantQuota = 0;
		q->SurplusTicket = 0;
		q->TrainOrder = NULL;
		q->TrainWaitOrder = NULL;
		q->next = NULL;
		// 将SUB_TrainInfo结点赋值给TOP中的指针变量
		switch (index)
		{
		case 0: {p->G = q; break; }
		case 1: {p->D = q; break; }
		case 2: {p->C = q; break; }
		case 3: {p->Z = q; break; }
		case 4: {p->T = q; break; }
		case 5: {p->K = q; break; }
		case 6: {p->Y = q; break; }
		case 7: {p->L = q; break; }
		case 8: {p->S = q; break; }
		case 9: {p->N = q; break; }
		case 10: {p->P = q; break; }
		} // switch
	
	} // for (index = 0; index < 11; index++)
	return OK;

} // Status InitTicket()

// 返回VL_Ti_Lib中对应车次开头的头指针
SUB_TrainInfo* TM_GetHeadPointer(char FirstC)
{
	switch (FirstC)
	{
	case 'G': return VL_Ti_Lib->G;
	case 'D': return VL_Ti_Lib->D;
	case 'C': return VL_Ti_Lib->C;
	case 'Z': return VL_Ti_Lib->Z;
	case 'T': return VL_Ti_Lib->T;
	case 'K': return VL_Ti_Lib->K;
	case 'Y': return VL_Ti_Lib->Y;
	case 'L': return VL_Ti_Lib->L;
	case 'S': return VL_Ti_Lib->S;
	case 'N': return VL_Ti_Lib->N;
	case 'P': return VL_Ti_Lib->P;
	}
}

// 将车次信息结点依照升序插入到对应位置
Status TM_InsertTrainNode(SUB_TrainInfo* NT)
{
	
}

// 更新该车次类别下，头结点FIrstNum指针数组内的结点指针
Status TM_UpdateFirstNumPointer(char* TrainNum)
{
	
}

// 新增车次
// input：车次编号、始发站、途经站、终到站、_LeaveTime(各站点发车时间、各站点运行到下一站点时间)、乘员定额、余票数量
// output：NOSPACE：无可用空间，ERROR：对应车次头结点不存在，OK：正常
Status TM_NewTrain(char* _TrainNum, char* _Start, StopName* _Stop, char* _End,
	LeaveTime* _LeaveTime, int _OccuQuota, int _SurpTick)
{
	SUB_TrainInfo* NT, *p; // NT为新结点指针，p为工作指针
	NT = (SUB_TrainInfo*)malloc(sizeof(struct SUB_TrainInfo));
	if (!NT) return NOSPACE; // 无可用空间

	if (!(p = TM_GetHeadPointer(_TrainNum[0]))) return ERROR; // 该类别车次的头指针不存在

	// 写入车次信息进NT
	NT->NodeKind = "E";
	NT->Start = _Start;
	NT->Stop = _Stop;
	NT->End = _End;
	NT->StationLeaveTime = _LeaveTime;
	NT->OccupantQuota = _OccuQuota;
	NT->SurplusTicket = _SurpTick;

	NT->TrainOrder = NULL;
	NT->TrainWaitOrder = NULL;

	NT->next = NULL;

	// 将新车次结点插入到VL_Ti_lib中，并更新对应车次类别头结点的信息
	TM_InsertTrainNode(NT);
	TM_UpdateFirstNumPointer(_TrainNum);

	return OK;
}

