// 本文件用于存放关于搜索的函数
// 所依赖的关键变量存放于Variables_Lib.c中
// 本文件的函数名以'S_'开头
//
// Test Status: Undo
// Code Status: Working
//
// 函数与功能对应：
// 
// 初始化一个车次链表头链表
// TrainIndexNode* S_RequestTINode()
// return: NULL, 对应头结点地址
// 
// 返回VL_TI_DB中车次类别的入口指针
// TrainIndexNode* S_GetTIHeadPointer(char*)
// return: NULL, 对应头结点指针
// 
// 初始化VL_TI_DB
// Status S_InitTIDB()
// return: NOSPACE, OK
//
// 初始化VL_SI_DB
// Status S_InitSIDB()
// return: NOSPACE, OK
// 
// 将车次信息结点新增进车次检索系统中
// Status S_AddTrainToSearchDB(char*, StopName*) 
// input：车次编号，站点
// return: OK, NOSPACE
//
// 根据车次编号返回VL_Ti_Lib下的车次结点
// SUB_TrainInfo* S_GetTrainNode(char*)
// input：车次编号
// return：对应头指针, NULL
//
// 根据手机号返回VL_Or_Lib下的手机号结点
// PhoneOrder* S_GetPhoneOrder(char*)
// input：电话
// return：对应数据元素结点指针（无则创建该数据元素结点）, NULL（无现成结点，也无空间创建结点）
//

#include "F_Lib.h"
#include "V_Lib.h"
#include <stdlib.h>
#include <string.h>

// 初始化部分

// 初始化一个车次链表头链表
TrainIndexNode* S_RequestTINode()
{
	int i; // 索引变量

	TrainIndexNode* node;
	node = (TrainIndexNode*)malloc(sizeof(struct TrainIndexNode));
	StationList* namelist;
	namelist = (StationList*)malloc(sizeof(struct StationList));

	if (!node || !namelist) return NULL; // 无可用空间

	namelist->StationName = "HeadNode";
	namelist->next = NULL;

	node->NodeKind = "H";
	node->TrainNum = "HeadNode";
	node->StationNameList = NULL;

	for (i = 0; i < 10; i++)
	{
		TrainIndexNode* subnode;
		subnode = (TrainIndexNode*)malloc(sizeof(struct TrainIndexNode));
		
		if (!subnode) return NULL; // 无可用空间

		// 初始化加快检索的头结点
		subnode->NodeKind = "H";
		for (int j = 0; j < 10; j++) subnode->NumIndex[j] = NULL;
		subnode->TrainNum = "HeadNode";
		subnode->StationNameList = NULL;

		// 子结点存入指针数组
		node->NumIndex[i] = subnode;
	}
	return node;
}

// 返回VL_TI_DB中车次类别的入口指针
TrainIndexNode* S_Get_TIDB_HeadPointer(char* First)
{
	switch (*First)
	{
	case 'G': return VL_TI_DB->G;
	case 'D': return VL_TI_DB->D;
	case 'C': return VL_TI_DB->C;
	case 'Z': return VL_TI_DB->Z;
	case 'T': return VL_TI_DB->T;
	case 'K': return VL_TI_DB->K;
	case 'Y': return VL_TI_DB->Y;
	case 'L': return VL_TI_DB->L;
	case 'S': return VL_TI_DB->S;
	case 'N': return VL_TI_DB->N;
	case 'P': return VL_TI_DB->P;
	}
	return NULL; // 传入的字符不存在于可用类型中
}

// 初始化VL_TI_DB
Status S_InitTIDB()
{
	TrainIndexDB* TopDB;
	TrainIndexNode* p;
	int i; // 循环变量
	TopDB = (TrainIndexDB*)malloc(sizeof(struct TrainIndexDB));
	if (!TopDB) return NOSPACE; // 无可用空间

	
	for (i = 0; i < 11; i++)
	{
		p = S_RequestTINode();
		switch (i)
		{
		case 0: {TopDB->G = p; break; }
		case 1: {TopDB->D = p; break; }
		case 2: {TopDB->C = p; break; }
		case 3: {TopDB->Z = p; break; }
		case 4: {TopDB->T = p; break; }
		case 5: {TopDB->K = p; break; }
		case 6: {TopDB->Y = p; break; }
		case 7: {TopDB->L = p; break; }
		case 8: {TopDB->S = p; break; }
		case 9: {TopDB->N = p; break; }
		case 10: {TopDB->P = p; break; }

		} // switch (i)
	} // for (i = 0; i < 11; i++)
	
	
	VL_TI_DB = TopDB; // 将结点地址赋值给VL_TI_DB

	return OK;
}

