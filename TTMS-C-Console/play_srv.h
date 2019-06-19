//structs
#include "common.h"
#include "enums.h"

typedef struct {
	int ID;   //��ĿID
	char name[51];              //��Ŀ����
	char type[21];           //��Ŀ����
	char area[11];               //��Ŀ��Ʒ����
	play_rating_t rating;       //��Ŀ�ȼ�
	int duration;               //ʱ�����Է���Ϊ��λ
	user_date_t start_date;     //��ʼ��ӳ����
	user_date_t end_date;       //��ӳ��������
	int price;                  //Ʊ��
}play_t;

typedef struct play_node {
	play_t data;
	struct play_node* next;
	struct play_node* prev;
}play_node_t, * play_list_t;


// Variables

extern int play_unassignedID;
extern play_node_t* play_head;

// Functions

// ��������Play��ID�����ز���1
extern int play_srv_getID();

//��������һ��play_t��ע�ⷵ��ֵ
extern play_t play_srv_generate(int ID, char name[51], char type[21], char area[11], play_rating_t rating, int duration, user_date_t start_date, user_date_t end_date, int price);

extern void play_srv_add(play_t inputPlay_t); //ӰƬ�����


//����ID���ң�����play_list_t.û�ҵ��򷵻�NULL
extern play_list_t play_srv_findByID(int inputID);


//ɾ��play�������ɾ��play�������������
// ɾ���ɹ�����1,����0
extern int play_srv_deleteByID(int inputID);

//����play_t���޸�
// �޸ĳɹ�����1,����0
extern int play_srv_modifyByPlay_t(play_t inputPlay_t);

extern void play_srv_printAll();