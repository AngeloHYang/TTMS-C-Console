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

} account_t;

//account_t g1_Curuser = { 0,usr_anomy,"Anonymous","" };
//����ȫ�ֱ���g1_Curuser����ϵͳ�û���Ϣ

typedef struct account_node {
	account_t data;
	struct account_node* next;
	struct account_node* prev;
} account_node_t, * account_list_t;

// Variables

extern int account_unassignedID;
extern account_node_t* account_head;

// functions
// ��������Account��ID�����ز���1
extern int account_srv_getID();

//��������һ��account_t��ע�ⷵ��ֵ
extern account_t account_srv_generate(int ID, account_type_t type, char username[30], char password[30]);

extern void account_srv_add(account_t inputAccount_t);