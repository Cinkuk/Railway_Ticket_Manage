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

	char TrainNum[10];
	char Phone[20];
	int Ticket;

	SearchResult* SR;
	SearchResult* p, * q;

	while (True)
	{

		printf("����������أ�");
		scanf("%s", &Leave);
		getchar();
		printf("������Ŀ�ĵأ�");
		scanf("%s", &Arrive);
		getchar();

		// ��ȡ��ѯ���
		SR = UF_SearchStop(Leave, Arrive);

		// ��������ʾ��ѯ���
		system("cls");
		printf("\n\n");

		if (!SR) printf("%5s��ѯ������%s��%s�Ŀ��ð��\n%5s��������һ��ָ��\n", " ", Leave, Arrive," ");
		else if (SR)
		{
			// Ĭ���Գ���ʱ������
			p = UF_LeaveTimeSort(SR);
			command = -1;
		}
		
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
					case 49: {system("cls"); printf("\n"); break; }
					case 50: {system("cls"); return; }
					}
				}
				else printf("��������ȷ������\n");
			}
		}
		// ���β�ѯ�п��ð��
		else if (SR)
		{

			while(True) 
			{
				switch (command)
				{
					// ����ʱ������
					case 49: 
					{
						system("cls");
						p = UF_LeaveTimeSort(SR);
						
						command = -1;
					}
					// ����ʱ������ 
					case 50: 
					{
						system("cls");
						p = UF_RunTimeSort(SR);
						// ��ʾ���
						command = -1;
					}
					// ����ʱ������
					case 51: 
					{
						system("cls");
						p = UF_ArriveTimeSort(SR);
						// ��ʾ���
						command = -1;
					}
					// ��Ʊ
					case 52:
					{ 
						// ���복�κ�
						while (True)
						{
							printf("�����복�κţ���ĸ��Ҫ��д����");
							scanf("%s", &TrainNum);
							getchar();
							q = SR->NextResult;
							while (q)
							{
								if (strcmp(q->TrainNum, TrainNum) == 0) break;
								else q = q->NextResult;
							}
							// ���κŲ�����
							if (!q) printf("��������ȷ���κ�\n");
							else if (q) break;
							
						}
						
						// �����ֻ���
						while (True)
						{
							printf("�������ֻ��ţ�");
							scanf("%s", &Phone);
							getchar();
							if (strlen(Phone) == 11) break;
							else printf("��������ȷ��11λ�ֻ���\n");
						}
						
						// ��Ʊ����
						while (True)
						{
							printf("�����붩��������");
							scanf("%d", &Ticket);
							getchar();
							if (Ticket > 0)break;
							else printf("��������ֵΪ����Ʊ��\n");
						}

						// �ж���Ʊ�Ƿ���� 
						// ȷ�϶�����Ϣ
						// ���� ��ʽ����
						if (Ticket < q->TrainNode->SurplusTicket)
						{
							// ȷ����Ϣ
							printf("����Ϊ������Ϣ��\n");
							printf("���α�ţ�%s\n����վ��%s\n����վ��%s\n����ʱ�䣺%s\n����ʱ�䣺%s\n��Ʊ������%d\n", \
								TrainNum, Leave, Arrive, BF_TimeToStr(q->LeaveTime[0], q->LeaveTime[1]), BF_TimeToStr(q->ArriveTime[0], q->ArriveTime[1]), Ticket);
							printf("ȷ�ϣ�\ny��ȷ�϶���\nn����������\n");
							// ȷ�ϲ���
							while (True)
							{
								char* ensure = (char*)malloc(sizeof(char)*10);
								scanf("%s", &ensure);
								getchar();
								if (strcmp(ensure, "y") == 0) break;
								else if (strcmp(ensure, "n") == 0)
								{
									printf("ȡ���µ�������󽫷������˵�\n");
									Sleep(3);
									system("cls");
									return;
								}
								else printf("��������ȷ����ָ��\n");

							}
							if (UF_New_F_Order(TrainNum, Leave, Arrive, Ticket, Phone) == OK)
							{
								printf("\n�µ��ɹ�\n");
								printf("����󽫷������˵�\n");
								Sleep(3);
								system("cls");
								return;
							}
							else
							{
								printf("�����洢����������Զ��������˵�");
								Sleep(3);
								system("cls");
								return;
							}
						}
						// ���� �򲹶���
						else
						{
							// ȷ����Ϣ
							printf("����Ϊ������Ϣ��\n");
							printf("���α�ţ�%s\n����վ��%s\n����վ��%s\n����ʱ�䣺%s\n����ʱ�䣺%s\n��Ʊ������%d\n", \
								TrainNum, Leave, Arrive, BF_TimeToStr(q->LeaveTime[0], q->LeaveTime[1]), BF_TimeToStr(q->ArriveTime[0], q->ArriveTime[1]), Ticket);
							printf("��Ʊ�������㣬�Ƿ����򲹣�\n");
							printf("y�������\nn������\n");
							// ȷ�ϲ���
							while (True)
							{
								char* ensure = (char*)malloc(sizeof(char)*10);
								scanf("%s", &ensure);
								getchar();
								if (strcmp(ensure, "y") == 0) break;
								else if (strcmp(ensure, "n") == 0)
								{
									printf("ȡ���µ�����󽫷������˵�\n");
									Sleep(3);
									system("cls");
									return;
								}
								else printf("��������ȷ����ָ��\n");

							}
							if (UF_New_W_Order(TrainNum, Leave, Arrive, Ticket, Phone) == OK)
							{
								printf("\n����򲹳ɹ�");
								printf("����󽫷������˵�\n");
								Sleep(3);
								system("cls");
								return;
							}
							else
							{
								printf("�����洢����������Զ��������˵�");
								Sleep(3);
								system("cls");
								return;
							}
						}

					}
					// �˳���ѯ
					case 53: 
					{
						system("cls"); return; 
					}
					// ��ʾ
					case -1:
					{
						system("cls");
						printf("\n%5s��ѯ����%s��%s�İ�����£�\n\n"," ", Leave, Arrive);
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
						command = -2;
					}
					// ��������Ѱ����˵�
					case -2:
					{
						while (True)
						{

							printf("\t% s\n\t% s\n\t% s\n\t% s\n\t% s\n\n", "1�����ճ���ʱ������", "2�����յ���ʱ������", "3����������ʱ������", "4����Ʊ", "5���˳���ѯ");
							printf("������Ҫ�����Ĺ��ܣ�����1-5����");
							while (True)
							{
								scanf("%c", &in_command);
								getchar();
								if (in_command >= 49 && in_command <= 53) {command = in_command; break;}
								else{printf("��������ȷ������\n");}
							}
							break;
						}
					}
				} // switch (command)
			} // if (command >= 49 && command <= 53)
			
		} // else if (SR)

	} // while (True)

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
	printf("\n��л��ʹ�ñ�ϵͳ����ȷ���Ƿ�Ҫ�˳�\n");
	printf("y��ȷ���˳�\nn��ȡ��\n");
	printf("���������ָ�");

	char* ensure = (char*)malloc(sizeof(char) * 10);
	scanf("%s", &ensure);
	getchar();
	while (True)
	{
		if (strcmp(ensure, "y") == 0) exit(0);
		else if (strcmp(ensure, "n") == 0) return;
		else printf("��������ȷ����ָ��\n");
	}
}
