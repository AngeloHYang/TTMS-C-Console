extern int Ticket_Perst_Insert(ticket_node_t* h);
extern int Ticket_Perst_FetchAll(int id, ticket_node_t* h);
extern int Ticket_Perst_FetchByID(schedule_node_t* h, ticket_node_t* p);
extern int Ticket_Perst_SearchByTId(ticket_node_t* p);
extern int Ticket_Perst_ModifyStatus(ticket_node_t* p);
extern int Ticket_Perst_ReturnModify(sale_node_t* p);