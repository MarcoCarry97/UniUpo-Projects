#include <mysql/mysql.h>

#define SERVER "localhost"
#define USERNAME "root"
#define PASSWORD "deeder4123"

int create_users_database();
int create_items_database();
int create_bids_database();
int get_from_db(char query[], char result_string[]);
int insert_into_db(char query[]);
int registrer_new_user(list_node *node);
int check_login(list_node *node);
void finish_with_error(MYSQL *conn);
