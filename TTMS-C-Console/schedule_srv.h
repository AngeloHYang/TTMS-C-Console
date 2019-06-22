//Struct

#include "common.h"
#include "enums.h"

/*
typedef struct {
	int hour;
	int minute;
	int second;
}ttms_time_t;

typedef struct {
	int year;
	int month;
	int day;
}ttms_date_t;
*/


typedef struct {
	int ID;
	int play_ID;
	int studio_ID;
	// 开始时间
	user_date_t date;
	user_time_t time;

	int exist;
	
}schedule_t;

typedef struct schedule_node {
	schedule_t data;
	struct schedule_node* next;
	struct schedule_node* prev;
}schedule_node_t,*schedule_list_t;

// variables

extern int schedule_unassignedID;
extern schedule_node_t* schedule_head;

// functions
// 生成新增schedule的ID，返回并加1
extern int schedule_srv_getID();

//用于生成一个schedule_t，注意返回值
extern schedule_t schedule_srv_generate(int ID, int play_ID, int studio_ID, user_date_t date, user_time_t time);

//schedule的添加
extern void schedule_srv_add(schedule_t inputSchedule_t);

//按照ID查找，返回schedule_list_t.没找到则返回NULL
extern schedule_list_t schedule_srv_findByID(int inputID);

//删除schedule，不解决删除schedule引起的其他问题
// 删除成功返回1,否则0
extern int schedule_srv_deleteByID(int inputID);

//输入schedule_t以修改
// 修改成功返回1,否则0
extern int schedule_srv_modifyBySchedule_t(schedule_t inputSchedule_t);

extern void schedule_srv_printAll();