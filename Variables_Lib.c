// 本文件用于定义并存放项目运行时依赖的关键变量
// 此文件的变量会在项目中共用
// 含有：
// 以上变量以'VL_'开头
//
// Code Status: Freeze

#include "V_Lib.h"


// 车票车次信息总入口
TOP_TrainInfo* VL_Ti_Lib;

// 订单信息总入口
PhoneOrder* VL_Or_Lib;

// 用于检索的数据库
// 以车次搜索站点
TrainIndexDB* VL_TI_DB;

// 以站点搜索车次
StopIndexDB* VL_SI_DB;

// 订单编号池
OrderSet* VL_OrderID;


