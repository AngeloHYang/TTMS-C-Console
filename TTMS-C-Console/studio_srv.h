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

extern int studio_unassignedID;// 为未分配的ID
extern studio_list_t studio_head;

// functions

// 生成新增Studio的ID，返回并加1
extern int studio_srv_getID();

//用于生成一个studio_t，注意返回值
extern studio_t studio_srv_generate(int ID, char* name, int rowsCount, int colsCount);

//负责将完整的studio_t添加到链表
extern void studio_srv_add(studio_t inputStudio_t);

extern void studio_srv_printAll();

//按照ID查找，返回studio_list_t.没找到则返回NULL
extern studio_list_t studio_srv_findByID(int inputID);

//删除studio，不解决删除studio引起的其他问题
extern int studio_srv_deleteByID(int inputID);


//输入studio_t以修改
// 修改成功返回1,否则0
extern int studio_srv_modifyByStudio_t(studio_t inputStudio_t);