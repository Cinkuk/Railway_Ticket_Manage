// ���ļ���ŵĺ���������ʾ��Ϣ
// ���ļ��ĺ�������'DP_'��ͷ
//
// Test Status: Working
// Code Status: Working

#include "F_Lib.h"
#include "V_Lib.h"

void DP_CheckTrain()
{
	char Leave[150];
	char Arrive[150];
	char command;
	char in_command;
	SearchResult* SR;
	SearchResult *p;

	while (True)
	{

		printf("����������أ�");
		scanf("%s", &Leave);
		getchar();
		printf("������Ŀ�ĵأ�");
		scanf("%s", &Arrive);
		getchar();

		printf("�������ǣ�%s\n", Leave);
		printf("Ŀ�ĵ��ǣ�%s\n", Arrive);
	
		// ��ȡ��ѯ���
		SR = UF_SearchStop(Leave, Arrive);
		p = SR->NextResult;

		// ��������ʾ��ѯ���
		system("cls");
		printf("\n\n");
		printf("%5s��ѯ����%s��%s�İ�����£�\n"," ", Leave, Arrive);

		if (!SR) printf("%5s��ѯ�������ð��\n", " ");
		else if (SR)
		{
			printf("%5s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
					" ", " ", "���α��", " ",  " ", "������", " ", " ", "�����", " "," ", "����ʱ��", " "," ", "����ʱ��", " ", " ", "��Ʊ����", " ", " ");
			while (p)
			{
				printf("%5s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
						" ", " ", p->TrainNum, " ",  " ", p->Leave, " ", " ", p->Arrive, " "," ", BF_TimeToStr(p->LeaveTime[0], p->LeaveTime[1]), " ", " ", BF_TimeToStr(p->ArriveTime[0], p->ArriveTime[1]), " ", " ", BF_IntToStr(p->TrainNode->SurplusTicket), " ", " ");
				p = p->NextResult;
			}

		}
		printf("%s\n", "------------------------------------------------------------------------------------------------------------");
		printf("\n\t��������һ��ָ��:\n");
		
		// ���β�ѯ�޿��ð�� 
		if (!SR)
		{
			printf("\t%s\n\t%s\n\n", "1�����²�ѯ", "2���˳���ѯ");
			printf("������Ҫ�����Ĺ��ܣ�����1-2����");
			while (True)
			{

				scanf("%c", &command);
				getchar();
				if (command >= 49 && command <= 50)
				{
					switch (command)
					{
					case 49: {system("cls"); break; }
					case 50: {system("cls"); return; }
					}
				}
				else printf("��������ȷ������\n");
			}
		}
		// ���β�ѯ�п��ð��
		else if (SR)
		{
			printf("\t% s\n\t% s\n\t% s\n\t% s\n\t% s\n\n", "1�����ճ���ʱ������", "2�����յ���ʱ������", "3����������ʱ������", "4����Ʊ", "5���˳���ѯ");
			printf("������Ҫ�����Ĺ��ܣ�����1-5����");
			while (True)
			{

				scanf("%c", &command);
				getchar();
				if (command >= 49 && command <= 53) while(True) 
				{
					switch (command)
					{
						// ����ʱ������
						case 49: 
						{
							sys("cls");
							printf("%5s��ѯ����%s��%s�İ�����£�\n"," ", Leave, Arrive);
							p = UF_LeaveTimeSort(SR);
							printf("%5s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n", \
								" ", " ", "���α��", " ", " ", "������", " ", " ", "�����", " ", " ", "����ʱ��", " ", " ", "����ʱ��", " ", " ", "��Ʊ����", " ", " ");
							while (p)
							{
								printf("%5s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n", \
									" ", " ", p->TrainNum, " ", " ", p->Leave, " ", " ", p->Arrive, " ", " ", BF_TimeToStr(p->LeaveTime[0], p->LeaveTime[1]), " ", " ", BF_TimeToStr(p->ArriveTime[0], p->ArriveTime[1]), " ", " ", BF_IntToStr(p->TrainNode->SurplusTicket), " ", " ");
								p = p->NextResult;

							}
							
							// ������������˵�
							printf("%s\n", "------------------------------------------------------------------------------------------------------------");
							printf("\n\t��������һ��ָ��:\n");
							command = -1;
						}
						// ����ʱ������ 
						case 50: 
						{

							sys("cls");
							printf("%5s��ѯ����%s��%s�İ�����£�\n"," ", Leave, Arrive);
							p = UF_RunTimeSort(SR);
							printf("%5s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n", \
								" ", " ", "���α��", " ", " ", "������", " ", " ", "�����", " ", " ", "����ʱ��", " ", " ", "����ʱ��", " ", " ", "��Ʊ����", " ", " ");
							while (p)
							{
								printf("%5s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n", \
									" ", " ", p->TrainNum, " ", " ", p->Leave, " ", " ", p->Arrive, " ", " ", BF_TimeToStr(p->LeaveTime[0], p->LeaveTime[1]), " ", " ", BF_TimeToStr(p->ArriveTime[0], p->ArriveTime[1]), " ", " ", BF_IntToStr(p->TrainNode->SurplusTicket), " ", " ");
								p = p->NextResult;

							}
							
							// ������������˵�
							printf("%s\n", "------------------------------------------------------------------------------------------------------------");
							printf("\n\t��������һ��ָ��:\n");
							command = -1;
						}
						// ����ʱ������
						case 51: 
						{ 

							sys("cls");
							printf("%5s��ѯ����%s��%s�İ�����£�\n"," ", Leave, Arrive);
							p = UF_ArriveTimeSort(SR);
							printf("%5s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n", \
								" ", " ", "���α��", " ", " ", "������", " ", " ", "�����", " ", " ", "����ʱ��", " ", " ", "����ʱ��", " ", " ", "��Ʊ����", " ", " ");
							while (p)
							{
								printf("%5s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n", \
									" ", " ", p->TrainNum, " ", " ", p->Leave, " ", " ", p->Arrive, " ", " ", BF_TimeToStr(p->LeaveTime[0], p->LeaveTime[1]), " ", " ", BF_TimeToStr(p->ArriveTime[0], p->ArriveTime[1]), " ", " ", BF_IntToStr(p->TrainNode->SurplusTicket), " ", " ");
								p = p->NextResult;

							}
							// ������������˵�
							printf("%s\n", "------------------------------------------------------------------------------------------------------------");
							printf("\n\t��������һ��ָ��:\n");
							command = -1;
						}
						// ��Ʊ
						case 52:
						{ 
							
						}
						// �˳���ѯ
						case 53: 
						{
							system("cls"); return; 
						}
						// ���½���˵�
						case -1:
						{
							printf("\t% s\n\t% s\n\t% s\n\t% s\n\t% s\n\n", "1�����ճ���ʱ������", "2�����յ���ʱ������", "3����������ʱ������", "4����Ʊ", "5���˳���ѯ");
							printf("������Ҫ�����Ĺ��ܣ�����1-5����");
							scanf("%c", &in_command);
							getchar();
							if (in_command >= 49 && in_command <= 53) command = in_command;
							else
							{
								printf("��������ȷ������\n");
							}
						}
					} // switch (command)
				} // if (command >= 49 && command <= 53)
				else printf("��������ȷ������\n");
			}
		}


	}

	return;
}

