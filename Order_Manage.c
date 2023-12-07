// 本文件用于存放订单管理的函数
// 所依赖的关键变量存放于Variables_Lib.c中
// 本文件的函数名以'OM_'开头
//
// Test Status: Undo
// Code Status: Working
//
// 函数与功能对应:
// 
// 初始化VL_Or_Lib
// OM_InitOrder()：初始化VL_Or_Lib
// 返回值：NOSPACE, OK
// 
//


#include "V_Lib.h"
#include <stdlib.h>
#include "F_Lib.h"

// 初始化VL_Or_Lib
Status OM_InitOrder()
{
	// 申请PhoneOrder结点
	PhoneOrder* p;
	p = (struct PhoneOrder*)malloc(sizeof(struct PhoneOrder));
	if (!p) return NOSPACE; // 无可用空间
	VL_Or_Lib = p; // 分配成功的内存地址赋值给VL_Or_Lib
	// 初始化变量值
	p->NodeKind = "H";
	p->phone = -1;
	p->OrderList = NULL;
	p->next = NULL;
	return OK; 
}



