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
	SearchResult* SR;
	SearchResult *p;

	while (True)
	{

		printf("请输入出发地：");
		scanf("%s", &Leave);
		getchar();
		printf("请输入目的地：");
		scanf("%s", &Arrive);
		getchar();

		printf("出发地是：%s\n", Leave);
		printf("目的地是：%s\n", Arrive);
	
		// 获取查询结果
		SR = UF_SearchStop(Leave, Arrive);
		p = SR->NextResult;

		// 清屏，显示查询结果
		system("cls");
		printf("\n\n");
		printf("%5s查询到从%s到%s的班次如下：\n"," ", Leave, Arrive);

		if (!SR) printf("%5s查询不到可用班次\n", " ");
		else if (SR)
		{
			printf("%5s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
					" ", " ", "车次编号", " ",  " ", "出发地", " ", " ", "到达地", " "," ", "出发时间", " "," ", "到达时间", " ", " ", "购票张数", " ", " ");
			while (p)
			{
				printf("%5s|%2s%-10s%3s|%2s%-10s%6s|%2s%-10s%3s|%2s%-8s%3s|%2s%-8s%3s|%2s%-8s%3s|%5s\n",\
						" ", " ", p->TrainNum, " ",  " ", p->Leave, " ", " ", p->Arrive, " "," ", BF_TimeToStr(p->LeaveTime[0], p->LeaveTime[1]), " ", " ", BF_TimeToStr(p->ArriveTime[0], p->ArriveTime[1]), " ", " ", BF_IntToStr(p->TrainNode->SurplusTicket), " ", " ");
				p = p->NextResult;
			}

		}
		printf("%s\n", "------------------------------------------------------------------------------------------------------------");
		printf("\n\t请输入下一步指令:\n");
		
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
					case 49: {system("cls"); break; }
					case 50: {system("cls"); return; }
					}
				}
				else printf("请输入正确操作数\n");
			}
		}
		// 本次查询有可用班次
		else if (SR)
		{
			printf("\t% s\n\t% s\n\t% s\n\t% s\n\t% s\n\n", "1、按照出发时间排序", "2、按照到达时间排序", "3、按照运行时间排序", "4、订票", "5、退出查询");
			printf("请输入要操作的功能（数字1-5）：");
			while (True)
			{

				scanf("%c", &command);
				getchar();
				if (command >= 49 && command <= 53) while(True) 
				{
					switch (command)
					{
						// 出发时间排序
						case 49: 
						{
							sys("cls");
							printf("%5s查询到从%s到%s的班次如下：\n"," ", Leave, Arrive);
							p = UF_LeaveTimeSort(SR);
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
							command = -1;
						}
						// 运行时间排序 
						case 50: 
						{

							sys("cls");
							printf("%5s查询到从%s到%s的班次如下：\n"," ", Leave, Arrive);
							p = UF_RunTimeSort(SR);
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
							command = -1;
						}
						// 到达时间排序
						case 51: 
						{ 

							sys("cls");
							printf("%5s查询到从%s到%s的班次如下：\n"," ", Leave, Arrive);
							p = UF_ArriveTimeSort(SR);
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
							command = -1;
						}
						// 订票
						case 52:
						{ 
							
						}
						// 退出查询
						case 53: 
						{
							system("cls"); return; 
						}
						// 重新进入菜单
						case -1:
						{
							printf("\t% s\n\t% s\n\t% s\n\t% s\n\t% s\n\n", "1、按照出发时间排序", "2、按照到达时间排序", "3、按照运行时间排序", "4、订票", "5、退出查询");
							printf("请输入要操作的功能（数字1-5）：");
							scanf("%c", &in_command);
							getchar();
							if (in_command >= 49 && in_command <= 53) command = in_command;
							else
							{
								printf("请输入正确操作数\n");
							}
						}
					} // switch (command)
				} // if (command >= 49 && command <= 53)
				else printf("请输入正确操作数\n");
			}
		}


	}

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
	// 感谢您使用本系统，请确认是否要退出
	// y：确定退出
	// n：取消

	printf("Enter 5\n");
	return;
}
