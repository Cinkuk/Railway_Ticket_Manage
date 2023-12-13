// ���ļ����ڶ��ļ����ж�д����
// ���ļ��ĺ�������'FO_'��ͷ
//
// Test Status: Finished
// Code Status: Freeze
//
// �����빦�ܶ�Ӧ��
//
// �Ӵ��̶�ȡ����
// Status FO_LoadTrainFromHD() 
// return: ERROR���ļ���ʧ�ܣ�, NOSPACE��û���ڴ�����ļ���, OK
// 

#include "F_Lib.h"
#include "V_Lib.h"

// �Ӵ��̶�ȡ����
// freeze
Status FO_LoadTrainFromHD()
{
	FILE* fp;
	char* filename = "TrainDB.csv";
	fp = fopen(filename, "r");

	int BlockBegin = 0; // 0������֮������ݣ�1����¼֮�������
	int coloum_index = 0; // �к�
	int row_index = 0; // �к�
	
	// �ļ���ʧ��
	if (fp == NULL)
	{
		return ERROR;
	}

	// ��ȡÿ�е��ַ�
	char line[LINELENGTH];
	char* token;

	// ���������洢ÿ��ȡһ��������Ϣ����Ҫ�Ĵ洢�ռ�
	ReadTrain* ReadBlock, *p, *q;
	ReadBlock = (ReadTrain*)malloc(sizeof(ReadTrain));
	if (!ReadBlock) return NOSPACE; // �޿��ÿռ�
	ReadBlock->NextLine = NULL;

	// ���л�ȡ����
	while (fgets(line, LINELENGTH, fp) != NULL)
	{
		// ÿ�ж�ȡ��������Ĵ洢�ռ�
		// �ṹ��
		ReadTrain* ReadLine;
		ReadLine = (ReadTrain*)malloc(sizeof(ReadTrain));
		if (!ReadLine) return NOSPACE; // �޿��ÿռ�
		// �ַ���
		char* l1 = (char*)malloc(sizeof(char) * STRLENGTH);
		char* l2 = (char*)malloc(sizeof(char) * STRLENGTH);
		char* l3 = (char*)malloc(sizeof(char) * STRLENGTH);
		ReadLine->c1 = l1;
		ReadLine->c2 = l2;
		ReadLine->c3 = l3;
		ReadLine->NextLine = NULL;

		// ��ȡ���ŷָ��ĵ�һ���ַ���
		token = strtok(line, ",");

		// �����зǿ�
		while (token != NULL)
		{
			// �к�����
			coloum_index++;

			// �ж�token��ȡ���ַ���λ��
			// ��Ϣ�鿪ʼ
			if (strcmp(token, "BOT") == 0) BlockBegin = 1;
			
			// ��Ϣ�����
			else if (strcmp(token, "EOT") == 0) BlockBegin = 0;

			// ���ж�ȡ�ַ�
			if (!(strcmp(token, "\n") == 0)) // ���ǻ��з�
			{
				switch (coloum_index)
				{
				case 1: {strcpy(l1, token); break; }
				case 2: {strcpy(l2, token); break; }
				case 3: {strcpy(l3, token); break; }
				} // switch (coloum_index)
			} // if (!(strcmp(token, "\n") == 0))

			// ��ȡ��һ���ɿո�ָ����ַ���
			token = strtok(NULL, ",");
		
		} // while (token != NULL)

		// �������ݷָ���ȡ�꣬�����к�
		coloum_index = 0;

		// ��ȡ�걾����Ϣ��д��ṹ�壬׼����ʼ��ȡ��һ��
		p = ReadBlock;
		// pָ��ReadBlockβ���
		// ������Ϊ�������ݣ��洢
		if (!(strcmp(ReadLine->c1, "BOT") == 0) && !(strcmp(ReadLine->c1, "EOT") == 0))
		{
			while (p)
			{
				// ReadLine���뵽β���֮��
				if (!(p->NextLine))
				{
					ReadLine->NextLine = NULL;
					p->NextLine = ReadLine;
					break;
				}
				p = p->NextLine;
			} // while (p)
		} // if (!(strcmp(ReadLine->c1, "BOT") == 0) && !(strcmp(ReadLine->c1, "EOT")))

		// �ж��Ƿ�Ϊһ��������Ϣ��ȡ��ϣ���ȡ����򴴽��³���
		// 1. BlockBegin=0, 2.ReadBlock���ٶ�ȡ�����е���Ϣ
		if (BlockBegin == 0 && ReadBlock->NextLine->NextLine)
		{
			// �����³�����Ҫ�Ŀռ����
			char* _TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
			char* _Start = (char*)malloc(sizeof(char) * STRLENGTH);
			char* _End = (char*)malloc(sizeof(char) * STRLENGTH);
			int _Occupant;
			int _SurplusTicket;
			StopName* _StopList = (StopName*)malloc(sizeof(StopName));
			StopName* NewS, *ps;
			LeaveTime* _LeaveTime = (LeaveTime*)malloc(sizeof(LeaveTime));
			LeaveTime* NewL, *pl;
			int time = 0;
			// �ռ������ֵ
			strcpy(_TrainNum, ReadBlock->NextLine->c1); // _TrainNum
			_Occupant = BF_StrToInt(ReadBlock->NextLine->c2); // _Occupant
			_SurplusTicket = BF_StrToInt(ReadBlock->NextLine->c3); // SurplusTicket
			strcpy(_Start, ReadBlock->NextLine->NextLine->c1); // _Start

			_StopList->next = NULL;
			_LeaveTime->next = NULL;
			// ������ȡ�����ݴ����Ӧ�ṹ��
			p = ReadBlock->NextLine->NextLine;
			while (p)
			{
				// �½��
				NewS = (StopName*)malloc(sizeof(StopName));
				NewL = (LeaveTime*)malloc(sizeof(LeaveTime));
				char* NewStopName = (char*)malloc(sizeof(char) * STRLENGTH);
				strcpy(NewStopName, p->c1);
				NewS->name = NewL->name = NewStopName; // BOTH.name
				// ���Ϊ���һվ
				if (!(p->NextLine))
				{
					_End = p->c1;
					NewL->hour = NewL->min = NewL->hour = -1;
				}
				else
				{
					NewL->ToNextMin = BF_StrToInt(p->c3); // LeaveTime.ToNextTime
					time = BF_StrToMin(p->c2);
					NewL->hour = time / 60;
					NewL->min = time % 60;
				}
				NewL->next = NULL;
				NewS->next = NULL;
				
				// NewS����Ϊβ���
				ps = _StopList;
				while (ps)
				{
					if (!(ps->next))
					{
						ps->next = NewS;
						break;
					}
					ps = ps->next;
				}
				// NewL����Ϊβ���
				pl = _LeaveTime;
				while (pl)
				{
					if (!(pl->next))
					{
						pl->next = NewL;
						break;
					}
					pl = pl->next;
				}
				p = p->NextLine;
			} // while (p)
			// ��������
			TM_NewTrain(_TrainNum, _Start, _StopList, _End, _LeaveTime, _Occupant, _SurplusTicket);
			S_AddTrainToSearchDB(_TrainNum, _StopList);

			// ���ReadBlock������ReadBlock��Nextָ��ΪNULL
			p = ReadBlock->NextLine; // pָ����Ԫ���
			while (p)
			{
				q = p; // qָ�����ͷŵĽ��
				p = p->NextLine; // p����
				free(q); // �ͷ�q
			} // while (p)
			ReadBlock->NextLine = NULL;

			// �ͷ��������ͷŵ��ڴ�
			free(_TrainNum);
			free(_Start);
			free(_End);

		} // if (BlockBegin == 0 && ReadBlock->NextLine->NextLine)

	} // while (fgets(line, LINELENGTH, fp) != NULL)

	fclose(fp);
	return OK;
}

