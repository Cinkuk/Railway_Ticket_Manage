// ��ͷ�ļ����ڼ�¼���ڿ�����Ŀ�й��õı������ͽṹ����
//
// Code Status: Undo
// ��ͷ�ļ����ڼ�¼���ڿ�����Ŀ�й��õı��������ṹ�塢����
//
// Code Status: Working

//////////
// ����ָ��
// ��ֹ�ṹ���ظ�����
#pragma once
// ����ʹ��strcpy
#define _CRT_SECURE_NO_WARNINGS


//////////
// ����
// ״̬�ʹ�����Ϣ
#define OK 1
#define ERROR 0
#define OVERFLOW -10
#define EMPTY -11
#define NOSPACE -12

// ����ֵ
#define True 1
#define False 0

// ���ȳ���
#define STATIONNAME 20
#define STRLENGTH 30

//////////
// ����ֵ����
typedef int Status;
typedef int Bool;

//////////
// �ṹ��
// �洢;��վ�����ֵ���ʽ��
typedef struct StopName {
	 char* name;

	struct StopName* next; // ��һվ������
}StopName;

// �洢����վ�㷢��ʱ�������ʱ����Ϣ
typedef struct LeaveTime {
	char* name; // վ������
	int hour; // ����ʱ��Сʱ
	int min; // ����ʱ�����
	int ToNextMin; // ��������һվ������ʱ��

	struct LeaveTime* next; // ��һվ����Ϣ
}LeaveTime;

// ��һ������Ϣ����
// ÿһ���εĶ�����Ϣ�������
typedef struct Order {
	char* NodeKind; // �ڵ����H:ͷ��㣬E������Ԫ�ؽ��
	char* OrderNum; // �������
	char* TrainNum; // ����
	char* phone; // �ֻ���
	char* Start; // ����վ
	char* End; // �յ�վ
	int TicketNum; // ������Ʊ����

	struct Order* next; // ��һ�ݶ���
}Order;

// �򲹶�����Ϣ
// ѭ������
typedef struct WaitOrder {
	char* NodeKind; // �ڵ����H:ͷ��㣬E������Ԫ�ؽ��
	char* OrderNum; // �������
	char* TrainNum; // ����
	char* phone; // �ֻ���
	char* Start; // ����վ
	char* End; // �յ�վ
	int TicketNum; // ������Ʊ����

	struct WaitOrder* rear; // �򲹶���βָ�룬�޺�ʱָ��ͷ���
	struct WaitOrder* next;
}WaitOrder;

// �洢������Ϣ
// �������ճ������ֵ�������
typedef struct SUB_TrainInfo {
	char* NodeKind; // ������H��ͷ�ڵ㣬E������Ԫ�ؽ��
	// ����ʮλ��ָ������
	// ���ڴ��ָ����1-9��ͷ�ĳ���������С�ĳ��ε�ָ�룬���ڼӿ���������õ�0λ
	struct SUB_TrainInfo* FirstNum[10];
	char* TrainNum; // ����
	char* Start; // ʼ��վ
	StopName* Stop; // ;��վ
	char* End; // �յ�վ
	LeaveTime*  StationLeaveTime; // ��վ�㷢��ʱ�������ʱ����Ϣ
	int OccupantQuota; // ��Ա����
	int SurplusTicket; // ��Ʊ����

	Order *TrainOrder; // ���ڸó��εĶ���
	WaitOrder *TrainWaitOrder; // ���ڸó��εĺ򲹶���

	struct SUB_TrainInfo* next; // ��һ����
}SUB_TrainInfo;

// ʵ��������Ʊ��Ϣ����
// ����Ӫʱ�����ֳ��ο�ͷ����11�ֿ�ͷ
typedef struct TOP_TrainInfo {
	SUB_TrainInfo* G;
	SUB_TrainInfo* D;
	SUB_TrainInfo* C;
	SUB_TrainInfo* Z;
	SUB_TrainInfo* T;
	SUB_TrainInfo* K;
	SUB_TrainInfo* Y;
	SUB_TrainInfo* L;
	SUB_TrainInfo* S;
	SUB_TrainInfo* N; // �����ĳ��κ�Ϊ������
	SUB_TrainInfo* P;
}TOP_TrainInfo;