// 初始化VL_SI_DB
Status S_InitSIDB()
{
	StopIndexDB* TopNode;
	TopNode = (StopIndexDB*)malloc(sizeof(struct StopIndexDB));

	if (!TopNode) return NOSPACE; // 无可用空间

	// 头结点赋值
	TopNode->NodeKind = "H";
	TopNode->StationName = "HeadNode";
	TopNode->TrainList = NULL;
	TopNode->next = NULL;

	// 结点地址传送给VL_SI_DB
	VL_SI_DB = TopNode;

	return OK;
}

// 赋值VL_Or_Lib中数据元素的头结点
Status S_Fill_OrLib_HeadNode(PhoneOrderList* p)
{
	p->NodeKind = "H";
	p->OrderStatus = "HN";
	p->CurrentOrder = NULL;
	p->CurrentWaitOrder = NULL;
	p->Train = NULL;
	p->LeaveStop = p->ArriveStop = NULL;
	p->TicketAmount = 0;
	p->NextOrder = NULL;
	return OK;
}

// 根据车次编号返回VL_Ti_Lib下的车次结点
// output：对应头指针
SUB_TrainInfo* S_GetTrainNode(char* _TrainNum)
{
	char First = *_TrainNum; // 车次编号首字母
	SUB_TrainInfo* p, *q; // 工作指针
	int i = 0; // 循环变量
	
	q = NULL; // q为返回值

	if (!(p = TM_Get_TiLib_HeadPointer(_TrainNum))); // p指向对应车次类别头结点
	return NULL; // 对应类别头结点不存在

	p = p->next;
	while (p) // 遍历车次信息链表
	{
		// 车次编号格式为一位字母+4位数字
		// 逐位比较车次数字
		for (i = 0; i <= 5; i++) 
		{
			// 车次逐位比较均相同
			// 退出while循环并返回地址
			if (*(p->TrainNum + i) == '\0' && *(_TrainNum + i) == '\0')
			{
				q = p;
				goto RETURN;
			}
			else if (*(p->TrainNum + i) == *(_TrainNum + i)); // 当前位相同，比较下一位
			else // 当前位不同，p指向下一位，本轮比较终止
			{
				p = p->next;
				break;
			}
		} // for (i = 1; i <= 4; i++) 
	} // while (p)

	// 只有找到匹配项才会返回对应指针，否则均返回空指针
RETURN: return q;

	// 此时q为空指针，由于不符合进入RETURN的条件，且函数需要返回值，下面的语句用于q=NULL时的返回
	return q;
}	

// 根据手机号返回VL_Or_Lib下的手机号结点
// output：对应数据元素结点指针（无则创建该数据元素结点）
PhoneOrder* S_GetPhoneOrderNode(char* _phone)
{
	PhoneOrder* p, *PONode; // 工作指针
	PhoneOrderList* q; // 用于新建结点
	int i; // 循环变量

	p = VL_Or_Lib->next; // p指向订单链表首元结点

	while (p) // 遍历订单链表
	{
		for (i = 0; i <= 11; i++) // 手机号为11位
		{
			// 手机号逐位比较均相同
			// 退出while循环并返回地址
			if (*(p->phone + i) == '\0' && *(_phone + i) == '\0') // 手机逐位比较均相同
			{
				goto RETURN;
			}
			else if (*(p->phone + i) == *(_phone + i)); // 当前位相同，比较下一位
			else // 当前位不同，p指向下一结点，本轮比较终止
			{
				p = p->next;
				break;
			}
		} // for (i = 0; i <= 11; i++) 
	} // while (p)

	if (!p) // 订单链表中无此手机号结点，创建并返回
	{
		q = (PhoneOrderList*)malloc(sizeof(struct PhoneOrderList));
		if (!q) { goto RETURN; } // 无可用空间，返回空指针

		PONode = (PhoneOrder*)malloc(sizeof(struct PhoneOrder));
		if (!PONode) { goto RETURN; } // 无可用空间，返回空指针
		
		// 赋值头结点
		S_Fill_OrLib_HeadNode(q);
		PONode->NodeKind = "H";
		strcpy(PONode->phone, _phone);
		PONode->OrderList = q;
		PONode->next = NULL;

		// q插入为VL_Or_lib的首元结点
		p = VL_Or_Lib;
		PONode->next = p->next;
		p->next = PONode;

		// 返回头结点地址
		p = PONode;
		goto RETURN;
	}

	// 返回结点地址
RETURN:return p;
}

// 将车次信息结点新增进车次检索系统中
// input：车次编号，站点
Status S_AddTrainToSearchDB(char* _TrainNum, StopName* _StopName)
{
	
}

