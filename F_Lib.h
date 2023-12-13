// 此头文件用于记录可在项目中被外部调用的函数的声明
//
// Code Status: Undo

#include "V_Lib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <memory.h>
#include <Windows.h>

// Ticket_Manage.c
extern SUB_TrainInfo* TM_RequestSUBTrainHeadNode();
extern SUB_TrainInfo* TM_RequestNodeForTopNode();
extern Status TM_InitTicket();
extern SUB_TrainInfo* TM_Get_TiLib_HeadPointer(char*);
extern Status TM_InsertTrainNode(SUB_TrainInfo*);
extern Status TM_NewTrain(char* , char* , StopName* , char* ,
	LeaveTime* , int , int );

// Order_Manage.c
extern Status OM_InitOrder();
extern Status OM_InitOrderID();
extern char* OM_CreateOrderNum();
extern Status OM_New_F_Order(char*, char*,char*, char*, int);
extern Status OM_New_W_Order(char*, char*, char*, char*, int);
extern Status OM_CheckWaitOrder(SearchWaitResult*);

// Search.c
extern TrainIndexNode* S_RequestTINode();
extern TrainIndexNode* S_Get_TIDB_HeadPointer(char*);
extern Status S_InitTIDB();
extern Status S_InitSIDB();
extern Status S_Fill_OrLib_HeadNode(PhoneOrderList* p);
extern SUB_TrainInfo* S_GetTrainNode(char* );
extern PhoneOrder* S_GetPhoneOrderNode(char* );
extern Status S_AddTrainToSearchDB(char* , StopName* );

// Basic_Function.c
extern int BF_Get_Train_Number(char*);
extern char* BF_Merge_Char(char[]);
extern int BF_StrToInt(char*);
extern int BF_StrToMin(char*);

// UserFunction.c
extern SearchResult* UF_SearchStop(char*, char*);
extern OrderSet* UF_GetOrderInfo(char*);
extern Status UF_New_F_Order(char*, char*, char*, int, char*);
extern Status UF_New_W_Order(char*, char*, char*, int, char*);
extern Status UF_Delete_Order(char*);
extern SearchResult* UF_LeaveTimeSort(SearchResult*);
extern SearchResult* UF_RunTimeSort(SearchResult* );
extern SearchResult* UF_ArriveTimeSort(SearchResult*);
extern PhoneOrder* UF_GetPhoneOrderNode(char*);

// File_Operation.c
extern Status FO_LoadTrainFromHD();

// Display.c
extern void DP_CheckTrain();
extern void DP_CheckOrder();
extern void DP_CheckPhoneOrder();
extern void DP_WithdrawOrder();
extern void DP_ExitSys();
