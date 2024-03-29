#include "schedule_srv.h"

//票类型的定义
#ifndef _enum_status
#define _enum_status
typedef enum {
	TICKET_UNSOLD = 0,
	TICKET_SOLD = 1,
	TICKET_ERROR = 9 // If the ticket is sold and the seat is broken later, etc
}ticket_status_t;
#endif

//票实体数据类型的定义
typedef struct {
	int ID;
	int schedule_ID;
	int seat_ID;
	int soldBy; // -1 for unsold
	ticket_status_t status;
}ticket_t;

//票链表节点的定义
typedef struct ticket_node 
{
	ticket_t data;
	struct ticket_node*next, *prev;
}ticket_node_t, *ticket_list_t;

// Variables

extern int ticket_unassignedID;
extern ticket_node_t* ticket_head;

// Functions 

// 生成新增Ticket的ID，返回并加1
extern int ticket_srv_getID();

//用于生成一个ticket_t，注意返回值
extern ticket_t ticket_srv_generate(int ID, int schedule_ID, int seat_ID, int soldBy, ticket_status_t status);

extern void ticket_srv_add(ticket_t inputTicket_t); //ticket的添加

//按照ID查找，返回ticket_list_t.没找到则返回NULL
extern ticket_list_t ticket_srv_findByID(int inputID);

//删除ticket，不解决删除ticket引起的其他问题
// 删除成功返回1,否则0
extern int ticket_srv_deleteByID(int inputID);

//输入ticket_t以修改
// 修改成功返回1,否则0
extern int ticket_srv_modifyByTicket_t(ticket_t inputTicket_t);

extern void ticket_srv_printAll();

extern void ticket_srv_makeTicketERROR_byEndTimeAndSeat(int seatID, int currentSecond);

//extern void ticket_srv_makeTicketInvalidAfterDate(user_date_t byDateAfter, int playID);

//extern void ticket_srv_makeTicketInvalidBeforeDate(user_date_t byDateBefore, int playID);

extern void ticket_srv_deleteTicketByPlayID(int playID);

extern ticket_list_t ticket_srv_findTicketByScheduleAndSeat(schedule_list_t theSchedule, int whichRow, int whichColumn);

extern void ticket_srv_deleteTicketBySchedule(int scheduleID);

extern int ticket_srv_playIDReturnSoldNumber(int playID);

extern void ticket_srv_clerkIDAndDateToSoldNumberAndTotal(int clerkID, user_date_t startDate, user_date_t endDate, int* sold, int* total);