// ���붩���Ų�ѯ����
void DP_CheckOrder()
{

	char* OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);
	char* ph = (char*)malloc(sizeof(char) * STRLENGTH);
	OrderSet* order;

	while (True)
	{
		while (True)
		{
			printf("�����붩���ţ�");
			scanf("%s", &OrderNum);
			getchar();
			if (strlen(OrderNum) != 10 )
			{
				printf("�����Ÿ�ʽ����ȷ������������\n");
				continue;
			}
			else if (strlen(OrderNum) == 10) break;
		}
		while (True)
		{
			printf("�������ֻ��ţ�");
			scanf("%s", &ph);
			getchar();
			if (strlen(ph) != 11)
			{
				printf("�ֻ��Ÿ�ʽ����ȷ������������11λ�ֻ���\n");
				continue;
			}
			else if (strlen(ph) == 11) break;

		}

		order = UF_GetOrderInfo(OrderNum);

		if (!order)
		{
			printf("�޴˶����ţ�����������\n");
		}
		else if (order) break;

	}
	
	while (True)
	{
		// �ö���Ϊ��ʽ����
		if (strcmp(order->OrderKind, "F") == 0)
		{
			while (True)
			{

				if (strcmp(order->OrderNode->phone, ph) == 0)
				{
					printf("��ѯ���������Ϊ%s����Ϣ���£�\n\n", OrderNum);
					printf("�������ͣ���ʽ����\n");
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%5s\n",\
					" ", " ", "���α��", " ", " ", "�������", " ", " ", "������", " ", " ", "�����", " ", " ", "��Ʊ����", " ", " ");
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%5s\n",\
					" ", " ", order->OrderNode->TrainNum, " ", " ", OrderNum,  " ", " ", order->OrderNode->Start, " ", " ", order->OrderNode->End, " ", " ", BF_IntToStr(order->OrderNode->TicketNum), " ", " ");
				}
				else
				{
					printf("�ֻ��Ų���ȷ�����������룬��q�˳���ѯ��");
					scanf("%s", ph);
					getchar();
					if (strcmp(ph, "q") == 0) return;
				}
			}
		}
		// �ö���Ϊ�򲹶���
		else if (strcmp(order->OrderKind, "W") == 0)
		{
			
			while (True)
			{

				if (strcmp(order->WaitOrderNode->phone, ph) == 0)
				{
					printf("��ѯ���������Ϊ%s����Ϣ���£�\n\n", OrderNum);
					printf("�������ͣ��򲹶���\n");
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%5s\n",\
					" ", " ", "���α��", " ", " ", "�������", " ", " ", "������", " ", " ", "�����", " ", " ", "��Ʊ����", " ", " ");
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%5s\n",\
					" ", " ", order->WaitOrderNode->TrainNum, " ", " ", OrderNum,  " ", " ", order->WaitOrderNode->Start, " ", " ", order->WaitOrderNode->End, " ", " ", BF_IntToStr(order->WaitOrderNode->TicketNum), " ", " ");
				}
				else
				{
					printf("�ֻ��Ų���ȷ�����������룬��q�˳���ѯ��");
					scanf("%s", ph);
					getchar();
					if (strcmp(ph, "q") == 0) return;
				}
			}
		}
	}
	
	return;
}

void DP_ChechPhoneOrder()
{
	// ���������ֻ��š�
	// ��ʾ��Ϣ ��/��

	// ����������������ء� getchar

	printf("Enter 3\n");
	return;
}

void DP_WithdrawOrder()
{
	// �����붩���ֻ���
	// ������Ҫȡ���Ķ���

	// -�����Ŵ���-���������룬��������˳�
	// -��������ȷ-\n
	// ��Ҫȡ���Ķ�����Ϣ���£�
	//
	// ȷ��ȡ���˶��������������ָ���������˳��������Իᱻ������
	// y��ȷ��ȡ���˶���
	// n�������˶���
	// ������ָ�

	printf("Enter 4\n");
	return;
}

void DP_ExitSys()
{
	// ��л��ʹ�ñ�ϵͳ����ȷ���Ƿ�Ҫ�˳�
	// y��ȷ���˳�
	// n��ȡ��

	printf("Enter 5\n");
	return;
}
