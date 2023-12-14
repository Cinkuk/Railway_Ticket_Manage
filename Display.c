// 本文件存放的函数用于显示信息
// 本文件的函数名以'DP_'开头
//
// Test Status: Working
// Code Status: Working

#include "F_Lib.h"
#include "V_Lib.h"

// 订票服务
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
		printf("\t请输入出发地：");
		scanf("%s", &Leave);
		getchar();
		printf("\t请输入目的地：");
		scanf("%s", &Arrive);
		getchar();

		// 获取查询结果
		SR = UF_SearchStop(Leave, Arrive);

		// 清屏，显示查询结果
		system("cls");
		printf("\n\n");

		if (!SR) printf("\t查询不到从%s到%s的可用班次\n%5s请输入下一步指令\n", Leave, Arrive," ");
		else if (SR)
		{
			// 默认以出发时间排序
			p = UF_LeaveTimeSort(SR);
			command = 33;
		}
		
		// 本次查询无可用班次 
		if (!SR)
		{
			printf("\t%s\n\t%s\n\n", "1、重新查询", "2、退出查询");
			printf("\t请输入要操作的功能（数字1-2）：");
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
				else printf("\t请输入正确操作数\n");
				break;
			}
		}
		// 本次查询有可用班次
		else if (SR)
		{

			while(True) 
			{
				switch (command)
				{
					// 出发时间排序
					case 49: 
					{
						system("cls");
						p = UF_LeaveTimeSort(SR);
						
						// 显示结果
						command = 33;
						break;
					}
					// 运行时间排序 
					case 50: 
					{
						system("cls");
						p = UF_RunTimeSort(SR);

						// 显示结果
						command = 33;
						break;
					}
					// 到达时间排序
					case 51: 
					{
						system("cls");
						p = UF_ArriveTimeSort(SR);

						// 显示结果
						command = 33;
						break;
					}
					// 订票
					case 52:
					{ 
						// 输入车次号
						while (True)
						{
							printf("\t请输入车次号（字母需要大写）：");
							scanf("%s", &TrainNum);
							getchar();
							q = SR->NextResult;
							while (q)
							{
								if (strcmp(q->TrainNum, TrainNum) == 0) break;
								else q = q->NextResult;
							}
							// 车次号不存在
							if (!q) printf("\t请输入正确车次号\n");
							else if (q) break;
							
						}
						
						// 输入手机号
						while (True)
						{
							printf("\t请输入手机号：");
							scanf("%s", &Phone);
							getchar();
							if (strlen(Phone) == 11) break;
							else printf("\t请输入正确的11位手机号\n");
						}
						
						// 订票张数
						while (True)
						{
							printf("\t请输入订购张数：");
							scanf("%d", &Ticket);
							getchar();
							if (Ticket > 0)break;
							else printf("\t请输入数值为正的票数\n");
						}

						// 判断余票是否充足 
						// 确认订单信息
						// 充足 正式订单
						if (Ticket < q->TrainNode->SurplusTicket)
						{
							// 确认信息
							system("cls");
							printf("\n以下为订单信息：\n");
							printf("\t订单编号：%s\n\t手机号：%s\n\t车次编号：%s\n\t出发站：%s\n\t到达站：%s\n\t出发时间：%02d：%02d\n\t到达时间：%02d：%02d\n\t购票张数：%d\n", \
								OM_NextOrderNum(), \
								Phone,\
								TrainNum, \
								Leave, \
								Arrive, \
								q->LeaveTime[0], q->LeaveTime[1], \
								((q->LeaveTime[0] * 60 + q->LeaveTime[1] + q->ToNextMin) / 60), \
								((q->LeaveTime[0] * 60 + q->LeaveTime[1] + q->ToNextMin) % 60), \
								Ticket);
							printf("\n\t确认？\n\n\ty：确认订单\n\tn：放弃订单\n");
							
							char ensure[5];
							
							// 确认操作
							while (True)
							{
								printf("\n\t请输入指令:");
								scanf("%s", &ensure);
								getchar();
								if (strcmp(ensure, "y") == 0) break;
								else if (strcmp(ensure, "n") == 0)
								{
									printf("\n");
									printf("\t取消下单\n");
									printf("\t2秒后将返回主菜单\n");
									Sleep(2000);
									return;
								}
								else printf("\t请输入正确操作指令\n");

							}
							if (UF_New_F_Order(TrainNum, Leave, Arrive, Ticket, Phone) == OK)
							{
								printf("\n");
								printf("\t下单成功\n");
								printf("\t2秒后将返回主菜单\n");
								Sleep(2000);
								return;
							}
							else
							{
								printf("\n");
								printf("\t发生存储错误\n");
								printf("\t2秒后将返回主菜单\n");
								Sleep(2000);
								return;
							}
						}
						// 不足 候补订单
						else
						{
							// 确认信息
							system("cls");
							printf("\n以下为订单信息：\n");
							printf("\t订单编号：%s\n\t手机号：%s\n\t车次编号：%s\n\t出发站：%s\n\t到达站：%s\n\t出发时间：%02d：%02d\n\t到达时间：%02d：%02d\n\t购票张数：%d\n", \
								OM_NextOrderNum(),\
								Phone,\
								TrainNum, \
								Leave, \
								Arrive,\
								q->LeaveTime[0], q->LeaveTime[1],\
								((q->LeaveTime[0] * 60 + q->LeaveTime[1] + q->ToNextMin) / 60),\
								((q->LeaveTime[0] * 60 + q->LeaveTime[1] + q->ToNextMin) % 60), \
								Ticket);
							printf("\t余票数量不足，是否进入候补？\n");
							printf("\n\ty：进入候补\n\tn：放弃\n");

							char ensure[5];

							// 确认操作
							while (True)
							{
								printf("\n\t请输入指令:");
								scanf("%s", &ensure);
								getchar();
								if (strcmp(ensure, "y") == 0) break;
								else if (strcmp(ensure, "n") == 0)
								{
									system("cls");
									printf("\n");
									printf("\t取消下单\n");
									printf("\t2秒后将返回主菜单\n");
									Sleep(2000);
									return;
								}
								else printf("请输入正确操作指令\n");

							}
							if (UF_New_W_Order(TrainNum, Leave, Arrive, Ticket, Phone) == OK)
							{
								system("cls");
								printf("\n");
								printf("\t加入候补成功");
								printf("\n\t2秒后将返回主菜单\n");
								Sleep(2000);
								return;
							}
							else
							{
								system("cls");
								printf("\n");
								printf("\t发生储存错误\n");
								printf("\t2秒后将返回主菜单\n");
								Sleep(2000);
								return;
							}
						}
						break;

					} // case52
					// 退出查询
					case 53: 
					{
						system("cls"); return; 
						break;
					}
					// 显示
					case 33:
					{
						p = p->NextResult;
						system("cls");
						printf("\n\t%5s查询到从%s到%s的班次如下：\n\n"," ", Leave, Arrive);
						printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%4s%-5s%4s|%5s\n", \
							" ", " ", "车次编号", " ", " ", "出发地", " ", " ", "到达地", " ", " ", "出发时间", " ", " ", "到达时间", " ", " ", "运行时间", " "," ", "余票", " ", " ");
						while (p)
						{
							printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%3s%02d：%02d%4s|%3s%02d：%02d%4s|%3s%02d：%02d%4s|%4s%4d%5s|%5s\n", \
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
						// 进入后续操作菜单
						printf("\n%s\n", "------------------------------------------------------------------------------------------------------------");
						printf("\n\t请输入下一步指令:\n");
						command = 34;
						break;
					}
					// 进入有搜寻结果菜单
					case 34:
					{
						int flag = 0;
						while (True)
						{
							flag = 0;
							printf("\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\n", "1、按照出发时间排序", "2、按照到达时间排序", "3、按照运行时间排序", "4、订票", "5、退出查询");
							printf("请输入要操作的功能（数字1-5）：");
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
								else{printf("请输入正确操作数\n");printf("请输入要操作的功能（数字1-5）：");}
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

// 输入订单号查询订单
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
			printf("\n\t请输入订单号：");
			scanf("%s", &OrderNum);
			getchar();
			if (strlen(OrderNum) != 10 )
			{
				system("cls");
				printf("\n");
				printf("\t订单号格式不正确，请重新输入");
			}
			else if (strlen(OrderNum) == 10) break;
		}
		system("cls");
		while (True)
		{
			while (True)
			{
				printf("\n");
				printf("\t订单号：%s\n", OrderNum);
				printf("\t请输入订单手机号：");
				scanf("%s", &ph);
				getchar();
				if (strlen(ph) != 11)
				{
					system("cls");
					printf("\n\t订单号：%s\n", OrderNum);
					printf("\t手机号格式不正确，请重新输入11位手机号\n");
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
						printf("\n\t手机号不正确，请输入q退出查询，或输入其他字符重新输入：");
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
						printf("\n\t手机号不正确，请输入q退出查询，或输入其他字符重新输入：");
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
				printf("\n\t无此订单，2秒后将返回主菜单");
				Sleep(2000);
				return;
			}

		}

	} // while (True)
	
	while (True)
	{
		SHOW:
		// 该订单为正式订单
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

			printf("\t查询到订单编号为%s的信息如下：\n\n", OrderNum);
			printf("\t订单类型：正式订单\n");
			printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
			" ", " ", "车次编号", " ", " ", "订单编号", " ", " ", "出发地", " ", " ", "到达地", " "," ", "出发时间", " "," ", "到达时间", " ", " ", "购票张数", " ", " ");

			printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%3s%02d：%02d%4s|%3s%02d：%02d%4s|%4s%4d%5s|%5s\n",\
			" ",\
			" ", order->OrderNode->TrainNum, " ",\
			" ", OrderNum, " ",\
			" ", order->OrderNode->Start, " ", \
			" ", order->OrderNode->End, " ",\
			" ", (Leavetime/60),(Leavetime%60), " ", \
			" ", (Arrivetime/60),(Arrivetime%60), " ", \
			" ", order->OrderNode->TicketNum, " ", \
			" ");

			printf("\n\t请输入回车键返回");
			getchar();
			return;
		}
		// 该订单为候补订单
		else if (strcmp(order->OrderKind, "W") == 0)
		{
			
			printf("\t查询到订单编号为%s的信息如下：\n\n", OrderNum);
			printf("\t订单类型：候补订单\n");
			printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%5s\n",\
			" ", " ", "车次编号", " ", " ", "订单编号", " ", " ", "出发地", " ", " ", "到达地", " ", " ", "购票张数", " ", " ");
			printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%4s%4d%5s|%5s\n",\
				" ", \
				" ", order->WaitOrderNode->TrainNum, " ",\
				" ", OrderNum,  " ",\
				" ", order->WaitOrderNode->Start, " ",\
				" ", order->WaitOrderNode->End, " ",\
				" ", order->WaitOrderNode->TicketNum, " ",\
				" ");
			printf("\t请按回车键返回");
			getchar();
			return;
		}
	} // while(True)
	
	return;
}

// 输入手机号查询订单
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
		printf("\n\t请输入11位手机号：");
		scanf("%s", &phone);
		getchar();
		
		// 手机号格式不正确
		if (strlen(phone) != 11)
		{
			system("cls");
			printf("\n\t请输入正确的11位手机号\n");
		}
		// 手机号格式正确
		else
		{
			PN = UF_GetPhoneOrderNode(phone);
			// 无订单
			if (!(PN->OrderList->NextOrder))
			{
				printf("\t手机号%s下无订单\n", phone);
				printf("\n\t2秒后将返回主菜单\n");
				Sleep(2000);
				return;
			}
			// 显示订单
			else
			{
				printf("\t查询到手机号%s下的订单：\n", phone);
				printf("%s\n","-------------------------------------------------------------------------------------------------------------------\n");
				printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
						" ", \
					" ", "订单类型", " ",\
					" ", "车次编号", " ",\
					" ", "订单编号", " ", \
					" ", "出发地", " ", \
					" ", "到达地", " ",\
					" ", "出发时间", " ",\
					" ", "到达时间", " ", \
					" ", "购票张数", " ",\
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

					if (strcmp(p->OrderStatus, "W") == 0) strcpy(OrderKind, "候补订单");
					else if (strcmp(p->OrderStatus, "F") == 0) strcpy(OrderKind, "正式订单");
					
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%3s%02d：%02d%4s|%3s%02d：%02d%4s|%4s%4d%5s|%5s\n",\
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
			} // else 显示订单
		} // else 手机号格式正确
	} // while (True)
	while (True)
	{
		printf("\n\n\t请按回车键返回主菜单\n");
		getchar();
		break;
	}
	return;
}

