//票类型的定义
typedef enum {
	TICKET_AVL = 0,
	TICKET_SOLD = 1,
	TICKET_RESV = 9

}ticket_status_t;
//票实体数据类型的定义
typedef struct {
	int id;
	int schedule_id;
	int seat_id;
	int price;
	ticket_status_t status;
}ticket_t;
//票链表节点的定义
typedef struct ticket_node {
	ticket_t data;
	struct ticket_node*next, *prev;
}ticket_node_t, *ticket_list_t;

extern void Schedule_Srv_FetchByID();
extern void Ticket_Srv_GenBatch();