// Struct
typedef struct
{
	int ID;
	char name[30];
	int rowsCount;
	int colsCount;
} studio_t;

typedef struct studio_node
{
	studio_t data;
	struct studio_node* next;
	struct studio_node* prev;
} studio_node_t, *studio_list_t;

// variables

extern int studio_unassignedID;// Ϊδ�����ID
extern studio_list_t studio_head;

// functions

// ��������Studio��ID�����ز���1
extern int studio_srv_getID();

//��������һ��studio_t��ע�ⷵ��ֵ
extern studio_t studio_srv_generate(int ID, char* name, int rowsCount, int colsCount);

//����������studio_t��ӵ�����
extern void studio_srv_add(studio_t inputStudio_t);

extern void studio_srv_printAll();

//����ID���ң�����studio_list_t.û�ҵ��򷵻�NULL
extern studio_list_t studio_srv_findByID(int inputID);

//ɾ��studio�������ɾ��studio�������������
extern int studio_srv_deleteByID(int inputID);


//����studio_t���޸�
// �޸ĳɹ�����1,����0
extern int studio_srv_modifyByStudio_t(studio_t inputStudio_t);