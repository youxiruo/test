#include "syslib.h"

void err_ret(const char *fmt,...)
{
	va_list ap;
	va_start(ap ,fmt);//������ap����Ϊ�ɱ�����б�ĵ�һ������������ap�����ͱ���Ϊva_list������fmt���ڿɱ�����б�֮ǰ����һ������
	//func(fmt,ap);
	va_end(ap);//���в������������ˣ��ͷ�ָ��
	return;
}
