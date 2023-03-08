/* Simple C program that connects to MySQL Database server*/
#include "basic.h"
#include "list.h"
#include "mysql.h"

int create_users_database() {
	MYSQL *conn = NULL;

	conn = mysql_init(NULL);

	if (!conn) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		return -1;
	}

	if (!mysql_real_connect(conn, SERVER, USERNAME, PASSWORD, NULL, 0, NULL, 0))
		finish_with_error(conn);

	if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS ebay_like_database"))
		finish_with_error(conn);

	if (mysql_query(conn, "USE ebay_like_database"))
		finish_with_error(conn);

	if (mysql_query(conn,
			"CREATE TABLE IF NOT EXISTS users( `id` int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY, `username` varchar(100) NOT NULL, `password` varchar(100) NOT NULL)"))
		finish_with_error(conn);

	mysql_close(conn);
	return 0;
}

int create_items_database() {
	MYSQL *conn = NULL;

	conn = mysql_init(NULL);

	if (!conn) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		return -1;
	}

	if (!mysql_real_connect(conn, SERVER, USERNAME, PASSWORD, NULL, 0, NULL, 0))
		finish_with_error(conn);

	if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS ebay_like_database"))
		finish_with_error(conn);

	if (mysql_query(conn, "USE ebay_like_database"))
		finish_with_error(conn);

	if (mysql_query(conn,
			"CREATE TABLE IF NOT EXISTS `items` ( `id` int(11) NOT NULL AUTO_INCREMENT,`name` text NOT NULL,`start_date` date NOT NULL,`end_date` date NOT NULL,`seller_id` int(11) NOT NULL,`actual_price` decimal(10,0) NOT NULL,`actual_winning_user` int(11) NOT NULL, PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;"))
		finish_with_error(conn);

	mysql_close(conn);
	return 0;
}

int create_bids_database() {
	MYSQL *conn = NULL;

	conn = mysql_init(NULL);

	if (!conn) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		return -1;
	}

	if (!mysql_real_connect(conn, SERVER, USERNAME, PASSWORD, NULL, 0, NULL, 0))
		finish_with_error(conn);

	if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS ebay_like_database"))
		finish_with_error(conn);

	if (mysql_query(conn, "USE ebay_like_database"))
		finish_with_error(conn);

	if (mysql_query(conn,
			"CREATE TABLE IF NOT EXISTS `bids` ( `user_id` int(11) NOT NULL, `item_id` int(11) NOT NULL, `bid` decimal(10,0) NOT NULL, `date` date NOT NULL, PRIMARY KEY (`user_id`, `item_id`, `bid`) ) ENGINE=InnoDB DEFAULT CHARSET=latin1;"))
		finish_with_error(conn);

	mysql_close(conn);
	return 0;
}

int get_from_db(char query[], char result_string[]) {
	MYSQL *conn = NULL;
	MYSQL_RES *result = NULL;
	int i;
	/*if (!strcpy(result_string, ''))
	 err_msg("Error writing retrieved data");*/

	conn = mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn, SERVER, USERNAME, PASSWORD,
			"ebay_like_database", 0, NULL, 0))
		finish_with_error(conn);

	/* send SQL query */
	if (mysql_query(conn, query))
		finish_with_error(conn);

	printf("QUERY: %s\n", query);

	result = mysql_store_result(conn);

	if (!result)
		finish_with_error(conn);

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;
	MYSQL_FIELD *field;

	int num_rows = mysql_num_rows(result);

	if (num_rows >= 1)
		while ((row = mysql_fetch_row(result))) {
			for (i = 0; i < num_fields; i++) {
				if (i == 0) {
					while ((field = mysql_fetch_field(result))) {
						if (!strcat(result_string, strcat(field->name, "\t\t")))
							err_msg("Error writing retrieved data");
					}
					if (!strcat(result_string, "\n"))
						err_msg("Error writing retrieved data");
				}
				if (!strcat(result_string, row[i]))
					err_msg("Error writing retrieved data");
				if (!strcat(result_string, "\t\t"))
					err_msg("Error writing retrieved data");
				printf("%s ", row[i] ? row[i] : "NULL");
			}
			if (!strcat(result_string, "\n"))
				err_msg("Error writing retrieved data");
			printf("\n");
		}

	mysql_free_result(result);
	mysql_close(conn);

	return num_rows;
}

int insert_into_db(char query[]) {
	MYSQL *conn = NULL;

	conn = mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn, SERVER, USERNAME, PASSWORD,
			"ebay_like_database", 0, NULL, 0))
		finish_with_error(conn);

	printf("\nQUERY: %s\n", query);

	/* send SQL query */
	if (mysql_query(conn, query))
		finish_with_error(conn);

	mysql_close(conn);
	return 0;
}

int registrer_new_user(list_node *node) {
	MYSQL *conn = NULL;
	MYSQL_RES *result = NULL;
	char query[MAXLINE];

	conn = mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn, SERVER, USERNAME, PASSWORD,
			"ebay_like_database", 0, NULL, 0))
		finish_with_error(conn);

	memset(query, '\0', MAXLINE);
	strcpy(query, "SELECT * FROM users WHERE username = '");
	strcat(query, node->add_info->username);
	strcat(query, "'");

	/* send SQL query */
	if (mysql_query(conn, query))
		finish_with_error(conn);

	result = mysql_use_result(conn);

	if (!mysql_fetch_row(result)) {
		mysql_free_result(result);

		memset(query, '\0', MAXLINE);
		strcpy(query, "INSERT INTO users (username, password) VALUES ('");
		strcat(query, node->add_info->username);
		strcat(query, "', '");
		strcat(query, node->add_info->password);
		strcat(query, "')");

		/* send SQL query */
		if (mysql_query(conn, query))
			finish_with_error(conn);

		/* close connection */
		mysql_close(conn);
		return 0;
	}

	mysql_free_result(result);
	/* close connection */
	mysql_close(conn);
	return -1;
}

int check_login(list_node *node) {
	MYSQL *conn = NULL;
	MYSQL_RES *result = NULL;
	char query[MAXLINE];

	conn = mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn, SERVER, USERNAME, PASSWORD,
			"ebay_like_database", 0, NULL, 0))
		finish_with_error(conn);

	memset(query, '\0', MAXLINE);
	strcpy(query, "SELECT * FROM users WHERE username = '");
	strcat(query, node->add_info->username);
	strcat(query, "' AND password = '");
	strcat(query, node->add_info->password);
	strcat(query, "'");

	/* send SQL query */
	if (mysql_query(conn, query))
		finish_with_error(conn);

	result = mysql_use_result(conn);
	MYSQL_ROW row;

	/* The user exists and he entered the right password */
	if ((row = mysql_fetch_row(result))) {
		/* Assigning the id to the client */
		node->add_info->logged = (int) atoi(row[0]);

		mysql_free_result(result);
		/* close connection */
		mysql_close(conn);
		return 0;
	}

	/* The user doesn't exist or he inserted the wrong password */
	memset(node->add_info->username, '\0', sizeof(node->add_info->username));
	memset(node->add_info->password, '\0', sizeof(node->add_info->password));
	mysql_free_result(result);
	/* close connection */
	mysql_close(conn);
	return -1;
}

void finish_with_error(MYSQL *conn) {
	fprintf(stderr, "%s\n", mysql_error(conn));
	mysql_close(conn);
	exit(1);
}
