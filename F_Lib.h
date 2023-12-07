// 此头文件用于记录可在项目中被外部调用的函数的声明
//
// Code Status: Undo

#include "V_Lib.h"

// Ticket_Manage.c
extern SUB_TrainInfo* TM_RequestSUBTrainHeadNode();
extern SUB_TrainInfo* TM_RequestNodeForTopNode();
extern Status TM_InitTicket();
extern SUB_TrainInfo* TM_GetHeadPointer(char*);
extern Status TM_InsertTrainNode(SUB_TrainInfo*);
extern Status TM_NewTrain(char* , char* , StopName* , char* ,
	LeaveTime* , int , int );

// Order_Manage.c
extern Status OM_InitOrder();
extern char* OM_CreateOrderNum();
extern Status OM_New_F_Order(char*, char*,char*, char*, int);
extern Status OM_New_W_Order(char*, char*, char*, char*, int);


// Search.c
extern TrainIndexNode* S_RequestTINode();
extern TrainIndexNode* S_GetTIHeadPointer(char*);
extern Status S_InitTIDB();
extern Status S_InitSIDB();
extern Status S_AddTrainToSearchDB(char* , StopName* );
extern SUB_TrainInfo* S_GetTrainNode(char* );
extern PhoneOrder* S_GetPhoneOrder(char* );




// Basic_Function.c
extern int BF_Get_Train_Number(char*);


