// ���ļ����ڴ�Ŷ�������ĺ���
// �������Ĺؼ����������Variables_Lib.c��
// ���ļ��ĺ�������'OM_'��ͷ
//
// Test Status: Undo
// Code Status: Working
//
// �����빦�ܶ�Ӧ:
// 
// ��ʼ��VL_Or_Lib
// OM_InitOrder()����ʼ��VL_Or_Lib
// ����ֵ��NOSPACE, OK
// 
// ����Ψһ�Ķ������
// char* OM_CreateOrderNum()
// return: ��������ַ���ָ��
//
//
// �����µ���ʽ����
// Status OM_New_F_Order(char* _phone, char* _TrainNum,
//	                     char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
// input���ֻ��š����Ρ�����վ������վ����Ʊ����
// return: NOSPACE, OK
//
// �����µĺ򲹶���
//Status OM_New_W_Order(char* _phone, char* _TrainNum,
//	                    char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
// input���ֻ��š����Ρ�����վ������վ����Ʊ����
// return: NOSPACE, OK
//
//


#include "V_Lib.h"
#include <stdlib.h>
#include "F_Lib.h"

// ��ʼ��VL_Or_Lib
Status OM_InitOrder()
{
	// ����PhoneOrder���
	PhoneOrder* p;
	p = (struct PhoneOrder*)malloc(sizeof(struct PhoneOrder));
	if (!p) return NOSPACE; // �޿��ÿռ�
	// ��ʼ������ֵ
	p->NodeKind = "H";
	p->phone = -1;
	p->OrderList = NULL;
	p->next = NULL;

	VL_Or_Lib = p; // ����ɹ����ڴ��ַ��ֵ��VL_Or_Lib
	return OK; 
}

// ����Ψһ�Ķ������
char* OM_CreateOrderNum()
{
	int i; // ѭ������
	if (!VL_OrderID) // ��ų�Ϊ��
	{
		OrderSet* node;
		node = (OrderSet*)malloc(sizeof(struct OrderSet));

		if (!node) return NULL; // �޿��ÿռ�������

		// ��ʼ��ΪA000000001
		node->ID[0] = 65; // 65ΪASCII��A
		for (int i = 1; i < 9; i++) node->ID[i] = 0;
		node->ID[9] = 1;
		node->next = NULL;
		return BF_Merge_Char(node->ID);
	}
	OrderSet* node;
	node = (OrderSet*)malloc(sizeof(struct OrderSet));
	if (!node) return NULL; // �޿��ÿռ�������
	
	node->next = VL_OrderID;
	for (i = 0; i < 9; i++) node->ID[i] = node->next->ID[i]; // ����ǰһ�Ŷ����ı��
	VL_OrderID = node; // ����Ϊ��һ�����
	
	node->ID[9] += 1;

	for (i = 9; i > 0; i--)
	{
		if (node->ID[i] > 9) // ���λ
		{
			node->ID[i] = 0;
			node->ID[1 - 1] += 1;
		}
	}

	if (node->ID[0] > 90) return NULL; // ��ǰ����ѳ������ֵ��Z999999999��

	return BF_Merge_Char(node->ID);
}

// �����µ���ʽ����
// input���ֻ��š����Ρ�����վ������վ����Ʊ����
Status OM_New_F_Order(char* _phone, char* _TrainNum,
	char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
{
	Order* p;
	char* _OrderNum;
	SUB_TrainInfo* TrainNode;
	PhoneOrder* PhoneNode;

	p = (Order*)malloc(sizeof(struct Order));

	if (!p) return NOSPACE; // �޿��ÿռ�

	PhoneOrderList* q; // �ܶ������
	q = (PhoneOrderList*)malloc(sizeof(struct PhoneOrderList));

	if (!q) return NOSPACE; //�޿��ÿռ�

	// ���붩����ź���Ҫ�Ľ���ַ
	_OrderNum = OM_CreateOrderNum();
	TrainNode = S_GetTrainNode(_TrainNum);
	PhoneNode = S_GetPhoneOrder(_phone);

	// ��㸳ֵ
	// ��������
	p->NodeKind = "E";
	q->NodeKind = "E";
	q->OrderStatus =  "F";

	p->OrderNum = _OrderNum; // �������
	p->TrainNum = _TrainNum; // ���α��
	p->phone = _phone; // �ֻ���

	// ����վ
	p->Start = _LeaveStop;
	q->LeaveStop = _LeaveStop;
	// ����վ
	p->End = _ArriveStop;
	q->ArriveStop = _ArriveStop;
	// Ʊ��
	p->TicketNum = _TicketSmount;
	q->TicketAmount = _TicketSmount;

	// �ܶ������ָ������
	// ����ͬһ�ֻ����µ���������
	q->NextOrder = PhoneNode->OrderList->NextOrder;
	PhoneNode->OrderList->NextOrder = q;
	// ���ӵ�ǰ���ν��
	q->Train = TrainNode; // ָ��ǰ���ν��
	q->CurrentOrder = TrainNode->TrainOrder; // ָ��ǰ���ζ���	
	// �ó����µĶ�������У����ӱ��Ŷ����Ľ��
	p->next = TrainNode->TrainOrder->next;
	TrainNode->TrainOrder->next = p;

	return OK;
}

// �����µĺ򲹶���
// input���ֻ��š����Ρ�����վ������վ����Ʊ����
Status OM_New_W_Order(char* _phone, char* _TrainNum,
	char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
{
	WaitOrder* p;
	char* _OrderNum;
	SUB_TrainInfo* TrainNode;
	PhoneOrder* PhoneNode;

	p = (WaitOrder*)malloc(sizeof(struct WaitOrder));

	if (!p) return NOSPACE; // �޿��ÿռ�

	PhoneOrderList* q; // �ܶ������
	q = (PhoneOrderList*)malloc(sizeof(struct PhoneOrderList));

	if (!q) return NOSPACE; // �޿��ÿռ�

	// ���붩����ź���Ҫ�Ľ���ַ
	_OrderNum = OM_CreateOrderNum();
	TrainNode = S_GetTrainNode(_TrainNum);
	PhoneNode = S_GetPhoneOrder(_phone);

	// ��㸳ֵ
	// ��������
	p->NodeKind = "E";
	q->NodeKind = "E";
	q->OrderStatus = "W";

	p->OrderNum = _OrderNum; // �������
	p->TrainNum = _TrainNum; // ���α��
	p->phone = _phone; // �ֻ���

	// ����վ
	p->Start = _LeaveStop;
	q->LeaveStop = _LeaveStop;
	// ����վ
	p->End = _ArriveStop;
	q->ArriveStop = _ArriveStop;
	// Ʊ��
	p->TicketNum = _TicketSmount;
	q->TicketAmount = _TicketSmount;

	// �ܶ������ָ������
	// ����ͬһ�ֻ����µ���������
	q->NextOrder = PhoneNode->OrderList->NextOrder;
	PhoneNode->OrderList->NextOrder = q;
	// ���ӵ�ǰ���ν��
	q->Train = TrainNode; // ָ��ǰ���ν��
	q->CurrentWaitOrder =  TrainNode->TrainWaitOrder; // ָ��ǰ���κ򲹶���ͷ���
	
	// �ó����µĺ򲹶�������У����ӱ��Ŷ����Ľ��
	p->next = TrainNode->TrainWaitOrder->rear->next;
	TrainNode->TrainWaitOrder->rear = p;

	return OK;
}


