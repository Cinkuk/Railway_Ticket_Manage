// ���ļ����ڴ�Ŷ�������ĺ���
// �������Ĺؼ����������Variables_Lib.c��
// ���ļ��ĺ�������'OM_'��ͷ
//
// Test Status: Working
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
// �����µ���ʽ����
// Status OM_New_F_Order(char* _phone, char* _TrainNum,
//	                     char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
// input���ֻ��š����Ρ�����վ������վ����Ʊ����
// return: NOSPACE, OK, ERROR
//
// �����µĺ򲹶���
//Status OM_New_W_Order(char* _phone, char* _TrainNum,
//	                    char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
// input���ֻ��š����Ρ�����վ������վ����Ʊ����
// return: NOSPACE, OK
//
// ��ѯ�򲹶����ܷ�򲹲�����
// Status OM_CheckWaitOrder(SearchWaitResult* SWR)
// output: OK���к򲹶������ɹ��򲹣���EMPTY���޿��Խ��к򲹲����Ķ�����
// 
// 
//


#include "V_Lib.h"
#include "F_Lib.h"


// ��ʼ��VL_Or_Lib
// Freeze
Status OM_InitOrder()
{
	// ����PhoneOrder���
	PhoneOrder* p;
	p = (struct PhoneOrder*)malloc(sizeof(struct PhoneOrder));
	if (!p) return NOSPACE; // �޿��ÿռ�
	// ��ʼ������ֵ
	p->NodeKind = "H";
	p->phone = NULL;
	p->OrderList = NULL;
	p->next = NULL;

	VL_Or_Lib = p; // ����ɹ����ڴ��ַ��ֵ��VL_Or_Lib
	return OK; 
}

// ��ʼ��������
// Freeze
Status OM_InitOrderID()
{
	VL_OrderID = (OrderSet*)malloc(sizeof(OrderSet));
	if (!VL_OrderID) return NOSPACE;
	memset(VL_OrderID, 0, sizeof(OrderSet));
	return OK;

}

// ����Ψһ�Ķ������
// Freeze
char* OM_CreateOrderNum()
{
	int i; // ѭ������
	if (!(VL_OrderID->next)) // ��ų�Ϊ��
	{
		OrderSet* node;
		node = (OrderSet*)malloc(sizeof(struct OrderSet));
		if (!node) return NULL; // �޿��ÿռ�������
		memset(node, 0, sizeof(OrderSet));
		node->OrderKind = (char*)malloc(sizeof(char) * 5);

		// ��ʼ��ΪA000000001
		node->ID[0] = 65; // 65ΪASCII��A
		for (int i = 1; i < 9; i++) node->ID[i] = 48; // 48ΪASCII��0
		node->ID[9] = 49;
		node->ID[10] = '\0';

		node->next = VL_OrderID->next;
	    VL_OrderID->next = node;
		
		return BF_Merge_Char(node->ID);
	}
	else
	{
		OrderSet* node;
		node = (OrderSet*)malloc(sizeof(struct OrderSet));
		if (!node) return NULL; // �޿��ÿռ�������
		memset(node, 0, sizeof(OrderSet));
		node->OrderKind = (char*)malloc(sizeof(char) * 5);
	
		for (i = 0; i <= 10; i++) node->ID[i] = VL_OrderID->next->ID[i]; // ����ǰһ�Ŷ����ı��
		node->next = VL_OrderID->next;
		VL_OrderID->next = node; // ����Ϊ��һ�����

		node->ID[9] += 1;

		for (i = 9; i > 0; i--)
		{
			if (node->ID[i] > 57) // >0���λ
			{
				node->ID[i] = 48;
				node->ID[i - 1] += 1;
			}
		}

		if (node->ID[0] > 90) return NULL; // ��ǰ����ѳ������ֵ��Z999999999��


		return BF_Merge_Char(node->ID);
	}
}

