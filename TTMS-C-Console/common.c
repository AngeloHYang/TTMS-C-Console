/*
* Copyright(C), 2007-2008, XUPT Univ.	 
* File name: common.c			 
* Description : 通用函数定义	 
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015年4月22日		 
*/

#include "Common.h"

#include<stdio.h>
#include<fcntl.h>
#include <time.h>

//将字符串str就地转换为大写字符串，并返回字符串头指针
char *Str2Upper(char *str) {
	if (NULL == str)
		return NULL;
	else {
		char *p = str;
		while ('\0' != *p) {
			if (*p >= 'a' && *p <= 'z')
				*p -= 32;
			p++;
		}
		return str;
	}
}

//将字符串str就地转换为小写字符串，并返回字符串头指针
char *Str2Lower(char *str) {
	if (NULL == str)
		return NULL;
	else {
		char *p = str;
		while ('\0' != *p) {
			if (*p >= 'A' && *p <= 'Z')
				*p += 32;
			p++;
		}
		return str;
	}
}

//比较日期dt1, dt2的大小。相等返回0，dt1<dt2返回-1，否则1
int DateCmp(user_date_t dt1, user_date_t dt2) {
	if (dt1.year < dt2.year)
		return -1;
	else if (dt1.year == dt2.year && dt1.month < dt2.month)
		return -1;
	else if (dt1.year == dt2.year && dt1.month == dt2.month && dt1.day < dt2.day)
		return -1;
	else if (dt1.year == dt2.year && dt1.month == dt2.month
			&& dt1.day == dt2.day)
		return 0;
	else
		return 1;
}

//比较时间tm1, tm2的大小。相等返回0，tm1<tm2返回-1，否则1
int TimeCmp(user_time_t tm1, user_time_t tm2) {
	if (tm1.hour < tm2.hour)
		return -1;
	else if (tm1.hour == tm2.hour && tm1.minute < tm2.minute)
		return -1;
	else if (tm1.hour == tm2.hour && tm1.minute == tm2.minute && tm1.second < tm2.second)
		return -1;
	else if (tm1.hour == tm2.hour && tm1.minute == tm2.minute
		&& tm1.second == tm2.second)
		return 0;
	else
		return 1;
}

//比较dt1 tm1, dt2 tm2的大小。相等返回0，dt1 tm1<dt2 tm2返回-1，否则1
int DateAndTimeCmp(user_date_t dt1, user_time_t tm1, user_date_t dt2, user_time_t tm2)
{
	if (DateCmp(dt1, dt2) == -1)
	{
		return -1;
	}
	else if (DateCmp(dt1, dt2) == 0)
	{
		if (TimeCmp(tm1, tm2) == -1)
		{
			return -1;
		}
		else if (TimeCmp(tm1, tm2) == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 1;
	}
}

//获取系统当前日期
user_date_t DateNow() {
	user_date_t curDate;
	time_t now;         //实例化time_t结构
	struct tm *timeNow;         //实例化tm结构指针
	time(&now);
	timeNow = localtime(&now);
	curDate.year=timeNow->tm_year+1900;
	curDate.month=timeNow->tm_mon+1;
	curDate.day=timeNow->tm_mday;

	return curDate;
}

//获取系统当前时间
user_time_t TimeNow(){
	user_time_t curTime;
	time_t now;         //实例化time_t结构
	struct tm *timeNow;         //实例化tm结构指针
	time(&now);
	timeNow = localtime(&now);
	curTime.hour=timeNow->tm_hour;
	curTime.minute=timeNow->tm_min;
	curTime.second=timeNow->tm_sec;
	return curTime;
}

/*
 *
 *
 int ScanKeyboard() {
 int in;
 struct termios new_settings;
 struct termios stored_settings;
 tcgetattr(0, &stored_settings);
 new_settings = stored_settings;
 new_settings.c_lflag &= (~ICANON);
 new_settings.c_cc[VTIME] = 0;
 tcgetattr(0, &stored_settings);
 new_settings.c_cc[VMIN] = 1;
 tcsetattr(0, TCSANOW, &new_settings);

 in = getchar();

 tcsetattr(0, TCSANOW, &stored_settings);
 return in;
 }

 */


