#include "../sys/sysdata.h"


int configcomm(unsigned char *filename)
{
    FILE *fp;
	char stream[8192];
	
	//���ļ�
	if((fp=Fopen(filename,"r"))==NULL)
	{
		return -1;
	}

	while(Fgets(stream,8192,fp))

}

