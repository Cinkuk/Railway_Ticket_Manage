// ���ļ���ŵĺ���������ʾ��Ϣ
// ���ļ��ĺ�������'DP_'��ͷ
//
// Test Status: Working
// Code Status: Working

#include "F_Lib.h"
#include "V_Lib.h"

// ��Ʊ����
// 
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
		printf("\n");
		printf("\t����������أ�");
		scanf("%s", &Leave);
		getchar();
		printf("\t������Ŀ�ĵأ�");
		scanf("%s", &Arrive);
		getchar();

		// ��ȡ��ѯ���
		SR = UF_SearchStop(Leave, Arrive);

		// ��������ʾ��ѯ���
		system("cls");
		printf("\n\n");

		if (!SR) printf("\t%5s��ѯ������%s��%s�Ŀ��ð��\n%5s��������һ��ָ��\n", " ", Leave, Arrive," ");
		else if (SR)
		{
			// Ĭ���Գ���ʱ������
			p = UF_LeaveTimeSort(SR);
			command = 33;
		}
		
		// ���β�ѯ�޿��ð�� 
		if (!SR)
		{
			printf("\t%s\n\t%s\n\n", "1�����²�ѯ", "2���˳���ѯ");
			printf("\t������Ҫ�����Ĺ��ܣ�����1-2����");
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
				else printf("\t��������ȷ������\n");
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
						
						// ��ʾ���
						command = 33;
						break;
					}
					// ����ʱ������ 
					case 50: 
					{
						system("cls");
						p = UF_RunTimeSort(SR);

						// ��ʾ���
						command = 33;
						break;
					}
					// ����ʱ������
					case 51: 
					{
						system("cls");
						p = UF_ArriveTimeSort(SR);

						// ��ʾ���
						command = 33;
						break;
					}
					// ��Ʊ
					case 52:
					{ 
						// ���복�κ�
						while (True)
						{
							printf("\t�����복�κţ���ĸ��Ҫ��д����");
							scanf("%s", &TrainNum);
							getchar();
							q = SR->NextResult;
							while (q)
							{
								if (strcmp(q->TrainNum, TrainNum) == 0) break;
								else q = q->NextResult;
							}
							// ���κŲ�����
							if (!q) printf("\t��������ȷ���κ�\n");
							else if (q) break;
							
						}
						
						// �����ֻ���
						while (True)
						{
							printf("\t�������ֻ��ţ�");
							scanf("%s", &Phone);
							getchar();
							if (strlen(Phone) == 11) break;
							else printf("\t��������ȷ��11λ�ֻ���\n");
						}
						
						// ��Ʊ����
						while (True)
						{
							printf("\t�����붩��������");
							scanf("%d", &Ticket);
							getchar();
							if (Ticket > 0)break;
							else printf("\t��������ֵΪ����Ʊ��\n");
						}

						// �ж���Ʊ�Ƿ���� 
						// ȷ�϶�����Ϣ
						// ���� ��ʽ����
						if (Ticket < q->TrainNode->SurplusTicket)
						{
							// ȷ����Ϣ
							printf("\t����Ϊ������Ϣ��\n");
							printf("\t���α�ţ�%s\n����վ��%s\n����վ��%s\n����ʱ�䣺%02d��%02d\n����ʱ�䣺%02d��%02d\n��Ʊ������%d\n", \
								TrainNum, \
								Leave, \
								Arrive, \
								q->LeaveTime[0], q->LeaveTime[1], \
								q->ArriveTime[0], q->ArriveTime[1], \
								Ticket);
							printf("\n\tȷ�ϣ�\n\ty��ȷ�϶���\n\tn����������\n");
							
							char ensure[5];
							
							// ȷ�ϲ���
							while (True)
							{
								scanf("%s", &ensure);
								getchar();
								if (strcmp(ensure, "y") == 0) break;
								else if (strcmp(ensure, "n") == 0)
								{
									system("cls");
									printf("\n");
									printf("\tȡ���µ�\n");
									printf("\t����󽫷������˵�\n");
									Sleep(3);
									system("cls");
									return;
								}
								else printf("\t��������ȷ����ָ��\n");

							}
							if (UF_New_F_Order(TrainNum, Leave, Arrive, Ticket, Phone) == OK)
							{
								system("cls");
								printf("\n");
								printf("\t�µ��ɹ�\n");
								printf("\t����󽫷������˵�\n");
								Sleep(3);
								system("cls");
								return;
							}
							else
							{
								system("cls");
								printf("\n");
								printf("\t�����洢����\n");
								printf("\t����󽫷������˵�\n");
								Sleep(3);
								system("cls");
								return;
							}
						}
						// ���� �򲹶���
						else
						{
							// ȷ����Ϣ
							printf("\t����Ϊ������Ϣ��\n");
							printf("\t���α�ţ�%s\n����վ��%s\n����վ��%s\n����ʱ�䣺%02d��%02d\n����ʱ�䣺%02d��02d\n��Ʊ������%d\n", \
								TrainNum, \
								Leave, \
								Arrive,\
								q->LeaveTime[0], q->LeaveTime[1],\
								q->ArriveTime[0], q->ArriveTime[1], \
								Ticket);
							printf("\t��Ʊ�������㣬�Ƿ����򲹣�\n");
							printf("\n\ty�������\n\tn������\n");

							char ensure[5];

							// ȷ�ϲ���
							while (True)
							{
								scanf("%s", &ensure);
								getchar();
								if (strcmp(ensure, "y") == 0) break;
								else if (strcmp(ensure, "n") == 0)
								{
									system("cls");
									printf("\n");
									printf("\tȡ���µ�\n");
									printf("\t����󽫷������˵�\n");
									Sleep(3);
									system("cls");
									return;
								}
								else printf("��������ȷ����ָ��\n");

							}
							if (UF_New_W_Order(TrainNum, Leave, Arrive, Ticket, Phone) == OK)
							{
								system("cls");
								printf("\n");
								printf("\t����򲹳ɹ�");
								printf("\t����󽫷������˵�\n");
								Sleep(3);
								system("cls");
								return;
							}
							else
							{
								system("cls");
								printf("\n");
								printf("\t�����������\n");
								printf("\t����󽫷������˵�\n");
								Sleep(3);
								system("cls");
								return;
							}
						}
						break;

					} // case52
					// �˳���ѯ
					case 53: 
					{
						system("cls"); return; 
						break;
					}
					// ��ʾ
					case 33:
					{
						p = p->NextResult;
						system("cls");
						printf("\n\t%5s��ѯ����%s��%s�İ�����£�\n\n"," ", Leave, Arrive);
						printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n", \
							" ", " ", "���α��", " ", " ", "������", " ", " ", "�����", " ", " ", "����ʱ��", " ", " ", "����ʱ��", " ", " ", "����ʱ��", " ", " ");
						while (p)
						{
							printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%3s%02d��%02d%4s|%3s%02d��%02d%4s|%3s%02d��%02d%s|%5s\n", \
									" ",\
									" ", p->TrainNum, " ",\
									" ", p->Leave, " ",\
									" ", p->Arrive, " ",\
									" ", p->LeaveTime[0], p->LeaveTime[1], " ", \
									" ", ((p->LeaveTime[0] * 60 + p->LeaveTime[1] + p->ToNextMin) / 60),\
										((p->LeaveTime[0] * 60 + p->LeaveTime[1] + p->ToNextMin) % 60), " ", \
									" ", (p->ToNextMin/60),(p->ToNextMin%60), " ",\
									" ");
							p = p->NextResult;

						}
						// ������������˵�
						printf("\n%s\n", "------------------------------------------------------------------------------------------------------------");
						printf("\n\t��������һ��ָ��:\n");
						command = 34;
						break;
					}
					// ��������Ѱ����˵�
					case 34:
					{
						int flag = 0;
						while (True)
						{
							flag = 0;
							printf("\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\n", "1�����ճ���ʱ������", "2�����յ���ʱ������", "3����������ʱ������", "4����Ʊ", "5���˳���ѯ");
							printf("������Ҫ�����Ĺ��ܣ�����1-5����");
							while (flag==0)
							{
								scanf("%c", &in_command);
								getchar();
								if (in_command >= 49 && in_command <= 53)
								{
									switch (in_command)
									{
									case 49: {command = 49; flag = 1; break; }
									case 50: {command = 51; flag = 1; break; }
									case 51: {command = 50; flag = 1; break; }
									case 52: {command = 52; flag = 1; break; }
									case 53: {command = 53; flag = 1; break; }
									}
									break;
								} // if (in_command >= 49 && in_command <= 53)
								else{printf("��������ȷ������\n");printf("������Ҫ�����Ĺ��ܣ�����1-5����");}
							} // while (True && flag==0)
							break;
						} // while (True)
						break;
					} // case -2
				} // switch (command)
			} // if (command >= 49 && command <= 53)
			
		} // else if (SR)

	} // while (True)

	return;
}