// �����µ���ʽ����
// Freeze
// input���ֻ��š����Ρ�����վ������վ����Ʊ����
Status OM_New_F_Order(char* _phone, char* _TrainNum,
	char* _LeaveStop, char* _ArriveStop, int _TicketAmount)
{
	Order* p; // ������Ϣ���
	OrderSet* t; // ������ųع���ָ��
	char* _OrderNum = (char*)malloc(sizeof(char)*STRLENGTH); // �������
	SUB_TrainInfo* TrainNode; // ָ��ǰ�������εĳ�����Ϣͷ���
	PhoneOrder* PhoneNode; // ָ���ܶ�����Ϣ���
	

	p = (Order*)malloc(sizeof(struct Order));

	if (!p) return NOSPACE; // �޿��ÿռ�

	PhoneOrderList* q; // ������Ϣ���
	q = (PhoneOrderList*)malloc(sizeof(struct PhoneOrderList));

	if (!q) return NOSPACE; //�޿��ÿռ�

	// ���붩����ź���Ҫ�Ľ���ַ
	_OrderNum = OM_CreateOrderNum();
	TrainNode = S_GetTrainNode(_TrainNum);
	PhoneNode = S_GetPhoneOrderNode(_phone);

	if (!TrainNode) return ERROR; // �޴˰��

	// TrainNode or PhoneNodeΪ�ս����޿��ÿռ佨���������_OrderNum
	if (!_OrderNum || !PhoneNode) return NOSPACE; 

	// �ж��Ƿ��ܹ���Ʊ
	if (TrainNode->SurplusTicket < _TicketAmount) return ERROR;

	// ��㸳ֵ

	p->NodeKind = (char*)malloc(sizeof(char) * STRLENGTH);
	p->OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);
	p->TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
	p->phone = (char*)malloc(sizeof(char) * STRLENGTH);
	p->Start = (char*)malloc(sizeof(char) * STRLENGTH);
	p->End = (char*)malloc(sizeof(char) * STRLENGTH);


	q->NodeKind = (char*)malloc(sizeof(char) * STRLENGTH);
	q->OrderStatus = (char*)malloc(sizeof(char) * STRLENGTH);
	q->LeaveStop = (char*)malloc(sizeof(char) * STRLENGTH);
	q->ArriveStop = (char*)malloc(sizeof(char) * STRLENGTH);
	q->OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);

	// ��������
	p->NodeKind = "E";
	q->NodeKind = "E";
	q->OrderStatus =  "F";

	strcpy(p->OrderNum, _OrderNum); // �������
	strcpy(q->OrderNum, _OrderNum);
	strcpy(p->TrainNum, _TrainNum); // ���α��
	strcpy(p->phone, _phone); // �ֻ���

	// ����վ
	strcpy(p->Start, _LeaveStop);
	strcpy(q->LeaveStop, _LeaveStop);
	// ����վ
	strcpy(p->End, _ArriveStop);
	strcpy(q->ArriveStop, _ArriveStop);
	// Ʊ��
	p->TicketNum = _TicketAmount;
	q->TicketAmount = _TicketAmount;
	// ����Ʊ
	TrainNode->SurplusTicket -= _TicketAmount;

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

	t = VL_OrderID->next;
	// ������Ϣ���p���붩����ų���
	while (t)
	{
		
		// tָ��ǰ�������
		if (strcmp(BF_Merge_Char(t->ID),BF_Merge_Char(_OrderNum)) == 0)
		{
			strcpy(t->OrderKind, "F"); // ��������Ϊ��ʽ����
			t->OrderNode = p; // ����ǰ�������ӽ���������
			t->WaitOrderNode = NULL;
			break; // �˳�ѭ��
		}
		// tָ����һ�Ŷ���
		t = t->next;
	}


	return OK;
}

