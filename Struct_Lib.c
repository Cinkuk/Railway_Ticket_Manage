// ���ļ����Դ����Ŀ����Ľṹ�嶨��ͳ�������
//
// Test Status: Undo
// Code Status: Undo

#define OK 1
#define ERROR 0
#define OVERFLOW -10
#define EMPTY -11
#define NOSPACE -12

#define True 1
#define False 0

#define STATIONNAME 20

// �洢;��վ�����ֵ���ʽ��
typedef struct StopName {
	char name[STATIONNAME];
	struct StopName* next;
}StopName;

// �洢����վ�㷢��ʱ��
typedef struct LeaveTime {
	char name[STATIONNAME]; // վ������
	int hour; // ����xia
}LeaveTime;
// �洢������Ϣ
typedef struct SUB_TrainInfo {
	char TrainNum[6]; // ����
	char Start[STATIONNAME]; // ʼ��վ
	struct StopName Stop; // ;��վ
	char End[STATIONNAME]; // �յ�վ

}SUB_TrainInfo;
