#include "sysdata.h"



void configsystem(unsigned char *filename)
{
	//从当前地址读取com_config.ini


	//从当前地址读取sys_config.ini

	
}



int main()
{

	//配置文件读取SYS文件
	configsystem(SYSCFGPATH)

	//配置文件读取COMCONFIG文件
    configcomm(COMMCFGPATH)
    
	//打开网口，启动网口收发功能 SOCKET功能

	//确认和前后台连接正常

	//接收消息

	//发送消息

	//处理消息
	
}

