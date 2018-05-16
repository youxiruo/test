#ifndef _SYSDATA_H
#define _SYSDATA_H


#include "../lib/syslib.h"
#include "../mml/mmlsys.h"



typedef struct
{
	unsigned char cfgPath[128];
	unsigned char commPath[128];

	//com_config.ini  里面的配置参数socket常用参数  port,ip,服务端/客户端标识,模块号,心跳类型,组号类型，昵称
	

	//sys_config.ini 里面的配置参数

	
}SYSTEM_DATA_t;



extern SYSTEM_DATA_t SystemData;


#define SYSCFGPATH	(SystemData.cfgPath)
#define COMMCFGPATH (SystemData.commPath)


#endif
