//#ifndef _seat_status_t
//#define _seat_status_t
//��λ״̬ 
typedef enum {
	SEAT_NONE = 0,			//��λ�����ڣ�������
	SEAT_GOOD = 1,			//��λ���
	SEAT_BROKEN = 9			//�𻵵���λ
} seat_status_t;
//#endif

//#ifndef _seatRelated
//#define _seatRelated
//��λ���ݽṹ 
typedef struct 
{
	int ID;					//��λid
	int roomID;				//�����ݳ���id
	int row;           		//��λ�к�
	int column;        		//��λ�к�
	seat_status_t status;
} seat_t;


//˫������
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

// ��������Seat��ID�����ز���1
extern int seat_srv_getID();

//��������һ��seat_t��ע�ⷵ��ֵ
extern seat_t seat_srv_generate(int ID, int roomID, int row, int column, seat_status_t status);

//Seat�����
extern void seat_srv_add(seat_t inputSeat_t);

//����ID���ң�����seat_list_t.û�ҵ��򷵻�NULL
extern seat_list_t seat_srv_findByID(int inputID);

//����seat_t���޸�
// �޸ĳɹ�����1,����0
extern int seat_srv_modifyBySeat_t(seat_t inputSeat_t);

//ɾ��seat�������ɾ��seat�������������
// ɾ���ɹ�����1,����0
extern int seat_srv_deleteByID(int inputID);

extern void seat_srv_printAll();

/*
extern int seat_srv_deleteAllByRoomId(int roomId);
ɾ�������������λ
extern int seat_srv_fetchById(int Id, seat_t buf);
����Id��ȡ������Ϣ
int seat_srv_fetchValidByRoomID(seat_list_t list, int roomId);
�����ݳ�����ID�����Ч��λ
int seat_srv_fetchByRoomId(seat_list_t list, int roomId);
�����ݳ�����
seat_node_t Seat_Srv_FindByRowCol(seat_list_t list, int row, int column);

void seat_srv_sortSeatList(seat_list_t list);
���������кţ��кŽ�������

void seat_srv_addToSortedList(seat_list_t list, seat_node_t node);
��һ����λ�ڵ�������������λ������*/