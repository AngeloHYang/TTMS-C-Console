//#ifndef _seat_status_t
//#define _seat_status_t
//座位状态 
typedef enum {
	SEAT_NONE = 0,			//座位不存在（过道）
	SEAT_GOOD = 1,			//座位完好
	SEAT_BROKEN = 9			//损坏的座位
} seat_status_t;
//#endif

//#ifndef _seatRelated
//#define _seatRelated
//座位数据结构 
typedef struct 
{
	int ID;					//座位id
	int roomID;				//所在演出厅id
	int row;           		//座位行号
	int column;        		//座位列号
	seat_status_t status;
} seat_t;


//双向链表
typedef struct seat_node 
{
	seat_t data;
	struct seat_node* next,  *prev;
} seat_node_t,  *seat_list_t;
//#endif

// Variables

extern int seat_unassignedID;
extern seat_node_t* seat_head;

// Functions

// 生成新增Seat的ID，返回并加1
extern int seat_srv_getID();

//用于生成一个seat_t，注意返回值
extern seat_t seat_srv_generate(int ID, int roomID, int row, int column, seat_status_t status);

//Seat的添加
extern void seat_srv_add(seat_t inputSeat_t);

//按照ID查找，返回seat_list_t.没找到则返回NULL
extern seat_list_t seat_srv_findByID(int inputID);

//输入seat_t以修改
// 修改成功返回1,否则0
extern int seat_srv_modifyBySeat_t(seat_t inputSeat_t);

//删除seat，不解决删除seat引起的其他问题
// 删除成功返回1,否则0
extern int seat_srv_deleteByID(int inputID);

extern void seat_srv_printAll();

/*
extern int seat_srv_deleteAllByRoomId(int roomId);
删除整个房间的座位
extern int seat_srv_fetchById(int Id, seat_t buf);
根据Id获取数据信息
int seat_srv_fetchValidByRoomID(seat_list_t list, int roomId);
根据演出厅的ID获得有效座位
int seat_srv_fetchByRoomId(seat_list_t list, int roomId);
根据演出厅的
seat_node_t Seat_Srv_FindByRowCol(seat_list_t list, int row, int column);

void seat_srv_sortSeatList(seat_list_t list);
对链表按照行号，列号进行排序

void seat_srv_addToSortedList(seat_list_t list, seat_node_t node);
将一个座位节点加入已排序的座位链表中*/