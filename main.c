// ���ļ�Ϊ�����������ڵ��ø�ģ�鲢ʵ�����û��Ľ���
//
// Test Status: Undo
// Code Status: Undo


#include "V_Lib.h"
#include "F_Lib.h"

void main()
{
	S_InitSIDB();
	S_InitTIDB();
	TM_InitTicket();
	OM_InitOrder();
	OM_InitOrderID();
	FO_LoadTrainFromHD();

	while (True)
	{
		
		char command;
		while (True)
		{
			system("cls");
			printf("\n\n------------------------------------------��ӭʹ���г�Ʊ��ϵͳ------------------------------------------\n\n");
			printf("\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\n", "1����Ʊ����", "2�����붩���Ų�ѯ����", "3�������ֻ��Ų�ѯ����", "4����Ʊ", "5���˳�ϵͳ");
			printf("------------------------------------------\n\n");
			while (True)
			{
				printf("\t������Ҫ�����Ĺ��ܣ�����1-5����");
				scanf("%c", &command);
				getchar();
				if (command >= 49 && command <= 53)
				{
					switch (command)
					{
					case 49: {DP_CheckTrain(); break; }
					case 50: {DP_CheckOrder(); break; }
					case 51: {DP_CheckPhoneOrder(); break; }
					case 52: {DP_WithdrawOrder(); break; }
					case 53: {DP_ExitSys(); break; }
					}
					break;
				}
				else printf("\t��������ȷ������\n");
			}
		}
	}
}