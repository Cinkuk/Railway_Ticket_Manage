// ���ļ�Ϊ�����������ڵ��ø�ģ�鲢ʵ�����û��Ľ���
//
// Test Status: Undo
// Code Status: Undo


#include "V_Lib.h"
#include "F_Lib.h"

void WAIT_main()
{
	while (True)
	{
		// ��������зָ�
		printf("%s\n","-------------------------------------------------------------------------------------------------------------------");
		printf("------------------------------------------��ӭʹ���г�Ʊ��ϵͳ------------------------------------------\n\n");
		printf("\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\n", "1����Ʊ����", "2�����붩���Ų�ѯ����", "3�������ֻ��Ų�ѯ����", "4����Ʊ", "5���˳�ϵͳ");
		printf("------------------------------------------\n\n");
		
		char command;
		while (True)
		{
			printf("������Ҫ�����Ĺ��ܣ�����1-5����");
			scanf("%c", &command);
			getchar();
			if (command >= 49 && command <= 53)
			{
				switch (command)
				{
				case 49: {CheckTrain(); break; }
				case 50: {CheckOrder(); break; }
				case 51: {ChechPhoneOrder(); break; }
				case 52: {WithdrawOrder(); break; }
				case 53: {ExitSys(); break; }
				}
			}
			else printf("��������ȷ������\n");
		}
	}
}