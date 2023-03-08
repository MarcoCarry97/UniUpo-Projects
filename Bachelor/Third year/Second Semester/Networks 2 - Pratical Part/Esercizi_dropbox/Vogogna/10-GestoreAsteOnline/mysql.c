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

	if (!mysql_real_connect(conn, SERVER, USERNAME, PASSWORD, "10035843", 0, NULL, 0))
		finish_with_error(conn);

	/*
	if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS ebay_like_database"))
		finish_with_error(conn);
	
	if (mysql_query(conn, "USE 10035843")) //USE ebay_like_database
		finish_with_error(conn);
	*/

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

	if (!mysql_real_connect(conn, SERVER, USERNAME, PASSWORD, "10035843", 0, NULL, 0))
		finish_with_error(conn);

	/*
	if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS ebay_like_database"))
		finish_with_error(conn);
	
	if (mysql_query(conn, "USE 10035843")) //USE ebay_like_database
		finish_with_error(conn);
	*/

	if (mysql_query(conn,
			"CREATE TABLE IF NOT EXISTS `items` ( `id` int(11) NOT NULL AUTO_INCREMENT,`name` text NOT NULL,`start_date` date NOT NULL,`end_date` date NOT NULL,`seller_id` int(11) NOT NULL,`actual_price` int(11) NOT NULL,`actual_winning_user` int(11) NOT NULL, PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;"))
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

	if (!mysql_real_connect(conn, SERVER, USERNAME, PASSWORD, "10035843", 0, NULL, 0))
		finish_with_error(conn);

	/*
	if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS ebay_like_database"))
		finish_with_error(conn);
	
	if (mysql_query(conn, "USE 10035843")) //USE ebay_like_database
		finish_with_error(conn);
	*/

	if (mysql_query(conn,
			"CREATE TABLE IF NOT EXISTS `bids` ( `user_id` int(11) NOT NULL, `item_id` int(11) NOT NULL, `bid` int(11) NOT NULL, `date` date NOT NULL, PRIMARY KEY (`user_id`, `item_id`, `bid`) ) ENGINE=InnoDB DEFAULT CHARSET=latin1;"))
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
			"10035843", 0, NULL, 0)) //ebay_like_database
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
				//printf("%s ", row[i] ? row[i] : "NULL");
			}
			if (!strcat(result_string, "\n"))
				err_msg("Error writing retrieved data");
			//printf("\n");
		}

	mysql_free_result(result);
	mysql_close(conn);

	return num_rows;
}