// ���붩���Ų�ѯ����
// 
void DP_CheckOrder()
{

	char OrderNum[STRLENGTH];
	char ph[STRLENGTH];
	OrderSet* order;

	while (True)
	{
		while (True)
		{
			printf("\n\t�����붩���ţ�");
			scanf("%s", &OrderNum);
			getchar();
			if (strlen(OrderNum) != 10 )
			{
				printf("\t�����Ÿ�ʽ����ȷ������������\n");
				continue;
			}
			else if (strlen(OrderNum) == 10) break;
		}
		while (True)
		{
			printf("\t�������ֻ��ţ�");
			scanf("%s", &ph);
			getchar();
			if (strlen(ph) != 11)
			{
				printf("\t�ֻ��Ÿ�ʽ����ȷ������������11λ�ֻ���\n");
				continue;
			}
			else if (strlen(ph) == 11) break;

		}

		order = UF_GetOrderInfo(OrderNum);

		if (!order)
		{
			printf("\t�޴˶����ţ�����������\n");
			Sleep(1);
			system("cls");
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
					printf("\t��ѯ���������Ϊ%s����Ϣ���£�\n\n", OrderNum);
					printf("\t�������ͣ���ʽ����\n");
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%5s\n",\
					" ", " ", "���α��", " ", " ", "�������", " ", " ", "������", " ", " ", "�����", " ", " ", "��Ʊ����", " ", " ");
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%4s%4d%5s|%8s\n",\
						" ",\
						" ", order->OrderNode->TrainNum, " ",\
						" ", OrderNum,  " ",\
						" ", order->OrderNode->Start, " ",\
						" ", order->OrderNode->End, " ",\
						" ", order->OrderNode->TicketNum, " ",\
						" ");
				}
				else
				{
					printf("\t�ֻ��Ų���ȷ�����������룬��q�˳���ѯ��");
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
					printf("\t��ѯ���������Ϊ%s����Ϣ���£�\n\n", OrderNum);
					printf("\t�������ͣ��򲹶���\n");
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%5s\n",\
					" ", " ", "���α��", " ", " ", "�������", " ", " ", "������", " ", " ", "�����", " ", " ", "��Ʊ����", " ", " ");
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%4s%4d%5s|%5s\n",\
						" ", \
						" ", order->WaitOrderNode->TrainNum, " ",\
						" ", OrderNum,  " ",\
						" ", order->WaitOrderNode->Start, " ",\
						" ", order->WaitOrderNode->End, " ",\
						" ", order->WaitOrderNode->TicketNum, " ",\
						" ");
				}
				else
				{
					printf("\t�ֻ��Ų���ȷ�����������룬��q�˳���ѯ��");
					scanf("%s", ph);
					getchar();
					if (strcmp(ph, "q") == 0) return;
				}
			}
		}
	}
	
	return;
}

