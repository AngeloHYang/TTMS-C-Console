//structs
/*
Rating symbol	Meaning
G rating symbol
G �C General Audiences
All ages admitted. Nothing that would offend parents for viewing by children.
PG- rating symbol
PG �C Parental Guidance Suggested
Some material may not be suitable for children. Parents urged to give "parental guidance". May contain some material parents might not like for their young children.
PG-13 rating symbol
PG-13 �C Parents Strongly Cautioned
Some material may be inappropriate for children under 13. Parents are urged to be cautious. Some material may be inappropriate for pre-teenagers.
R rating symbol
R �C Restricted
Under 17 requires accompanying parent or adult guardian. Contains some adult material. Parents are urged to learn more about the film before taking their young children with them.
NC-17 rating symbol
NC-17 �C Adults Only
No One 17 and Under Admitted. Clearly adult. Children are not admitted.
*/
typedef enum {
	PLAY_RATE_G = 1,
	PLAY_RATE_PG = 2,
	PLAY_RATE_PG13 = 3,
	PLAY_RATE_R = 4,
	PLAY_RATE_NC_17 = 5
}play_rating_t;

typedef struct {
	int year;
	int month;
	int day;
}ttms_date_t;

typedef struct {
	int ID;   //��ĿID
	char name[51];              //��Ŀ����
	char type[21];           //��Ŀ����
	char area[11];               //��Ŀ��Ʒ����
	play_rating_t rating;       //��Ŀ�ȼ�
	int duration;               //ʱ�����Է���Ϊ��λ
	ttms_date_t start_date;     //��ʼ��ӳ����
	ttms_date_t end_date;       //��ӳ��������
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
extern play_t play_srv_generate(int ID, char name[51], char type[21], char area[11], play_rating_t rating, int duration, ttms_date_t start_date, ttms_date_t end_date, int price);

extern void play_srv_add(play_t inputPlay_t); //ӰƬ�����


//����ID���ң�����play_list_t.û�ҵ��򷵻�NULL
extern play_list_t play_srv_findByID(int inputID);


//ɾ��play�������ɾ��play�������������
// ɾ���ɹ�����1,����0
extern int play_srv_deleteByID(int inputID);

//����play_t���޸�
// �޸ĳɹ�����1,����0
extern int play_srv_modifyByPlay_t(play_t inputPlay_t);

extern void play_printAll();