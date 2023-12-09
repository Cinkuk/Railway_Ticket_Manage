// 此头文件用于记录可在项目中被外部调用的函数的声明
//
// Code Status: Undo

#include "V_Lib.h"

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
extern char* OM_CreateOrderNum();
extern Status OM_New_F_Order(char*, char*,char*, char*, int);
extern Status OM_New_W_Order(char*, char*, char*, char*, int);
extern Status OM_CheckWaitOrder(SearchWaitResult*);

// Search.c
extern TrainIndexNode* S_RequestTINode();
extern TrainIndexNode* S_Get_TIDB_HeadPointer(char*);
extern Status S_InitTIDB();
extern Status S_InitSIDB();
extern Status S_AddTrainToSearchDB(char* , StopName* );
extern SUB_TrainInfo* S_GetTrainNode(char* );
extern PhoneOrder* S_GetPhoneOrderNode(char* );


// Basic_Function.c
extern int BF_Get_Train_Number(char*);
extern char* BF_Merge_Char(char[]);
extern void BF_QuickSort(SearchResult*, int, int, int);


// UserFunction.c
extern Status UF_SearchStop(char*, char*, SearchResult*);
extern int UF_GetOrderInfo(char*, void*);
extern PhoneOrderList* UF_GetPhoneOrder(char* );
extern Status UF_New_F_Order(char*, char*, char*, int, char*);
extern Status UF_New_W_Order(char*, char*, char*, int, char*);
extern Status UF_Delete_Order(char*);
extern Status UF_LeaveTimeSort(SearchResult*);
extern Status UF_RunTimeSort(SearchResult* );
