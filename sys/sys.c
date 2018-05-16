#include "sysdata.h"

#include "../cfg/cfgsys.h"

SYSTEM_DATA_t		SystemData;


int main()
{


	strcpy(COMMCFGPATH,"comconfig.ini");
	
	//配置文件读取COMCONFIG文件
    configcomm(COMMCFGPATH);
    
	//打开网口，启动网口收发功能 SOCKET功能

	//确认和前后台连接正常

	//接收消息

	//发送消息

	//处理消息
	
}

