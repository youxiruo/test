#include "syslib.h"

void err_ret(const char *fmt,...)
{
	va_list ap;
	va_start(ap ,fmt);//将参数ap设置为可变参数列表的第一个参数。参数ap的类型必须为va_list。参数fmt是在可变参数列表之前的那一个参数
	//func(fmt,ap);
	va_end(ap);//所有参数都被传递了，释放指针
	return;
}
