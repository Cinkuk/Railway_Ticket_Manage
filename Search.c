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
// return：对应头指针
//
// 根据手机号返回VL_Or_Lib下的手机号结点
// PhoneOrder* S_GetPhoneOrder(char*)
// input：电话
// return：对应数据元素结点指针（无则创建该数据元素结点）
//

#include "F_Lib.h"
#include "V_Lib.h"
#include <stdlib.h>

// 初始化部分

// 初始化一个车次链表头链表
TrainIndexNode* S_RequestTINode()
{
	int i; // 索引变量

	TrainIndexNode* node;
	node = (TrainIndexNode*)mallooc(sizeof(struct TrainIndexNode));
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
		subnode = (TrainIndexNode*)mallooc(sizeof(struct TrainIndexNode));
		
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
TrainIndexNode* S_GetTIHeadPointer(char* First)
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

// 将车次信息结点新增进车次检索系统中
// input：车次编号，站点
Status S_AddTrainToSearchDB(char* _TrainNum, StopName* _StopName)
{
	
}

// 根据车次编号返回VL_Ti_Lib下的车次结点
// output：对应头指针
SUB_TrainInfo* S_GetTrainNode(char* _TrainNum)
{

}

// 根据手机号返回VL_Or_Lib下的手机号结点
// output：对应数据元素结点指针（无则创建该数据元素结点）
PhoneOrder* S_GetPhoneOrder(char* _phone)
{

}
