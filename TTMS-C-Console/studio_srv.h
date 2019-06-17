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

extern void studio_srv_add(studio_t inputStudio_t);

extern void studio_printAll();