// ��������ͬһ�ֻ����µ����ж���
typedef struct PhoneOrderList {
	char* NodeKind; // ������H��ͷ��㣬E������Ԫ�ؽ��
	char* OrderStatus; // ����״̬��F����ʽ������W���򲹶���
	Order* CurrentOrder; // ָ��ǰ��ʽ�������
	WaitOrder* CurrentWaitOrder; // ָ��ǰ�򲹶������
	SUB_TrainInfo* Train; // ָ��ǰ���ν��
	char* LeaveStop; // ����վ
	char* ArriveStop; // ����վ
	int TicketAmount; // ����Ʊ��

	struct PhoneOrderList* NextOrder; // ͬһ�ֻ��ŵ���һ����
}PhoneOrderList;

// ���ڴ洢�ֻ��Ŷ�Ӧ�Ķ�����
typedef struct PhoneOrder {
	char* NodeKind; // ������H��ͷ��㣬E������Ԫ�ؽ��
	char* phone; // �ֻ���
	PhoneOrderList* OrderList; // ��ǰ�ֻ����µ�ȫ������

	struct PhoneOrder* next; // ��һ�ֻ���
}PhoneOrder;

// ���ڼ��������ݿ�
// �Գ�������վ��
//
// վ�������� 
typedef struct StationList
{
	char* StationName; // ��վ����
	struct StationList* next; // ��һվ
}StationList;

//��������
typedef struct TrainIndexNode
{
	char* NodeKind; // ������ͣ�H��ͷ��㣬E������Ԫ�ؽ��
	struct TrainIndexNode* NumIndex[10]; // ��λ���ּӿ������ָ������
	char* TrainNum; // ���α��
	StationList* StationNameList; // ���н������ŵ�����վ��
}TrainIndexNode;

// ���ݿ�ṹ��
typedef struct TrainIndexDB
{
	TrainIndexNode* G;
	TrainIndexNode* D;
	TrainIndexNode* C;
	TrainIndexNode* Z;
	TrainIndexNode* T;
	TrainIndexNode* K;
	TrainIndexNode* Y;
	TrainIndexNode* L;
	TrainIndexNode* S;
	TrainIndexNode* N;
	TrainIndexNode* P;
}TrainIndexDB;

// ������ų�
typedef struct OrderSet
{
	// ������Ÿ�ʽΪһλ��ĸ+9λ����
	char ID[10];
	char OrderKind; // �������F:��ʽ������W���򲹶���
	Order* OrderNode;
	WaitOrder* WaitOrderNode;
	struct OrderSet* next;
}OrderSet;


// ��վ����������
//
// ���α���б�
typedef struct TrainNumList
{
	// ����ͷ���
	char* CurNum; // �ý�㳵�α��
	struct TrainNumList* next;
}TrainNumList;

// վ�����б�
typedef struct StopIndexDB
{
	char* NodeKind; // ������ͣ�H��ͷ��㣬E������Ԫ�ؽ��
	char* StationName; // վ������
	TrainNumList* TrainList; // �����б�
	struct StopIndexDB* next; // ��һվ��
}StopIndexDB;

// ��Ѱ���
typedef struct SearchResult
{
	// ��ͷ���
	char* TrainNum;  // ���α��
	char* Leave; // ������
	char* Arrive; // �����
	int LeaveTime[2]; // ����ʱ��
	int ToNextMin;
	int ArriveTime[2]; // ����ʱ��

	SUB_TrainInfo* TrainNode; // ������Ϣ���

	struct SearchResult* NextResult;
}SearchResult;

// �򲹶�����ѯ���ؽ��
typedef struct SearchWaitResult
{
	Order* TransOrder; // תΪ��ʽ�����Ķ������
	struct SearchWaitResult* next;
}SearchWaitResult;

//////////
// ����
extern TOP_TrainInfo* VL_Ti_Lib; // ����Ʊ���α�������Ŀ�й���
extern PhoneOrder* VL_Or_Lib; // ��������Ϣ��������Ŀ�й���
extern TrainIndexDB* VL_TI_DB; // ���μ���վ������ݿ�
extern StopIndexDB* VL_SI_DB; // վ��������ε����ݿ�
extern OrderSet* VL_OrderID; // ������ų�
