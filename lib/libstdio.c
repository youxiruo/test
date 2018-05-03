#include	"syslib.h"


char *
Fgets(char *buf,int bufsize,FILE *stream)
{
	char *rtpr;
	if((rtpr=fgets(buf,bufsize,stream))==NULL && ferror(fp))
		err_ret("fgets err");
	return (rtpr);
}


FILE *
Fopen(const char *filename,const char *mode)
{
	FILE *fp;
	if((fp=fopen(filename,mode))==NULL)
    {
		err_ret("fopen err");
	}
	return (fp);
}