// �����µĺ򲹶���
// Freeze
// input���ֻ��š����Ρ�����վ������վ����Ʊ����
Status OM_New_W_Order(char* _phone, char* _TrainNum,
	char* _LeaveStop, char* _ArriveStop, int _TicketAmount)
{
	WaitOrder* p; // ������Ϣ���
	OrderSet* t; // ������ųع���ָ��
	char* _OrderNum = (char*)malloc(sizeof(char) * STRLENGTH); // �������
	SUB_TrainInfo* TrainNode; // ָ��ǰ�������εĳ�����Ϣͷ���
	PhoneOrder* PhoneNode; // ָ���ܶ�����Ϣ���

	p = (WaitOrder*)malloc(sizeof(struct WaitOrder));

	if (!p) return NOSPACE; // �޿��ÿռ�

	PhoneOrderList* q; // ������Ϣ���
	q = (PhoneOrderList*)malloc(sizeof(struct PhoneOrderList));

	if (!q) return NOSPACE; // �޿��ÿռ�

	// ���붩����ź���Ҫ�Ľ���ַ
	_OrderNum = OM_CreateOrderNum();
	TrainNode = S_GetTrainNode(_TrainNum);
	PhoneNode = S_GetPhoneOrderNode(_phone);

	// TrainNode or PhoneNodeΪ�ս����޿��ÿռ佨���������_OrderNum
	if (!_OrderNum || !TrainNode || !PhoneNode) return NOSPACE; 

	// ��㸳ֵ
	 
	p->NodeKind = (char*)malloc(sizeof(char) * STRLENGTH);
	p->OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);
	p->TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
	p->phone = (char*)malloc(sizeof(char) * STRLENGTH);
	p->Start = (char*)malloc(sizeof(char) * STRLENGTH);
	p->End = (char*)malloc(sizeof(char) * STRLENGTH);


	q->NodeKind = (char*)malloc(sizeof(char) * STRLENGTH);
	q->OrderStatus = (char*)malloc(sizeof(char) * STRLENGTH);
	q->LeaveStop = (char*)malloc(sizeof(char) * STRLENGTH);
	q->ArriveStop = (char*)malloc(sizeof(char) * STRLENGTH); 
	q->OrderNum = (char*)malloc(sizeof(char) * STRLENGTH); 
	
	// ��������
	p->NodeKind = "E";
	q->NodeKind = "E";
	q->OrderStatus = "W";

	strcpy(p->OrderNum, _OrderNum); // �������
	strcpy(q->OrderNum, _OrderNum);
	strcpy(p->TrainNum, _TrainNum); // ���α��
	strcpy(p->phone, _phone); // �ֻ���

	// ����վ
	strcpy(p->Start, _LeaveStop);
	strcpy(q->LeaveStop, _LeaveStop);
	// ����վ
	strcpy(p->End, _ArriveStop);
	strcpy(q->ArriveStop, _ArriveStop);
	
	// Ʊ��
	p->TicketNum = _TicketAmount;
	q->TicketAmount = _TicketAmount;

	// �ܶ������ָ������
	// ����ͬһ�ֻ����µ���������
	q->NextOrder = PhoneNode->OrderList->NextOrder;
	PhoneNode->OrderList->NextOrder = q;
	// ���ӵ�ǰ���ν��
	q->Train = TrainNode; // ָ��ǰ���ν��
	q->CurrentWaitOrder =  TrainNode->TrainWaitOrder; // ָ��ǰ���κ򲹶���ͷ���
	
	// �ó����µĺ򲹶�������У����ӱ��Ŷ����Ľ��
	p->next = TrainNode->TrainWaitOrder->rear->next;
	TrainNode->TrainWaitOrder->rear->next = p;
	TrainNode->TrainWaitOrder->rear = p;
	
	t = VL_OrderID->next;
	// ������Ϣ���p���붩����ų���
	while (t)
	{
		// tָ��ǰ�������
		if (strcmp(BF_Merge_Char(t->ID),BF_Merge_Char(_OrderNum)) == 0)
		{
			t->OrderKind = "W"; // ��������Ϊ�򲹶���
			t->WaitOrderNode = p; // ����ǰ�������ӽ���������
			break; // �˳�ѭ��
		}
		// tָ����һ�Ŷ���
		t = t->next;
	}

	return OK;
}

// ��ѯ�򲹶����ܷ�򲹲�����
Status OM_CheckWaitOrder(SearchWaitResult* SWR)
{

}
