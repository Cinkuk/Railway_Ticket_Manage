// 本文件存放的函数面向用户的操作
// 本文件的函数名以'User_'开头
//
// Test Status: Undo
// Code Status: Undo
//
// 函数与功能对应：
//
// // 查询，输入出发地、目的地
// Status SearchStop(char* _Leave, char* _Arrive, SearchResult* SR)
// 输入：出发站，到达站，返回结果结构体空指针
// return：OK, ERROR（出发站不存在）, NOSPACE, EMPTY（无可用班次）
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
//  
//

#include "F_Lib.h"
#include "V_Lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 查询，输入出发地、目的地
// return：OK, ERROR（出发站不存在）, NOSPACE, EMPTY（无可用班次）
Status SearchStop(char* _Leave, char* _Arrive, SearchResult* SR)
{
	StopIndexDB* LeaveStop; // 工作指针

	int FindLeaveStop = 0; // 0：未找到出发站，1：已找到
	int i = 0; // 循环变量

	char* CurTrain; //当前车次编号
	char* CurStop; // 当前遍历到的站点名

	int Index_L = 0; // 出发站点在车次中的顺序序号
	int Index_A =0; // 终点站在车次中的顺序序号
	int Index = 1; // 当前遍历到的站点的顺序序号

	int _LeaveTime[2] = { 0,0 }; // 出发时间，数组0：小时，数组1：分钟
	int _ArriveTime[2] = { 0,0 }; // 到达时间，数组0：小时，数组1：分钟
	int _ToNextTime=0; // 出发站到终点站的时间

	SUB_TrainInfo* CurTrainNode; // 当前车次的结点
	LeaveTime* CurStopList; // 当前站点

	SearchResult* NEW_SR;

	// 返回结果指针
	// 为SR分配空间，无可用空间则返回空指针
	if (!(SR = (SearchResult*)malloc(sizeof(SearchResult)))) return NOSPACE;
	// 填充头结点信息
	SR->TrainNum = SR->Leave = SR->Arrive = "HeadNode";
	SR->TrainNode = NULL;
	for (int j = 0; j < 2; j++) { SR->LeaveTime[j] = SR->ArriveTime[j] = 0; }
	SR->ToNextMin = 0;
	SR->NextResult = NULL;

	LeaveStop = VL_SI_DB->next; // 指向首元结点

	// 遍历站点检索车次的数据库寻找出发站
	while (LeaveStop && FindLeaveStop == 0) // 站点检索车次的数据库未遍历完，未找到出发站
	{
		while (*(LeaveStop->StationName + i) == *(_Leave + i) &&
			i != 0) // 需要匹配的字符串非空，逐位匹配相等
		{
			i++;
		} // while
		// 需要匹配的字符串完全相同且非空，找到出发站
		if (*(LeaveStop->StationName + i) == '\0' &&
			*(_Leave + i) == '\0' && i != 0)
		{
			// 找到出发站
			FindLeaveStop = 1;
			// 退出查找出发站循环
			break;
		} // if
		// 当前站点不匹配出发站，工作指针移到下一站点
		LeaveStop = LeaveStop->next;
	} // 	while (LeaveStop && FindLeaveStop == 0)

	// 出发站不存在
	if (FindLeaveStop == 0) return ERROR; 

	// 出发站存在，遍历经过出发站的全部车次
	TrainNumList* _TrainList = LeaveStop->TrainList;
	FindLeaveStop = 0;
	while (_TrainList) // 车次未遍历完
	{
		CurTrain = _TrainList->CurNum; // 暂存当前车次编号
		CurTrainNode = S_GetTrainNode(CurTrain);
		CurStopList = CurTrainNode->StationLeaveTime;
		
#if 0
		// 比较出发站、终点站与车次各站点
		// 出发站与车次终点站相等
		if (strcmp(_Leave, CurTrainNode->Start) == 0)
		{
			Index_L = Index;
			
			Index++;
		}
#endif

		CurStop = CurStopList->name;
		// 遍历途径站点
		while (CurStopList)
		{
			// 记录出发站到当前车站所经过的总时间
			if (FindLeaveStop == 1) _ToNextTime += 60 * CurStopList->hour + CurStopList->min;

			// 站点与出发站相同
			if (strcmp(CurStop, _Leave) == 0)
			{
				Index_L = Index;
				_LeaveTime[0] = CurStopList->hour;
				_LeaveTime[1] = CurStopList->min;

				FindLeaveStop = 1;
			}
			
			// 站点与终点站相同
			else if (strcmp(CurStop, _Arrive) == 0)
			{
				Index_A = Index;
				_ArriveTime[0] = CurStopList->hour;
				_ArriveTime[1] = CurStopList->min;

			}

			// 均不相同，比较下一个站点
			CurStopList = CurStopList->next; // 指向下一站点
			CurStop = CurStopList->name; // 记录当前站点名字

			// 遍历序号自增
			Index++;
		} // while (CurStopList)

#if 0
		// 终点站与终到站相同
		if (strcmp(_Leave, CurTrainNode->End) == 0) Index_A = Index;
#endif
		
		// 出发站和终点站均找到
		// 运行顺序为出发站前往终点站
		// 将查找结果写入搜寻结果中
		if (Index_L != 0 && Index_A != 0 &&
			Index_L < Index_A)
		{
			// 为SR分配空间，无可用空间则返回空指针
			if (!(NEW_SR = (SearchResult*)malloc(sizeof(SearchResult)))) return NULL;
			NEW_SR->TrainNum = CurTrain; // 车次编号
			NEW_SR->Leave = _Leave; // 出发地
			NEW_SR->Arrive = _Arrive; // 到达地
			// 出发时间
			NEW_SR->LeaveTime[0] = _LeaveTime[0];
			NEW_SR->LeaveTime[1] = _LeaveTime[1];
			// 到达时间
			NEW_SR->ArriveTime[0] = _ArriveTime[0];
			NEW_SR->ArriveTime[1] = _ArriveTime[1];
			NEW_SR->ToNextMin = _ToNextTime; // 总运行时间
			NEW_SR->TrainNode = CurTrainNode;
			// NEW_SR插入到SR首元结点
			NEW_SR->NextResult = SR->NextResult;
			SR->NextResult = NEW_SR;
		}

		else
		{
			// 重置搜索记录变量
			FindLeaveStop = 0;
			Index_L = Index_A = Index = 0;
			_LeaveTime[0] = _LeaveTime[1] = 0;
			_ArriveTime[0] = _ArriveTime[1] = 0;
			_ToNextTime = 0;
			
			// 查找该站点的下一班车次
			_TrainList = _TrainList->next;
		}
	} // while (_TrainList)

	// 无可用车次
	if (!SR->NextResult) return EMPTY;
	
	// 查找成功
	else return OK;
} // Status SearchStop(char* _Leave, char* _Arrive, SearchResult* SR)




