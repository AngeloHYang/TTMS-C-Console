//structs
/*
Rating symbol	Meaning
G rating symbol
G – General Audiences
All ages admitted. Nothing that would offend parents for viewing by children.
PG- rating symbol
PG – Parental Guidance Suggested
Some material may not be suitable for children. Parents urged to give "parental guidance". May contain some material parents might not like for their young children.
PG-13 rating symbol
PG-13 – Parents Strongly Cautioned
Some material may be inappropriate for children under 13. Parents are urged to be cautious. Some material may be inappropriate for pre-teenagers.
R rating symbol
R – Restricted
Under 17 requires accompanying parent or adult guardian. Contains some adult material. Parents are urged to learn more about the film before taking their young children with them.
NC-17 rating symbol
NC-17 – Adults Only
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
	int ID;   //剧目ID
	char name[51];              //剧目名称
	char type[21];           //剧目类型
	char area[11];               //剧目出品地区
	play_rating_t rating;       //剧目等级
	int duration;               //时长，以分钟为单位
	ttms_date_t start_date;     //开始放映日期
	ttms_date_t end_date;       //放映结束日期
	int price;                  //票价
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

// 生成新增Play的ID，返回并加1
extern int play_srv_getID();

//用于生成一个play_t，注意返回值
extern play_t play_srv_generate(int ID, char name[51], char type[21], char area[11], play_rating_t rating, int duration, ttms_date_t start_date, ttms_date_t end_date, int price);

extern void play_srv_add(play_t inputPlay_t); //影片的添加


//按照ID查找，返回play_list_t.没找到则返回NULL
extern play_list_t play_srv_findByID(int inputID);


//删除play，不解决删除play引起的其他问题
// 删除成功返回1,否则0
extern int play_srv_deleteByID(int inputID);

//输入play_t以修改
// 修改成功返回1,否则0
extern int play_srv_modifyByPlay_t(play_t inputPlay_t);

extern void play_printAll();