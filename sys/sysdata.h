#ifndef _SYSDATA_H
#define _SYSDATA_H

typedef struct
{
	unsigned char cfgPath[128];
	unsigned char commPath[128];

	//com_config.ini  ��������ò���socket���ò���  port,ip,�����/�ͻ��˱�ʶ,ģ���,��������,������ͣ��ǳ�
	

	//sys_config.ini ��������ò���

	
}SYSTEMDATA_t;


extern SYSTEM_DATA_t SystemData;


#define SYSCFGPATH	(SystemData.cfgPath)
#define COMMCFGPATH (SystemData.commPath)


#endif
