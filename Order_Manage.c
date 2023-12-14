// ���ļ����ڴ�Ŷ�������ĺ���
// �������Ĺؼ����������Variables_Lib.c��
// ���ļ��ĺ�������'OM_'��ͷ
//
// Test Status: Finished
// Code Status: Freeze
//
// �����빦�ܶ�Ӧ:
// 
// ��ʼ��VL_Or_Lib
// Status OM_InitOrder()
// ����ֵ��NOSPACE, OK
// 
// // ��ʼ��������
// Status OM_InitOrderID()
// 
// ����Ψһ�Ķ������
// char* OM_CreateOrderNum()
// return: ��������ַ���ָ��
// 
// ��ȡ��һ�Ŷ����ı��
// char* OM_NextOrderNum()
//
// �����µ���ʽ����
// Status OM_New_F_Order(char* _phone, char* _TrainNum,
//	                     char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
// input���ֻ��š����Ρ�����վ������վ����Ʊ����
// return: NOSPACE, OK, ERROR
//
// �����µĺ򲹶���
// Status OM_New_W_Order(char* _phone, char* _TrainNum,
//	                    char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
// input���ֻ��š����Ρ�����վ������վ����Ʊ����
// return: NOSPACE, OK
//
// ��ѯ�򲹶����ܷ�򲹲�����
// Status OM_CheckWaitOrder(SearchWaitResult* SWR)
// output: OK���к򲹶������ɹ��򲹣���EMPTY���޿��Խ��к򲹲����Ķ�����
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