int check_item_bid(int client_id, int item_id, int price, char result_string[]) {
	MYSQL *conn = NULL;
	MYSQL_RES *result = NULL;
	char query[MAXLINE], conv[10];
	/*if (!strcpy(result_string, ''))
	 err_msg("Error writing retrieved data");*/

	conn = mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn, SERVER, USERNAME, PASSWORD,
			"10035843", 0, NULL, 0)) //ebay_like_database
		finish_with_error(conn);

	memset(query, '\0', MAXLINE);
	/* SELECT * FROM items WHERE id = 'item_id' */
	if (!strcpy(query, "SELECT * FROM items WHERE id = '"))
		return -1;
	memset(conv, '\0', sizeof(conv));
	sprintf(conv, "%d", item_id);
	if (!strcat(query, conv))
		return -1;
	if (!strcat(query, "' AND end_date > NOW() LIMIT 1"))
		return -1;

	/* send SQL query */
	if (mysql_query(conn, query))
		finish_with_error(conn);

	printf("QUERY: %s\n", query);

	result = mysql_store_result(conn);

	if (!result)
		finish_with_error(conn);

	MYSQL_ROW row;

	int num_rows = mysql_num_rows(result);

	if (num_rows >= 1) {
		if ((row = mysql_fetch_row(result))) {
			if (atoi(row[SELLER_ID_ROW]) != client_id) {
				if (atoi(row[ACTUAL_WINNING_USER_ROW]) != client_id) {
					if (atoi(row[ACTUAL_PRICE_ROW]) < price) {
						// Inserting the data in the bid table and updating the actual winning user and the actual price in the items table
						memset(query, '\0', MAXLINE);
						if (!strcpy(query,
								"INSERT INTO bids (user_id, item_id, bid, date) VALUES ('"))
							return -1;
						memset(conv, '\0', sizeof(conv));
						sprintf(conv, "%d", client_id);
						if (!strcat(query, conv))
							return -1;
						if (!strcat(query, "', '"))
							return -1;
						memset(conv, '\0', sizeof(conv));
						sprintf(conv, "%d", item_id);
						if (!strcat(query, conv))
							return -1;
						if (!strcat(query, "', '"))
							return -1;
						memset(conv, '\0', sizeof(conv));
						sprintf(conv, "%d", price);
						if (!strcat(query, conv))
							return -1;
						if (!strcat(query, "', NOW())"))
							return -1;

						printf("QUERY: %s\n", query);

						/* send SQL query */
						if (mysql_query(conn, query))
							finish_with_error(conn);

						// Updating the items table
						memset(query, '\0', MAXLINE);
						if (!strcpy(query, "UPDATE items SET actual_price = '"))
							return -1;
						memset(conv, '\0', sizeof(conv));
						sprintf(conv, "%d", price);
						if (!strcat(query, conv))
							return -1;
						if (!strcat(query, "', actual_winning_user = '"))
							return -1;
						memset(conv, '\0', sizeof(conv));
						sprintf(conv, "%d", client_id);
						if (!strcat(query, conv))
							return -1;
						if (!strcat(query, "' WHERE id = '"))
							return -1;
						memset(conv, '\0', sizeof(conv));
						sprintf(conv, "%d", item_id);
						if (!strcat(query, conv))
							return -1;
						if (!strcat(query, "'"))
							return -1;

						printf("QUERY: %s\n", query);

						/* send SQL query */
						if (mysql_query(conn, query))
							finish_with_error(conn);

						// Sending back the positive response to the bidding client
						if (!strcpy(result_string,
								"Thanks for your bid. You are now winning the item named '"))
							return -1;
						if (!strcat(result_string, row[NAME_ROW]))
							return -1;
						if (!strcat(result_string, "' with a bid of "))
							return -1;
						memset(conv, '\0', sizeof(conv));
						sprintf(conv, "%d", price);
						if (!strcat(result_string, conv))
							return -1;
						if (!strcat(result_string, ".\n"))
							return -1;
						if (!strcat(result_string, MENU))
							return -1;

						mysql_free_result(result);
						/* close connection */
						mysql_close(conn);
						return 0;
					} else {
						// The bid is too low. Sending back the actual bidding price
						if (!strcpy(result_string,
								"Sorry but the actual winning price is "))
							return -1;
						if (!strcat(result_string, row[ACTUAL_PRICE_ROW]))
							return -1;
						if (!strcat(result_string,
								".\n Try to bid the item again with an higher offer\n"))
							return -1;
						if (!strcat(result_string, MENU))
							return -1;

						mysql_free_result(result);
						/* close connection */
						mysql_close(conn);
						return 0;
					}
				} else {
					// The winning user is trying to bid again the item
					if (!strcpy(result_string,
							"You are already winning this item with a bid of "))
						return -1;
					if (!strcat(result_string, row[ACTUAL_PRICE_ROW]))
						return -1;
					if (!strcat(result_string, ".\n"))
						return -1;
					if (!strcat(result_string, MENU))
						return -1;

					mysql_free_result(result);
					/* close connection */
					mysql_close(conn);
					return 0;
				}
			} else {
				// the bidder and the seller are the same person
				if (!strcpy(result_string,
						"The seller can't bid his own item\n"))
					return -1;
				if (!strcat(result_string, MENU))
					return -1;

				mysql_free_result(result);
				/* close connection */
				mysql_close(conn);
				return 0;
			}
		}

	} else {
		// Received wrong id
		if (!strcpy(result_string,
				"The item with that id doesn't exists, or you made a bid past the end time\n"))
			return -1;
		if (!strcat(result_string, MENU))
			return -1;

		mysql_free_result(result);
		/* close connection */
		mysql_close(conn);
		return 0;
	}

	// should never get here
	return -1;
}

int insert_into_db(char query[]) {
	MYSQL *conn = NULL;

	conn = mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn, SERVER, USERNAME, PASSWORD,
			"10035843", 0, NULL, 0)) //ebay_like_database
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
			"10035843", 0, NULL, 0)) //ebay_like_database
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
			"10035843", 0, NULL, 0)) //ebay_like_database
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
