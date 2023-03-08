/* *************************************************************************************** */
/* Definizione del tipo lista i cui elementi sono di tipo int
 * con le operazioni di inserzione in testa, estrazione dalla testa,  accesso all'elemento
 * in testa (primo),  costruzione della lista vuota (makeLista) e test se vuota (emptyL)   */
/* *************************************************************************************** */
typedef struct client_info {
	int logged;
	char username[100];
	char password[100];
} client_info;

typedef struct list {
	int server_fd;
	struct sockaddr_in svrAddr;
	int len;
	int portNumber; /* Only set if it is a server */
	struct timeval addTime;
	struct client_info *add_info; /* Only set if it is a client */
	struct list *next;
} list_node;

int add(list_node *el, list_node **l);
int del(list_node *el, list_node **lptr);
int move(list_node **source, list_node **destination, list_node *node, int port);
list_node *create_node(int server_fd, struct sockaddr_in svrAddr, int len,
		struct timeval addTime);
int add_client_info(list_node *node);