// ��ȡ��һ�Ŷ����ı��
// Freeze
char* OM_NextOrderNum()
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

	q->CurrentWaitOrder = NULL;

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

	q->CurrentOrder = NULL;
	
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
// Freeze
Status OM_CheckWaitOrder()
{
	// ����ָ��
	OrderSet* CurID = VL_OrderID->next;
	OrderSet* ChangedID;
	PhoneOrder* PhOrderNode; // �������ݿ���ֻ��Ž��
	PhoneOrderList* pre_PhOrder, * PhOrder; // �������ݿ��ֻ��Ŷ�����ǰһ��������㣬��Ӧ��Ӧ�������
	SUB_TrainInfo* TrainNode; // ���ν��
	WaitOrder* WTrainNode, * pre_WTrainNode; // �������ݿ��еĺ򲹶�����㣬����ǰһ�����

	// ���ڲ���Ķ������
	Order* NewTOrder;
	PhoneOrderList* NewPOrder;

	// ������Ϣ
	char* OrderNum, * TrainNum, * phone, * Start, * end, * NodeKind;
	int TicketNum;


	// ����������
	while (CurID)
	{
		// ��ǰ����Ϊ��ʽ����
		if (strcmp(CurID->OrderKind, "F") == 0) CurID = CurID->next;

		// ��ǰ����Ϊ�򲹶���
		else if (strcmp(CurID->OrderKind, "W") == 0)
		{
			// ��¼���κ�
			TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
			if (!TrainNum) return NOSPACE;
			memset(TrainNum, 0, sizeof(char) * STRLENGTH);
			strcpy(TrainNum, CurID->WaitOrderNode->TrainNum);

			// ��λ���ν��
			TrainNode = S_GetTrainNode(TrainNum);

			// �ж���Ʊ�Ƿ����
			// ���㣬�ͷ��ڴ棬ɨ����һ�Ŷ���
			if (TrainNode->SurplusTicket < CurID->WaitOrderNode->TicketNum)
			{
				CurID = CurID->next;
				continue;
			}
			// �㹻�������
			else if (TrainNode->SurplusTicket >= CurID->WaitOrderNode->TicketNum)
			{
				// ���복�κ򲹶������
				pre_WTrainNode = TrainNode->TrainWaitOrder->rear->next; // ����ͷ�ڵ�ڵ�

				// ����˳λ�ж�
				while (strcmp(pre_WTrainNode->next->NodeKind, "H") != 0)
				{
					// ��һ˳λ����Ʊ��������Ʊ��������һ˳λ
					if (pre_WTrainNode->next->TicketNum > TrainNode->SurplusTicket)
						pre_WTrainNode = pre_WTrainNode->next;
					
					// ��һ˳λ����Ʊ��С����Ʊ������򲹴���
					else if (pre_WTrainNode->next->TicketNum <= TrainNode->SurplusTicket)
					{
						// �������ݿ��㶨λ
						WTrainNode = pre_WTrainNode->next;

						// ��¼����������Ϣ
						OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);
						phone = (char*)malloc(sizeof(char) * STRLENGTH);
						Start = (char*)malloc(sizeof(char) * STRLENGTH);
						end = (char*)malloc(sizeof(char) * STRLENGTH);
						NodeKind = (char*)malloc(sizeof(char) * STRLENGTH);

						if (!OrderNum || !phone || !Start || !end || !NodeKind) return NOSPACE;
						memset(OrderNum, 0, sizeof(char) * STRLENGTH);
						memset(phone, 0, sizeof(char) * STRLENGTH);
						memset(Start, 0, sizeof(char) * STRLENGTH);
						memset(end, 0, sizeof(char) * STRLENGTH);
						memset(NodeKind, 0, sizeof(char) * STRLENGTH);

						strcpy(OrderNum, WTrainNode->OrderNum);
						strcpy(TrainNum, WTrainNode->TrainNum);
						strcpy(phone, WTrainNode->phone);
						strcpy(Start, WTrainNode->Start);
						strcpy(end, WTrainNode->End);
						strcpy(NodeKind, "E");
						TicketNum = WTrainNode->TicketNum;

						// д���½��
						NewTOrder = (Order*)malloc(sizeof(Order));
						if (!NewTOrder) return NOSPACE;
						memset(NewTOrder, 0, sizeof(Order));
						NewTOrder->NodeKind = NodeKind;
						NewTOrder->OrderNum = OrderNum;
						NewTOrder->TrainNum = TrainNum;
						NewTOrder->phone = phone;
						NewTOrder->Start = Start;
						NewTOrder->End = end;
						NewTOrder->TicketNum = TicketNum;

						NewPOrder = (PhoneOrderList*)malloc(sizeof(PhoneOrderList));
						if (!NewPOrder) return NOSPACE;
						memset(NewPOrder, 0, sizeof(Order));
						char* OrderStatus = (char*)malloc(sizeof(char) * STRLENGTH);
						if (!OrderStatus) return NOSPACE;
						memset(OrderStatus, 0, sizeof(char) * STRLENGTH);
						strcpy(OrderStatus, "F");

						NewPOrder->NodeKind = NodeKind;
						NewPOrder->OrderStatus = OrderStatus;
						NewPOrder->OrderNum = OrderNum;
						NewPOrder->LeaveStop = Start;
						NewPOrder->ArriveStop = end;
						NewPOrder->TicketAmount = TicketNum;
						NewPOrder->CurrentWaitOrder = NULL;
						// �������ݿ�ɾ���򲹽��
						pre_WTrainNode->next = WTrainNode->next;
						if (strcmp(pre_WTrainNode->next->NodeKind, "H") == 0) TrainNode->TrainWaitOrder->rear = pre_WTrainNode->next;
				
						// ���복�����ݿ���ʽ�������
						NewTOrder->next = TrainNode->TrainOrder->next;
						TrainNode->TrainOrder->next = NewTOrder;
	

						// �ڶ������ж�λ���
						ChangedID = VL_OrderID->next;
						while (strcmp(BF_Merge_Char(ChangedID->ID), OrderNum) != 0)
							ChangedID = ChangedID->next;
				
						// �ڶ������ݿ��ж�λ�򲹽��
						PhOrderNode = VL_Or_Lib->next;
						while (strcmp(PhOrderNode->phone, phone) != 0)
							PhOrderNode = PhOrderNode->next;
						pre_PhOrder = PhOrderNode->OrderList;
						while (strcmp(pre_PhOrder->NextOrder->OrderNum, OrderNum) != 0)
							pre_PhOrder = pre_PhOrder->NextOrder;
						PhOrder = pre_PhOrder->NextOrder;
				
						// ɾ���򲹽ӵ�
						pre_PhOrder->NextOrder = PhOrder->NextOrder;

						// ������ʽ�������
						NewPOrder->NextOrder = PhOrderNode->OrderList->NextOrder;
						PhOrderNode->OrderList->NextOrder = NewPOrder;

						// ���ӳ��ν��Ͷ������
						NewPOrder->Train = TrainNode;
						NewPOrder->CurrentOrder = TrainNode->TrainOrder;

						// �޸Ķ����ؽ��ָ�����Ϣ
						char* NewOrderKind = (char*)malloc(sizeof(char) * STRLENGTH);
						strcpy(NewOrderKind, "F");
						ChangedID->OrderKind = NewOrderKind;
						ChangedID->WaitOrderNode = NULL;
						ChangedID->OrderNode = NewTOrder;

						// ����ͷ�ڵ�����һ˳λ
						pre_WTrainNode = TrainNode->TrainWaitOrder->rear->next;

					} // else if (pre_WTrainNode->next->TicketNum <= TrainNode->SurplusTicket)
				} // while (strcmp(pre_WTrainNode->next->NodeKind, "H") != 0)

				// ɨ�趩������һ���
				CurID = CurID->next;


			} // else if (TrainNode->SurplusTicket >= CurID->WaitOrderNode->TicketNum)

		} // else if (strcmp(CurID->OrderKind, "W") == 0)
		
	} // while (VL_OrderID)

	return OK;
} // END Function

