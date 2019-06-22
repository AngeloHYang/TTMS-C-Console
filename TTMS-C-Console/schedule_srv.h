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
	// ��ʼʱ��
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
// ��������schedule��ID�����ز���1
extern int schedule_srv_getID();

//��������һ��schedule_t��ע�ⷵ��ֵ
extern schedule_t schedule_srv_generate(int ID, int play_ID, int studio_ID, user_date_t date, user_time_t time);

//schedule�����
extern void schedule_srv_add(schedule_t inputSchedule_t);

//����ID���ң�����schedule_list_t.û�ҵ��򷵻�NULL
extern schedule_list_t schedule_srv_findByID(int inputID);

//ɾ��schedule�������ɾ��schedule�������������
// ɾ���ɹ�����1,����0
extern int schedule_srv_deleteByID(int inputID);

//����schedule_t���޸�
// �޸ĳɹ�����1,����0
extern int schedule_srv_modifyBySchedule_t(schedule_t inputSchedule_t);

extern void schedule_srv_printAll();