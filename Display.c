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
		system("cls");
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

		if (!SR) printf("\t��ѯ������%s��%s�Ŀ��ð��\n%5s��������һ��ָ��\n", Leave, Arrive," ");
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
				break;
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
							system("cls");
							printf("\n����Ϊ������Ϣ��\n");
							printf("\t������ţ�%s\n\t�ֻ��ţ�%s\n\t���α�ţ�%s\n\t����վ��%s\n\t����վ��%s\n\t����ʱ�䣺%02d��%02d\n\t����ʱ�䣺%02d��%02d\n\t��Ʊ������%d\n", \
								OM_NextOrderNum(), \
								Phone,\
								TrainNum, \
								Leave, \
								Arrive, \
								q->LeaveTime[0], q->LeaveTime[1], \
								((q->LeaveTime[0] * 60 + q->LeaveTime[1] + q->ToNextMin) / 60), \
								((q->LeaveTime[0] * 60 + q->LeaveTime[1] + q->ToNextMin) % 60), \
								Ticket);
							printf("\n\tȷ�ϣ�\n\n\ty��ȷ�϶���\n\tn����������\n");
							
							char ensure[5];
							
							// ȷ�ϲ���
							while (True)
							{
								printf("\n\t������ָ��:");
								scanf("%s", &ensure);
								getchar();
								if (strcmp(ensure, "y") == 0) break;
								else if (strcmp(ensure, "n") == 0)
								{
									printf("\n");
									printf("\tȡ���µ�\n");
									printf("\t2��󽫷������˵�\n");
									Sleep(2000);
									return;
								}
								else printf("\t��������ȷ����ָ��\n");

							}
							if (UF_New_F_Order(TrainNum, Leave, Arrive, Ticket, Phone) == OK)
							{
								printf("\n");
								printf("\t�µ��ɹ�\n");
								printf("\t2��󽫷������˵�\n");
								Sleep(2000);
								return;
							}
							else
							{
								printf("\n");
								printf("\t�����洢����\n");
								printf("\t2��󽫷������˵�\n");
								Sleep(2000);
								return;
							}
						}
						// ���� �򲹶���
						else
						{
							// ȷ����Ϣ
							system("cls");
							printf("\n����Ϊ������Ϣ��\n");
							printf("\t������ţ�%s\n\t�ֻ��ţ�%s\n\t���α�ţ�%s\n\t����վ��%s\n\t����վ��%s\n\t����ʱ�䣺%02d��%02d\n\t����ʱ�䣺%02d��%02d\n\t��Ʊ������%d\n", \
								OM_NextOrderNum(),\
								Phone,\
								TrainNum, \
								Leave, \
								Arrive,\
								q->LeaveTime[0], q->LeaveTime[1],\
								((q->LeaveTime[0] * 60 + q->LeaveTime[1] + q->ToNextMin) / 60),\
								((q->LeaveTime[0] * 60 + q->LeaveTime[1] + q->ToNextMin) % 60), \
								Ticket);
							printf("\t��Ʊ�������㣬�Ƿ����򲹣�\n");
							printf("\n\ty�������\n\tn������\n");

							char ensure[5];

							// ȷ�ϲ���
							while (True)
							{
								printf("\n\t������ָ��:");
								scanf("%s", &ensure);
								getchar();
								if (strcmp(ensure, "y") == 0) break;
								else if (strcmp(ensure, "n") == 0)
								{
									system("cls");
									printf("\n");
									printf("\tȡ���µ�\n");
									printf("\t2��󽫷������˵�\n");
									Sleep(2000);
									return;
								}
								else printf("��������ȷ����ָ��\n");

							}
							if (UF_New_W_Order(TrainNum, Leave, Arrive, Ticket, Phone) == OK)
							{
								system("cls");
								printf("\n");
								printf("\t����򲹳ɹ�");
								printf("\n\t2��󽫷������˵�\n");
								Sleep(2000);
								return;
							}
							else
							{
								system("cls");
								printf("\n");
								printf("\t�����������\n");
								printf("\t2��󽫷������˵�\n");
								Sleep(2000);
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
						printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%4s%-5s%4s|%5s\n", \
							" ", " ", "���α��", " ", " ", "������", " ", " ", "�����", " ", " ", "����ʱ��", " ", " ", "����ʱ��", " ", " ", "����ʱ��", " "," ", "��Ʊ", " ", " ");
						while (p)
						{
							printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%3s%02d��%02d%4s|%3s%02d��%02d%4s|%3s%02d��%02d%4s|%4s%4d%5s|%5s\n", \
									" ",\
									" ", p->TrainNum, " ",\
									" ", p->Leave, " ",\
									" ", p->Arrive, " ",\
									" ", p->LeaveTime[0], p->LeaveTime[1], " ", \
									" ", ((p->LeaveTime[0] * 60 + p->LeaveTime[1] + p->ToNextMin) / 60),\
										((p->LeaveTime[0] * 60 + p->LeaveTime[1] + p->ToNextMin) % 60), " ", \
									" ", (p->ToNextMin/60),(p->ToNextMin%60), " ",\
									" ", p->TrainNode->SurplusTicket, " ", \
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
	LeaveTime* LT;
	int Leavetime = 0, Arrivetime = 0, Runtime = 0, flag = 0;

	char ErrorCommand[STRLENGTH];
	
	system("cls");

	while (True)
	{
		while (True)
		{
			printf("\n\t�����붩���ţ�");
			scanf("%s", &OrderNum);
			getchar();
			if (strlen(OrderNum) != 10 )
			{
				system("cls");
				printf("\n");
				printf("\t�����Ÿ�ʽ����ȷ������������");
			}
			else if (strlen(OrderNum) == 10) break;
		}
		system("cls");
		while (True)
		{
			while (True)
			{
				printf("\n");
				printf("\t�����ţ�%s\n", OrderNum);
				printf("\t�����붩���ֻ��ţ�");
				scanf("%s", &ph);
				getchar();
				if (strlen(ph) != 11)
				{
					system("cls");
					printf("\n\t�����ţ�%s\n", OrderNum);
					printf("\t�ֻ��Ÿ�ʽ����ȷ������������11λ�ֻ���\n");
				}
			else if (strlen(ph) == 11) break;
			}

			order = UF_GetOrderInfo(OrderNum);

			if (order)
			{
				if (strcmp(order->OrderKind, "F") == 0)
				{
					if (strcmp(order->OrderNode->phone, ph) != 0)
					{
						printf("\n\t�ֻ��Ų���ȷ��������q�˳���ѯ�������������ַ��������룺");
						scanf("%S", &ErrorCommand);
						getchar();
						if (strcmp(ErrorCommand, "q") == 0) return;
						else;
					}
					else goto SHOW;
				}
				else if (strcmp(order->OrderKind, "W") == 0)
				{

					if (strcmp(order->WaitOrderNode->phone, ph) != 0)
					{
						printf("\n\t�ֻ��Ų���ȷ��������q�˳���ѯ�������������ַ��������룺");
						scanf("%S", &ErrorCommand);
						getchar();
						if (strcmp(ErrorCommand, "q") == 0) return;
						else;
					}
					else goto SHOW;
				}
			}
			else if (!order)
			{
				printf("\n\t�޴˶�����2��󽫷������˵�");
				Sleep(2000);
				return;
			}

		}

	} // while (True)
	
	while (True)
	{
		SHOW:
		// �ö���Ϊ��ʽ����
		if (strcmp(order->OrderKind, "F") == 0)
		{
			LT = S_GetTrainNode(order->OrderNode->TrainNum)->StationLeaveTime->next;
			flag = 0; Runtime = 0;
			while (LT)
			{
				if (strcmp(LT->name, order->OrderNode->Start) == 0) { Leavetime = LT->hour * 60 + LT->min; flag = 1; }
				else if (strcmp(LT->name, order->OrderNode->End) == 0) { flag = 0; break; }
				if (flag == 1) Runtime += LT->ToNextMin;
				LT = LT->next;
			} // while (LT)
					
			Arrivetime = Leavetime + Runtime;

			printf("\t��ѯ���������Ϊ%s����Ϣ���£�\n\n", OrderNum);
			printf("\t�������ͣ���ʽ����\n");
			printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
			" ", " ", "���α��", " ", " ", "�������", " ", " ", "������", " ", " ", "�����", " "," ", "����ʱ��", " "," ", "����ʱ��", " ", " ", "��Ʊ����", " ", " ");

			printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%3s%02d��%02d%4s|%3s%02d��%02d%4s|%4s%4d%5s|%5s\n",\
			" ",\
			" ", order->OrderNode->TrainNum, " ",\
			" ", OrderNum, " ",\
			" ", order->OrderNode->Start, " ", \
			" ", order->OrderNode->End, " ",\
			" ", (Leavetime/60),(Leavetime%60), " ", \
			" ", (Arrivetime/60),(Arrivetime%60), " ", \
			" ", order->OrderNode->TicketNum, " ", \
			" ");

			printf("\n\t������س�������");
			getchar();
			return;
		}
		// �ö���Ϊ�򲹶���
		else if (strcmp(order->OrderKind, "W") == 0)
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
			printf("\t�밴�س�������");
			getchar();
			return;
		}
	} // while(True)
	
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
			system("cls");
			printf("\n\t��������ȷ��11λ�ֻ���\n");
		}
		// �ֻ��Ÿ�ʽ��ȷ
		else
		{
			PN = UF_GetPhoneOrderNode(phone);
			// �޶���
			if (!(PN->OrderList->NextOrder))
			{
				printf("\t�ֻ���%s���޶���\n", phone);
				printf("\n\t2��󽫷������˵�\n");
				Sleep(2000);
				return;
			}
			// ��ʾ����
			else
			{
				printf("\t��ѯ���ֻ���%s�µĶ�����\n", phone);
				printf("%s\n","-------------------------------------------------------------------------------------------------------------------\n");
				printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
						" ", \
					" ", "��������", " ",\
					" ", "���α��", " ",\
					" ", "�������", " ", \
					" ", "������", " ", \
					" ", "�����", " ",\
					" ", "����ʱ��", " ",\
					" ", "����ʱ��", " ", \
					" ", "��Ʊ����", " ",\
					" ");
				p = PN->OrderList->NextOrder;
				while (p)
				{
					strcpy(TrainNum, p->Train->TrainNum);
					strcpy(OrderNum, p->OrderNum);
					strcpy(Leave, p->LeaveStop);
					strcpy(Arrive, p->ArriveStop);
					Ticket = p->TicketAmount;
					LT = p->Train->StationLeaveTime->next;
					flag = 0; Runtime = 0;
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
					
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%3s%02d��%02d%4s|%3s%02d��%02d%4s|%4s%4d%5s|%5s\n",\
						" ",\
						" ", OrderKind, " ",\
						" ", TrainNum, " ",\
						" ", OrderNum, " ",\
						" ", Leave, " ", \
						" ", Arrive, " ",\
						" ", (Leavetime/60),(Leavetime%60), " ", \
						" ", (Arrivetime/60),(Arrivetime%60), " ", \
						" ", Ticket, " ", \
						" ");

					p = p->NextOrder;
				} // while (p)
				break;
			} // else ��ʾ����
		} // else �ֻ��Ÿ�ʽ��ȷ
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
	char inp[STRLENGTH];
	char phone[STRLENGTH];
	char OrderNum[STRLENGTH];
	char ErrorCommand[STRLENGTH];
	char* PhoneInOrder;

	char* TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
	char* Leave = (char*)malloc(sizeof(char) * STRLENGTH);
	char* Arrive = (char*)malloc(sizeof(char) * STRLENGTH);
	char* OrderKind = (char*)malloc(sizeof(char) * STRLENGTH);
	int Ticket;

	OrderSet* order;
	PhoneOrder* PN;
	PhoneOrderList* p;

	int len = 0;

	LeaveTime* LT;
	int Leavetime = 0, Arrivetime = 0, Runtime = 0, flag = 0;

	system("cls");
	printf("\n\t�����붩���Ż�Ʊ�ֻ��ţ�");
	while (True)
	{
		scanf("%s", &inp);
		getchar();
		len = strlen(inp);
		
		// ���붩����
		if (len == 10)
		{
			strcpy(OrderNum, inp);

			while (True)
			{
				printf("\n\t�����ţ�%s\n", OrderNum);
				printf("\t������11λ�ֻ��ţ�������q�˳���ѯ��");
				scanf("%s", phone);
				getchar();
				
				if (strcmp(phone, "q")==0) return;
				else if (strlen(phone) != 11)
				{
					system("cls");
					printf("\n\t��������ȷ��11�ֻ���\n");
				}
				else if (strlen(phone)==11)
				{
					order = UF_GetOrderInfo(OrderNum);
					// �޴˶���
					if (!order)
					{
						system("cls");
						printf("\n\t������ţ�%s\n", OrderNum);
						printf("\n\t�Ҳ����˶������밴�س�������");
						getchar();
						return;
					}
					// ��������
					else
					{
						if (strcmp(order->OrderKind, "F") == 0) PhoneInOrder = order->OrderNode->phone;
						else if (strcmp(order->OrderKind, "W") == 0) PhoneInOrder = order->WaitOrderNode->phone;

						if (strcmp(phone, PhoneInOrder) != 0)
						{
							printf("\n\t�����ֻ�����������ֻ��Ų�ƥ�䣬����q�˳���ѯ�������������ַ����������ֻ��ţ�");
							scanf("%s", &ErrorCommand);
							if (strcmp(ErrorCommand, "q") == 0) return;

						}
						else if (strcmp(phone, PhoneInOrder) == 0)
						{
							// �ö���Ϊ��ʽ����
							if (strcmp(order->OrderKind, "F") == 0)
							{
								LT = S_GetTrainNode(order->OrderNode->TrainNum)->StationLeaveTime->next;
								flag = 0; Runtime = 0;
								while (LT)
								{
									if (strcmp(LT->name, order->OrderNode->Start) == 0) { Leavetime = LT->hour * 60 + LT->min; flag = 1; }
									else if (strcmp(LT->name, order->OrderNode->End) == 0) { flag = 0; break; }
									if (flag == 1) Runtime += LT->ToNextMin;
									LT = LT->next;
								} // while (LT)
					
								Arrivetime = Leavetime + Runtime;

								printf("\t��ѯ���������Ϊ%s����Ϣ���£�\n\n", OrderNum);
								printf("\t�������ͣ���ʽ����\n");
								printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
								" ", " ", "���α��", " ", " ", "�������", " ", " ", "������", " ", " ", "�����", " "," ", "����ʱ��", " "," ", "����ʱ��", " ", " ", "��Ʊ����", " ", " ");

								printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%3s%02d��%02d%4s|%3s%02d��%02d%4s|%4s%4d%5s|%5s\n",\
								" ",\
								" ", order->OrderNode->TrainNum, " ",\
								" ", OrderNum, " ",\
								" ", order->OrderNode->Start, " ", \
								" ", order->OrderNode->End, " ",\
								" ", (Leavetime/60),(Leavetime%60), " ", \
								" ", (Arrivetime/60),(Arrivetime%60), " ", \
								" ", order->OrderNode->TicketNum, " ", \
								" ");

								while (True)
								{
									printf("\n\t�Ƿ�Ҫ��Ʊ��\n\n\ty��ȷ��\n\n\tn��ȡ����Ʊ\n\n\t������ָ��:");
									while (True)
									{
										scanf("%s", &ErrorCommand);
										getchar();
										if (strcmp(ErrorCommand, "y") == 0)
										{
											if (UF_Delete_Order(OrderNum) == OK)
											{
												printf("\n\t��Ʊ�ɹ�\n");
												printf("\n\t2���Ӻ󽫷������˵�");
												Sleep(2000);
												return;
											}
											else
											{
												printf("\n\t�����ڴ������Ʊʧ�ܣ�2���Ӻ󽫷������˵�\n");
												Sleep(2000);
												return;
											}
										}
										else if (strcmp(ErrorCommand, "n") == 0)
										{
											printf("\n\tȡ����Ʊ��2��󷵻����˵�\n");
											Sleep(2000);
											return;
										}
										else
										{
											printf("\n\t��������ȷ��������");

										}


									}
								}
							}
							// �ö���Ϊ�򲹶���
							else if (strcmp(order->OrderKind, "W") == 0)
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
								while (True)
								{
									printf("\n\t�Ƿ�Ҫ��Ʊ��\n\n\ty��ȷ��\n\tn��ȡ����Ʊ");
									while (True)
									{
										printf("\n\t������ָ�");
										scanf("%s", &ErrorCommand);
										getchar();
										if (strcmp(ErrorCommand, "y") == 0)
										{
											if (UF_Delete_Order(OrderNum) == OK)
											{
												printf("\n\t��Ʊ�ɹ�\n");
												printf("\n\t2���Ӻ󽫷������˵�");
												Sleep(2000);
												return;
											}
											else
											{
												printf("\n\t�����ڴ������Ʊʧ�ܣ�2��󽫷������˵�\n");
												Sleep(2000);
												return;
											}
										}
										else if (strcmp(ErrorCommand, "n") == 0)
										{
											printf("\n\tȡ����Ʊ��2��󽫷������˵�\n");
											Sleep(2000);
											return;
										}
										else
										{
											printf("\n\t��������ȷ��������");

										}


									}
								}
							}
						}
					}

				}
			}
		} // if (len == 10)
		// �����ֻ���
		else if (len == 11)
		{
			strcpy(phone, inp);
			PN = UF_GetPhoneOrderNode(phone);
			// �޶���
			if (!(PN->OrderList->NextOrder))
			{
				printf("\n\t�ֻ���%s���޶���\n", phone);
				printf("\n\t2��󽫷������˵�");
				Sleep(2000);
				return;
			}
			// ��ʾ����
			else
			{
				printf("\n\t��ѯ���ֻ���%s�µĶ�����\n", phone);
				printf("%s\n","-------------------------------------------------------------------------------------------------------------------\n");
				printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
						" ", \
					" ", "��������", " ",\
					" ", "���α��", " ",\
					" ", "�������", " ", \
					" ", "������", " ", \
					" ", "�����", " ",\
					" ", "����ʱ��", " ",\
					" ", "����ʱ��", " ", \
					" ", "��Ʊ����", " ",\
					" ");
				p = PN->OrderList->NextOrder;
				while (p)
				{
					strcpy(TrainNum, p->Train->TrainNum);
					strcpy(OrderNum, p->OrderNum);
					strcpy(Leave, p->LeaveStop);
					strcpy(Arrive, p->ArriveStop);
					Ticket = p->TicketAmount;
					LT = p->Train->StationLeaveTime->next;
					flag = 0; Runtime = 0;
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
					
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%3s%02d��%02d%4s|%3s%02d��%02d%4s|%4s%4d%5s|%5s\n",\
						" ",\
						" ", OrderKind, " ",\
						" ", TrainNum, " ",\
						" ", OrderNum, " ",\
						" ", Leave, " ", \
						" ", Arrive, " ",\
						" ", (Leavetime/60),(Leavetime%60), " ", \
						" ", (Arrivetime/60),(Arrivetime%60), " ", \
						" ", Ticket, " ", \
						" ");

					p = p->NextOrder;
				} // while (p)
				
			} // else ��ʾ����
			while (True)
			{
				printf("\n\t�����붩���ţ�");
				scanf("%s", &OrderNum);
				getchar();
				p = PN->OrderList->NextOrder;
				while (p)
				{
					if (strcmp(p->OrderNum, OrderNum) == 0) break;
					else p = p->NextOrder;
				}
				if (!p)
				{
					printf("\n\t�ֻ���%s���޶���%s\n", phone,OrderNum);
					printf("\n\t2��󽫷������˵�");
					Sleep(2000);
					return;
				}
				else if (p)
				{
					system("cls");
					printf("\n");
					printf("\n\t����%s���£�\n",OrderNum);
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
						" ", \
						" ", "��������", " ",\
						" ", "���α��", " ",\
						" ", "�������", " ", \
						" ", "������", " ", \
						" ", "�����", " ",\
						" ", "����ʱ��", " ",\
						" ", "����ʱ��", " ", \
						" ", "��Ʊ����", " ",\
						" ");

					strcpy(TrainNum, p->Train->TrainNum);
					strcpy(OrderNum, p->OrderNum);
					strcpy(Leave, p->LeaveStop);
					strcpy(Arrive, p->ArriveStop);
					Ticket = p->TicketAmount;
					LT = p->Train->StationLeaveTime->next;
					flag = 0; Runtime = 0;
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
					
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%3s%02d��%02d%4s|%3s%02d��%02d%4s|%4s%4d%5s|%5s\n",\
						" ",\
						" ", OrderKind, " ",\
						" ", TrainNum, " ",\
						" ", OrderNum, " ",\
						" ", Leave, " ", \
						" ", Arrive, " ",\
						" ", (Leavetime/60),(Leavetime%60), " ", \
						" ", (Arrivetime/60),(Arrivetime%60), " ", \
						" ", Ticket, " ", \
						" ");

					while (True)
					{
						while (True)
								{
									printf("\n\t�Ƿ�Ҫ��Ʊ��\n\n\ty��ȷ��\n\tn��ȡ����Ʊ\n\n\t������ָ��:");
									while (True)
									{
										scanf("%s", &ErrorCommand);
										getchar();
										if (strcmp(ErrorCommand, "y") == 0)
										{
											if (UF_Delete_Order(OrderNum) == OK)
											{
												printf("\n\t��Ʊ�ɹ�\n");
												printf("\n\t2���Ӻ󽫷������˵�");
												Sleep(2000);
												return;
											}
											else
											{
												printf("\n\t�����ڴ����\n");
												Sleep(2000);
												return;
											}
										}
										else if (strcmp(ErrorCommand, "n") == 0)
										{
											printf("\n\tȡ����Ʊ��2��󷵻����˵�\n");
											Sleep(2000);
											return;
										}
										else
										{
											printf("\n\t��������ȷ��������");

										}


									}
								}
					}

				}

			}			
		} // else if (len == 11)
		// �����ַ��Ƿ�
		else 
		{
			system("cls");
			printf("\n\t��������ȷ�Ķ����Ż��ֻ���\n");
			printf("\n\t�����붩���Ż�Ʊ�ֻ��ţ�");
		}
	} // while (True)


	return;
}

// �˳�ϵͳ
// Freeze
void DP_ExitSys()
{
	printf("\n\t��л��ʹ�ñ�ϵͳ����ȷ���Ƿ�Ҫ�˳�\n");
	printf("\n\ty��ȷ���˳�\n\tn��ȡ��\n");
	printf("\n\t���������ָ�");

	char ensure[5];
	while (True)
	{
		scanf("%s", &ensure);
		getchar();
		if (strcmp(ensure, "y") == 0) exit(0);
		else if (strcmp(ensure, "n") == 0) { system("cls"); return; }
		else printf("\n\t��������ȷ����ָ�");
	}
}