// �����ֻ��Ų�ѯ����
// 
void DP_CheckPhoneOrder()
{
	char phone[20];
	char* OrderKind = (char*)malloc(sizeof(char) * STRLENGTH);
	PhoneOrder* PN;
	PhoneOrderList* p;
	LeaveTime* LT;

	char* TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
	char* OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);
	char* Leave = (char*)malloc(sizeof(char) * STRLENGTH);
	char* Arrive = (char*)malloc(sizeof(char) * STRLENGTH);
	int Leavetime=0, Arrivetime=0, Runtime=0, Ticket=0, flag=0;

	system("cls");

	while (True)
	{
		printf("\n\t������11λ�ֻ��ţ�");
		scanf("%s", &phone);
		getchar();
		
		// �ֻ��Ÿ�ʽ����ȷ
		if (strlen(phone) != 11)
		{
			printf("\t����������11λ�ֻ��ţ�");
		}
		// �ֻ��Ÿ�ʽ��ȷ
		else
		{
			PN = UF_GetPhoneOrderNode(phone);
			// �޶���
			if (!(PN->OrderList->NextOrder))
			{
				printf("\t�ֻ���%s���޶���\n", phone);
			}
			// ��ʾ����
			else
			{
				printf("\t��ѯ���ֻ���%s�µĶ�����\n", phone);
				printf("%s\n","-------------------------------------------------------------------------------------------------------------------\n");
				printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
						" ", " ", "���α��", " ", " ", "�������", " ", " ", "������", " ", " ", "�����", " "," ", "����ʱ��", " "," ", "����ʱ��", " ", " ", "��Ʊ����", " ", " ");
				p = PN->OrderList->NextOrder;
				while (p)
				{
					strcpy(TrainNum, p->Train->TrainNum);
					strcpy(OrderNum, p->OrderNum);
					strcpy(Leave, p->LeaveStop);
					strcpy(Arrive, p->ArriveStop);
					Ticket = p->TicketAmount;
					LT = p->Train->StationLeaveTime->next;
					Ticket = 0; flag = 0; Runtime = 0;
					while (LT)
					{
						if (strcmp(LT->name, Leave) == 0) { Leavetime = LT->hour * 60 + LT->min; flag = 1; }
						else if (strcmp(LT->name, Arrive) == 0) { flag = 0; break; }
						if (flag == 1) Runtime += LT->ToNextMin;
						LT = LT->next;
					} // while (LT)
					
					Arrivetime = Leavetime + Runtime;

					if (strcmp(p->OrderStatus, "W") == 0) strcpy(OrderKind, "�򲹶���");
					else if (strcmp(p->OrderStatus, "F") == 0) strcpy(OrderKind, "��ʽ����");
					
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%3s%02d��%02d%4s|%3s%02d��%02d%4s|%4s%4d%5s|%5s\n",\
						" ",\
						" ", TrainNum, " ",\
						" ", OrderNum, " ",\
						" ", Leave, " ", \
						" ", Arrive, " ",\
						" ", (Leavetime/60),(Leavetime%60), " ", \
						" ", (Arrivetime/60),(Arrivetime%60), " ", \
						" ", Ticket, " ", \
						" ");
				} // while (p)
				break;
			} // else ��ʾ����
		} // else �ֻ��Ÿ�ʽ����ȷ
	} // while (True)
	while (True)
	{
		printf("\n\n\t�밴�س����������˵�\n");
		getchar();
		break;
	}
	return;
}

// ��Ʊ
// 
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

// �˳�ϵͳ
// Freeze
void DP_ExitSys()
{
	printf("\n��л��ʹ�ñ�ϵͳ����ȷ���Ƿ�Ҫ�˳�\n");
	printf("y��ȷ���˳�\nn��ȡ��\n");
	printf("���������ָ�");

	char ensure[5];
	while (True)
	{
		scanf("%s", &ensure);
		getchar();
		if (strcmp(ensure, "y") == 0) exit(0);
		else if (strcmp(ensure, "n") == 0) { system("cls"); return; }
		else printf("��������ȷ����ָ�");
	}
}
