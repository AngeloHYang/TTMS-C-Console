//Ʊ���͵Ķ���
#ifndef _enum_status
#define _enum_status
typedef enum {
	TICKET_UNSOLD = 0,
	TICKET_SOLD = 1,
	TICKET_ERROR = 9 // If the ticket is sold and the seat is broken later, etc
}ticket_status_t;
#endif

//Ʊʵ���������͵Ķ���
typedef struct {
	int ID;
	int schedule_ID;
	int seat_ID;
	int price;
	int soldBy; // -1 for unsold
	ticket_status_t status;
}ticket_t;

//Ʊ����ڵ�Ķ���
typedef struct ticket_node 
{
	ticket_t data;
	struct ticket_node*next, *prev;
}ticket_node_t, *ticket_list_t;

// Variables

extern int ticket_unassignedID;
extern ticket_node_t* ticket_head;

// Functions 

// ��������Ticket��ID�����ز���1
extern int ticket_srv_getID();

//��������һ��ticket_t��ע�ⷵ��ֵ
extern ticket_t ticket_srv_generate(int ID, int schedule_ID, int seat_ID, int price, int soldBy, ticket_status_t status);

extern void ticket_srv_add(ticket_t inputTicket_t); //ticket�����

//����ID���ң�����ticket_list_t.û�ҵ��򷵻�NULL
extern ticket_list_t ticket_srv_findByID(int inputID);

//ɾ��ticket�������ɾ��ticket�������������
// ɾ���ɹ�����1,����0
extern int ticket_srv_deleteByID(int inputID);

//����ticket_t���޸�
// �޸ĳɹ�����1,����0
extern int ticket_srv_modifyByPlay_t(ticket_t inputTicket_t);

extern void ticket_srv_printAll();

extern void ticket_srv_makeTicketERROR_byEndTimeAndSeat(int seatID, int currentSecond);