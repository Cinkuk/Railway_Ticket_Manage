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
// Status InitTicket()
// 返回值：OK, NOSPACE
// 
// 返回VL_Ti_Lib中对应车次开头的头指针
// SUB_TrainInfo * GetHeadPointer(char)
// 返回值：对应车次的SUB_TrainInfo指针
// 
// 新增车次
// Status NewTrain()
// 返回值：NOSPACE, OK
// 
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

//返回VL_Ti_Lib中对应车次开头的头指针
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

// 新增车次
Status NewTrain()
{

}

