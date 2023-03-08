#include <mysql/mysql.h>

// Insert mysql server address
#define SERVER "web.edu-al.unipmn.it"
// Insert mysql username here
#define USERNAME "10035843"
// Insert mysql password here
#define PASSWORD "10035843"

int create_users_database();
int create_items_database();
int create_bids_database();
int get_from_db(char query[], char result_string[]);
int check_item_bid(int client_id, int item_id, int price, char result_string[]);
int insert_into_db(char query[]);
int registrer_new_user(list_node *node);
int check_login(list_node *node);
void finish_with_error(MYSQL *conn);
