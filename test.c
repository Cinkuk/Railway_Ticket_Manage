#include "V_Lib.h"
#include "F_Lib.h"
#include <stdio.h>
#include <string.h>

void main()
{	
#if 0
	// TEST BF_Merge_Char
	char a[10] = { 'A','5','6','0','0','0','0','5','9'};
	char b[10] = { 'A','5','6','0','0','0','0','5','9','0'};
	printf("%s\n", BF_Merge_Char(a));
	printf("%s\n", BF_Merge_Char(b));
#endif

#if 0
	// TEST BF_Get_Train_Num
	char* a = "D7523";
	char* b = "K12";
	printf("%d\n", BF_Get_Train_Number(a));
	printf("%d\n", BF_Get_Train_Number(b));
#endif

#if 0
	// TEST OM_CreateOrderNum
	printf("%s", OM_CreateOrderNum());
#endif

#if 0
	// TEST BE_StrToInt
	char* a = "1253";
	char* b = "01258";
	char* c = "0";
	char* d = "10";
	printf("%d\n", BF_StrToInt(a));
	printf("%d\n", BF_StrToInt(b));
	printf("%d\n", BF_StrToInt(c));
	printf("%d\n", BF_StrToInt(d));
#endif

	char* a = "00:00";
	char* b = "15:47"; // 947
	char* c = "09:52"; // 592
	char* d = "22.16"; // 1336
	printf("%d\n", BF_StrToMin(a));
	printf("%d\n", BF_StrToMin(b));
	printf("%d\n", BF_StrToMin(c));
	printf("%d\n", BF_StrToMin(d));

}