// 退票
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
	printf("\n\t请输入订单号或订票手机号：");
	while (True)
	{
		scanf("%s", &inp);
		getchar();
		len = strlen(inp);
		
		// 输入订单号
		if (len == 10)
		{
			strcpy(OrderNum, inp);

			while (True)
			{
				printf("\n\t订单号：%s\n", OrderNum);
				printf("\t请输入11位手机号，或输入q退出查询：");
				scanf("%s", phone);
				getchar();
				
				if (strcmp(phone, "q")==0) return;
				else if (strlen(phone) != 11)
				{
					system("cls");
					printf("\n\t请输入正确的11手机号\n");
				}
				else if (strlen(phone)==11)
				{
					order = UF_GetOrderInfo(OrderNum);
					// 无此订单
					if (!order)
					{
						system("cls");
						printf("\n\t订单编号：%s\n", OrderNum);
						printf("\n\t找不到此订单，请按回车键返回");
						getchar();
						return;
					}
					// 订单存在
					else
					{
						if (strcmp(order->OrderKind, "F") == 0) PhoneInOrder = order->OrderNode->phone;
						else if (strcmp(order->OrderKind, "W") == 0) PhoneInOrder = order->WaitOrderNode->phone;

						if (strcmp(phone, PhoneInOrder) != 0)
						{
							printf("\n\t订单手机号与输入的手机号不匹配，输入q退出查询，或输入其他字符重新输入手机号：");
							scanf("%s", &ErrorCommand);
							if (strcmp(ErrorCommand, "q") == 0) return;

						}
						else if (strcmp(phone, PhoneInOrder) == 0)
						{
							// 该订单为正式订单
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

								printf("\t查询到订单编号为%s的信息如下：\n\n", OrderNum);
								printf("\t订单类型：正式订单\n");
								printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
								" ", " ", "车次编号", " ", " ", "订单编号", " ", " ", "出发地", " ", " ", "到达地", " "," ", "出发时间", " "," ", "到达时间", " ", " ", "购票张数", " ", " ");

								printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%3s%02d：%02d%4s|%3s%02d：%02d%4s|%4s%4d%5s|%5s\n",\
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
									printf("\n\t是否要退票？\n\n\ty：确定\n\n\tn：取消退票\n\n\t请输入指令:");
									while (True)
									{
										scanf("%s", &ErrorCommand);
										getchar();
										if (strcmp(ErrorCommand, "y") == 0)
										{
											if (UF_Delete_Order(OrderNum) == OK)
											{
												printf("\n\t退票成功\n");
												printf("\n\t2秒钟后将返回主菜单");
												Sleep(2000);
												return;
											}
											else
											{
												printf("\n\t发生内存错误，退票失败，2秒钟后将返回主菜单\n");
												Sleep(2000);
												return;
											}
										}
										else if (strcmp(ErrorCommand, "n") == 0)
										{
											printf("\n\t取消退票，2秒后返回主菜单\n");
											Sleep(2000);
											return;
										}
										else
										{
											printf("\n\t请输入正确操作数：");

										}


									}
								}
							}
							// 该订单为候补订单
							else if (strcmp(order->OrderKind, "W") == 0)
							{
			
								printf("\t查询到订单编号为%s的信息如下：\n\n", OrderNum);
								printf("\t订单类型：候补订单\n");
								printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%5s\n",\
								" ", " ", "车次编号", " ", " ", "订单编号", " ", " ", "出发地", " ", " ", "到达地", " ", " ", "购票张数", " ", " ");
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
									printf("\n\t是否要退票？\n\n\ty：确定\n\tn：取消退票");
									while (True)
									{
										printf("\n\t请输入指令：");
										scanf("%s", &ErrorCommand);
										getchar();
										if (strcmp(ErrorCommand, "y") == 0)
										{
											if (UF_Delete_Order(OrderNum) == OK)
											{
												printf("\n\t退票成功\n");
												printf("\n\t2秒钟后将返回主菜单");
												Sleep(2000);
												return;
											}
											else
											{
												printf("\n\t发生内存错误，退票失败，2秒后将返回主菜单\n");
												Sleep(2000);
												return;
											}
										}
										else if (strcmp(ErrorCommand, "n") == 0)
										{
											printf("\n\t取消退票，2秒后将返回主菜单\n");
											Sleep(2000);
											return;
										}
										else
										{
											printf("\n\t请输入正确操作数：");

										}


									}
								}
							}
						}
					}

				}
			}
		} // if (len == 10)
		// 输入手机号
		else if (len == 11)
		{
			strcpy(phone, inp);
			PN = UF_GetPhoneOrderNode(phone);
			// 无订单
			if (!(PN->OrderList->NextOrder))
			{
				printf("\n\t手机号%s下无订单\n", phone);
				printf("\n\t2秒后将返回主菜单");
				Sleep(2000);
				return;
			}
			// 显示订单
			else
			{
				printf("\n\t查询到手机号%s下的订单：\n", phone);
				printf("%s\n","-------------------------------------------------------------------------------------------------------------------\n");
				printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
						" ", \
					" ", "订单类型", " ",\
					" ", "车次编号", " ",\
					" ", "订单编号", " ", \
					" ", "出发地", " ", \
					" ", "到达地", " ",\
					" ", "出发时间", " ",\
					" ", "到达时间", " ", \
					" ", "购票张数", " ",\
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

					if (strcmp(p->OrderStatus, "W") == 0) strcpy(OrderKind, "候补订单");
					else if (strcmp(p->OrderStatus, "F") == 0) strcpy(OrderKind, "正式订单");
					
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%3s%02d：%02d%4s|%3s%02d：%02d%4s|%4s%4d%5s|%5s\n",\
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
				
			} // else 显示订单
			while (True)
			{
				printf("\n\t请输入订单号：");
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
					printf("\n\t手机号%s下无订单%s\n", phone,OrderNum);
					printf("\n\t2秒后将返回主菜单");
					Sleep(2000);
					return;
				}
				else if (p)
				{
					system("cls");
					printf("\n");
					printf("\n\t订单%s如下：\n",OrderNum);
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
						" ", \
						" ", "订单类型", " ",\
						" ", "车次编号", " ",\
						" ", "订单编号", " ", \
						" ", "出发地", " ", \
						" ", "到达地", " ",\
						" ", "出发时间", " ",\
						" ", "到达时间", " ", \
						" ", "购票张数", " ",\
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

					if (strcmp(p->OrderStatus, "W") == 0) strcpy(OrderKind, "候补订单");
					else if (strcmp(p->OrderStatus, "F") == 0) strcpy(OrderKind, "正式订单");
					
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%3s%02d：%02d%4s|%3s%02d：%02d%4s|%4s%4d%5s|%5s\n",\
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
									printf("\n\t是否要退票？\n\n\ty：确定\n\tn：取消退票\n\n\t请输入指令:");
									while (True)
									{
										scanf("%s", &ErrorCommand);
										getchar();
										if (strcmp(ErrorCommand, "y") == 0)
										{
											if (UF_Delete_Order(OrderNum) == OK)
											{
												printf("\n\t退票成功\n");
												printf("\n\t2秒钟后将返回主菜单");
												Sleep(2000);
												return;
											}
											else
											{
												printf("\n\t发生内存错误\n");
												Sleep(2000);
												return;
											}
										}
										else if (strcmp(ErrorCommand, "n") == 0)
										{
											printf("\n\t取消退票，2秒后返回主菜单\n");
											Sleep(2000);
											return;
										}
										else
										{
											printf("\n\t请输入正确操作数：");

										}


									}
								}
					}

				}

			}			
		} // else if (len == 11)
		// 输入字符非法
		else 
		{
			system("cls");
			printf("\n\t请输入正确的订单号或手机号\n");
			printf("\n\t请输入订单号或订票手机号：");
		}
	} // while (True)


	return;
}

// 退出系统
// Freeze
void DP_ExitSys()
{
	printf("\n\t感谢您使用本系统，请确认是否要退出\n");
	printf("\n\ty：确定退出\n\tn：取消\n");
	printf("\n\t请输入操作指令：");

	char ensure[5];
	while (True)
	{
		scanf("%s", &ensure);
		getchar();
		if (strcmp(ensure, "y") == 0) exit(0);
		else if (strcmp(ensure, "n") == 0) { system("cls"); return; }
		else printf("\n\t请输入正确操作指令：");
	}
}

