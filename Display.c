// 本文件存放的函数用于显示信息
// 本文件的函数名以'DP_'开头
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

		printf("请输入出发地：");
		scanf("%s", &Leave);
		getchar();
		printf("请输入目的地：");
		scanf("%s", &Arrive);
		getchar();

		// 获取查询结果
		SR = UF_SearchStop(Leave, Arrive);

		// 清屏，显示查询结果
		system("cls");
		printf("\n\n");

		if (!SR) printf("%5s查询不到从%s到%s的可用班次\n%5s请输入下一步指令\n", " ", Leave, Arrive," ");
		else if (SR)
		{
			// 默认以出发时间排序
			p = UF_LeaveTimeSort(SR);
			command = -1;
		}
		
		// 本次查询无可用班次 
		if (!SR)
		{
			printf("\t%s\n\t%s\n\n", "1、重新查询", "2、退出查询");
			printf("请输入要操作的功能（数字1-2）：");
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
				else printf("请输入正确操作数\n");
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
						
						command = -1;
					}
					// 运行时间排序 
					case 50: 
					{
						system("cls");
						p = UF_RunTimeSort(SR);
						// 显示结果
						command = -1;
					}
					// 到达时间排序
					case 51: 
					{
						system("cls");
						p = UF_ArriveTimeSort(SR);
						// 显示结果
						command = -1;
					}
					// 订票
					case 52:
					{ 
						// 输入车次号
						while (True)
						{
							printf("请输入车次号（字母需要大写）：");
							scanf("%s", &TrainNum);
							getchar();
							q = SR->NextResult;
							while (q)
							{
								if (strcmp(q->TrainNum, TrainNum) == 0) break;
								else q = q->NextResult;
							}
							// 车次号不存在
							if (!q) printf("请输入正确车次号\n");
							else if (q) break;
							
						}
						
						// 输入手机号
						while (True)
						{
							printf("请输入手机号：");
							scanf("%s", &Phone);
							getchar();
							if (strlen(Phone) == 11) break;
							else printf("请输入正确的11位手机号\n");
						}
						
						// 订票张数
						while (True)
						{
							printf("请输入订购张数：");
							scanf("%d", &Ticket);
							getchar();
							if (Ticket > 0)break;
							else printf("请输入数值为正的票数\n");
						}

						// 判断余票是否充足 
						// 确认订单信息
						// 充足 正式订单
						if (Ticket < q->TrainNode->SurplusTicket)
						{
							// 确认信息
							printf("以下为订单信息：\n");
							printf("车次编号：%s\n出发站：%s\n到达站：%s\n出发时间：%s\n到达时间：%s\n购票张数：%d\n", \
								TrainNum, Leave, Arrive, BF_TimeToStr(q->LeaveTime[0], q->LeaveTime[1]), BF_TimeToStr(q->ArriveTime[0], q->ArriveTime[1]), Ticket);
							printf("确认？\ny：确认订单\nn：放弃订单\n");
							// 确认操作
							while (True)
							{
								char* ensure = (char*)malloc(sizeof(char)*10);
								scanf("%s", &ensure);
								getchar();
								if (strcmp(ensure, "y") == 0) break;
								else if (strcmp(ensure, "n") == 0)
								{
									printf("取消下单，三秒后将返回主菜单\n");
									Sleep(3);
									system("cls");
									return;
								}
								else printf("请输入正确操作指令\n");

							}
							if (UF_New_F_Order(TrainNum, Leave, Arrive, Ticket, Phone) == OK)
							{
								printf("\n下单成功\n");
								printf("三秒后将返回主菜单\n");
								Sleep(3);
								system("cls");
								return;
							}
							else
							{
								printf("发生存储错误，三秒后将自动返回主菜单");
								Sleep(3);
								system("cls");
								return;
							}
						}
						// 不足 候补订单
						else
						{
							// 确认信息
							printf("以下为订单信息：\n");
							printf("车次编号：%s\n出发站：%s\n到达站：%s\n出发时间：%s\n到达时间：%s\n购票张数：%d\n", \
								TrainNum, Leave, Arrive, BF_TimeToStr(q->LeaveTime[0], q->LeaveTime[1]), BF_TimeToStr(q->ArriveTime[0], q->ArriveTime[1]), Ticket);
							printf("余票数量不足，是否进入候补？\n");
							printf("y：进入候补\nn：放弃\n");
							// 确认操作
							while (True)
							{
								char* ensure = (char*)malloc(sizeof(char)*10);
								scanf("%s", &ensure);
								getchar();
								if (strcmp(ensure, "y") == 0) break;
								else if (strcmp(ensure, "n") == 0)
								{
									printf("取消下单三秒后将返回主菜单\n");
									Sleep(3);
									system("cls");
									return;
								}
								else printf("请输入正确操作指令\n");

							}
							if (UF_New_W_Order(TrainNum, Leave, Arrive, Ticket, Phone) == OK)
							{
								printf("\n加入候补成功");
								printf("三秒后将返回主菜单\n");
								Sleep(3);
								system("cls");
								return;
							}
							else
							{
								printf("发生存储错误，三秒后将自动返回主菜单");
								Sleep(3);
								system("cls");
								return;
							}
						}

					}
					// 退出查询
					case 53: 
					{
						system("cls"); return; 
					}
					// 显示
					case -1:
					{
						system("cls");
						printf("\n%5s查询到从%s到%s的班次如下：\n\n"," ", Leave, Arrive);
						printf("%5s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n", \
							" ", " ", "车次编号", " ", " ", "出发地", " ", " ", "到达地", " ", " ", "出发时间", " ", " ", "到达时间", " ", " ", "购票张数", " ", " ");
						while (p)
						{
							printf("%5s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n", \
									" ", " ", p->TrainNum, " ", " ", p->Leave, " ", " ", p->Arrive, " ", " ", BF_TimeToStr(p->LeaveTime[0], p->LeaveTime[1]), " ", " ", BF_TimeToStr(p->ArriveTime[0], p->ArriveTime[1]), " ", " ", BF_IntToStr(p->TrainNode->SurplusTicket), " ", " ");
							p = p->NextResult;

						}
						// 进入后续操作菜单
						printf("%s\n", "------------------------------------------------------------------------------------------------------------");
						printf("\n\t请输入下一步指令:\n");
						command = -2;
					}
					// 进入有搜寻结果菜单
					case -2:
					{
						while (True)
						{

							printf("\t% s\n\t% s\n\t% s\n\t% s\n\t% s\n\n", "1、按照出发时间排序", "2、按照到达时间排序", "3、按照运行时间排序", "4、订票", "5、退出查询");
							printf("请输入要操作的功能（数字1-5）：");
							while (True)
							{
								scanf("%c", &in_command);
								getchar();
								if (in_command >= 49 && in_command <= 53) {command = in_command; break;}
								else{printf("请输入正确操作数\n");}
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

// 输入订单号查询订单
void DP_CheckOrder()
{

	char* OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);
	char* ph = (char*)malloc(sizeof(char) * STRLENGTH);
	OrderSet* order;

	while (True)
	{
		while (True)
		{
			printf("请输入订单号：");
			scanf("%s", &OrderNum);
			getchar();
			if (strlen(OrderNum) != 10 )
			{
				printf("订单号格式不正确，请重新输入\n");
				continue;
			}
			else if (strlen(OrderNum) == 10) break;
		}
		while (True)
		{
			printf("请输入手机号：");
			scanf("%s", &ph);
			getchar();
			if (strlen(ph) != 11)
			{
				printf("手机号格式不正确，请重新输入11位手机号\n");
				continue;
			}
			else if (strlen(ph) == 11) break;

		}

		order = UF_GetOrderInfo(OrderNum);

		if (!order)
		{
			printf("无此订单号，请重新输入\n");
		}
		else if (order) break;

	}
	
	while (True)
	{
		// 该订单为正式订单
		if (strcmp(order->OrderKind, "F") == 0)
		{
			while (True)
			{

				if (strcmp(order->OrderNode->phone, ph) == 0)
				{
					printf("查询到订单编号为%s的信息如下：\n\n", OrderNum);
					printf("订单类型：正式订单\n");
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%5s\n",\
					" ", " ", "车次编号", " ", " ", "订单编号", " ", " ", "出发地", " ", " ", "到达地", " ", " ", "购票张数", " ", " ");
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%5s\n",\
					" ", " ", order->OrderNode->TrainNum, " ", " ", OrderNum,  " ", " ", order->OrderNode->Start, " ", " ", order->OrderNode->End, " ", " ", BF_IntToStr(order->OrderNode->TicketNum), " ", " ");
				}
				else
				{
					printf("手机号不正确，请重新输入，或按q退出查询：");
					scanf("%s", ph);
					getchar();
					if (strcmp(ph, "q") == 0) return;
				}
			}
		}
		// 该订单为候补订单
		else if (strcmp(order->OrderKind, "W") == 0)
		{
			
			while (True)
			{

				if (strcmp(order->WaitOrderNode->phone, ph) == 0)
				{
					printf("查询到订单编号为%s的信息如下：\n\n", OrderNum);
					printf("订单类型：候补订单\n");
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%5s\n",\
					" ", " ", "车次编号", " ", " ", "订单编号", " ", " ", "出发地", " ", " ", "到达地", " ", " ", "购票张数", " ", " ");
					printf("%5s|%2s%-10s%3s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%5s\n",\
					" ", " ", order->WaitOrderNode->TrainNum, " ", " ", OrderNum,  " ", " ", order->WaitOrderNode->Start, " ", " ", order->WaitOrderNode->End, " ", " ", BF_IntToStr(order->WaitOrderNode->TicketNum), " ", " ");
				}
				else
				{
					printf("手机号不正确，请重新输入，或按q退出查询：");
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
	// “请输入手机号”
	// 显示信息 有/无

	// “请输入任意键返回” getchar

	printf("Enter 3\n");
	return;
}

void DP_WithdrawOrder()
{
	// 请输入订单手机号
	// 请输入要取消的订单

	// -订单号错误-请重新输入，或按任意键退出
	// -订单号正确-\n
	// 您要取消的订单信息如下：
	//
	// 确认取消此订单？请输入操作指令或按任意键退出（订单仍会被保留）
	// y：确定取消此订单
	// n：保留此订单
	// 请输入指令：

	printf("Enter 4\n");
	return;
}

void DP_ExitSys()
{
	printf("\n感谢您使用本系统，请确认是否要退出\n");
	printf("y：确定退出\nn：取消\n");
	printf("请输入操作指令：");

	char* ensure = (char*)malloc(sizeof(char) * 10);
	scanf("%s", &ensure);
	getchar();
	while (True)
	{
		if (strcmp(ensure, "y") == 0) exit(0);
		else if (strcmp(ensure, "n") == 0) return;
		else printf("请输入正确操作指令\n");
	}
}
