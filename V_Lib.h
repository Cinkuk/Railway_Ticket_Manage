// ��ͷ�ļ����ڼ�¼���ڿ�����Ŀ�й��õı������ͽṹ����
//
// Code Status: Undo
// ��ͷ�ļ����ڼ�¼���ڿ�����Ŀ�й��õı��������ṹ�塢����
//
// Code Status: Working

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
// ÿһ���εĶ�����Ϣ��������
typedef struct Order {
	char NodeKine; // �ڵ����H:ͷ��㣬E������Ԫ�ؽ��
	char* OrderNum; // �������
	char* TrainNum; // ����
	int phone; // �ֻ���
	char* Start; // ����վ
	char* End; // �յ�վ
	int TicketNum; // ������Ʊ����

	struct Order* next; // ��һ�ݶ���
}Order;

// �򲹶�����Ϣ
// ѭ������
typedef struct WaitOeder {
	char NodeKine; // �ڵ����H:ͷ��㣬E������Ԫ�ؽ��
	char *OrderNum; // �������
	char *TrainNum; // ����
	int phone; // �ֻ���
	char* Start; // ����վ
	char* End; // �յ�վ
	int TicketNum; // ������Ʊ����

	struct WaitOrder* rear; // �򲹶���βָ�룬�޺�ʱָ��ͷ���
}WaitOrder;

// �洢������Ϣ
// ���������ճ������ֵ�������
typedef struct SUB_TrainInfo {
	char NodeKind; // ������H��ͷ�ڵ㣬E������Ԫ�ؽ��
	// ����ʮλ��ָ������
	// ���ڴ��ָ����0-9��ͷ�ĳ���������С�ĳ��ε�ָ�룬���ڼӿ����
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
	char NodeKind; // ������H��ͷ��㣬E������Ԫ�ؽ��
	char OrderStatus; // ����״̬��F����ʽ������W���򲹶���
	Order* CurrentOrder; // ָ��ǰ��������򲹶������
	SUB_TrainInfo* Train; // ָ��ǰ���ν��

	struct PhoneOrderList* NextOrder; // ͬһ�ֻ��ŵ���һ����
}PhoneOrderList;

// ���ڴ洢�ֻ��Ŷ�Ӧ�Ķ�����
typedef struct PhoneOrder {
	char NodeKind; // ������H��ͷ��㣬E������Ԫ�ؽ��
	char* phone; // �ֻ���
	PhoneOrderList* OrderList; // ��ǰ�ֻ����µ�ȫ������

	struct PhoneOrder* next; // ��һ�ֻ���
}PhoneOrder;

//////////
// ����
extern TOP_TrainInfo* VL_Ti_Lib; // ����Ʊ���α�������Ŀ�й���
extern PhoneOrder* VL_Or_Lib; // ��������Ϣ��������Ŀ�й���
