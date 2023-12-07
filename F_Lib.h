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

// Basic_Function.c
extern int BF_Get_Train_Number(char*);


