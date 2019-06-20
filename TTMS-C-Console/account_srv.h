// Structs
typedef enum {
	USER_ANONYMOUS = 0,
	USER_CLERK = 1,
	USER_MANAGER = 2,
	USER_ADMIN = 9,
} account_type_t;

typedef struct {
	int ID;
	account_type_t type;
	char username[30];
	char password[30];
	char phone[20];
	char nickname[30];
} account_t;

//account_t g1_Curuser = { 0,usr_anomy,"Anonymous","" };
//定义全局变量g1_Curuser储存系统用户信息

typedef struct account_node {
	account_t data;
	struct account_node* next;
	struct account_node* prev;
} account_node_t, * account_list_t;

// Variables

extern int account_unassignedID;
extern account_node_t* account_head;

// functions
// 生成新增Account的ID，返回并加1
extern int account_srv_getID();

//用于生成一个account_t，注意返回值
extern account_t account_srv_generate(int ID, account_type_t type, char username[30], char password[30]);

extern void account_srv_add(account_t inputAccount_t);

//按照ID查找，返回account_list_t.没找到则返回NULL
extern account_list_t account_srv_findByID(int inputID);

//输入account_t以修改
// 修改成功返回1,否则0
extern int accout_srv_modifyByPlay_t(account_t inputAccount_t);

//删除account，不解决删除account引起的其他问题
// 删除成功返回1,否则0
extern int account_srv_deleteByID(int inputID);

// 查询总共有多少用户
extern int account_srv_howManyInToto();