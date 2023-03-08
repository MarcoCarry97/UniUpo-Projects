#include "basic.h"
#include "list.h"

/* Adding the element to the head of the list */
int add(list_node *el, list_node **l) {
	el->next = *l;
	/* Updating the head */
	*l = el;
	return 0;
}

int del(list_node *el, list_node **lptr) {
	/* If the list is not empty */
	if (*lptr) {
		/* If it is the first element in the list */
		if (*lptr == el) {
			(*lptr) = (*lptr)->next;
			free(el);
			return 0;
		}
		/* If it's in the list */
		list_node *l = (*lptr)->next, *last = (*lptr);
		while (l) {
			if (l == el) {
				last->next = l->next;
				free(el);
				return 0;
			}
			last = l;
			l = l->next;
		}
	}
	return -1;
}

int move(list_node **source, list_node **destination, list_node *node, int port) {
	/* Setting the port number if it a server, or 0 if it is a client */
	node->portNumber = port;
	list_node *source_list = *source;
	/* The element is the head of the list */
	if (source_list) {
		if (source_list == node) {
			(*source) = node->next;
			return add(node, destination);
		}
		/* The element is inside the list */
		else {
			list_node *last_source = source_list;
			source_list = source_list->next;
			while (source_list) {
				if (source_list == node) {
					last_source->next = source_list->next;
					return add(node, destination);
				}
				last_source = source_list;
				source_list = source_list->next;
			}
		}
	}
	return -1;
}

list_node *create_node(int server_fd, struct sockaddr_in svrAddr, int len,
		struct timeval addTime) {
	list_node *new;
	new = (list_node*) malloc(sizeof(list_node));
	new->server_fd = server_fd;
	new->svrAddr = svrAddr;
	new->len = len;
	new->addTime = addTime;
	new->add_info = NULL;
	new->next = NULL;
	return new;
}

int add_client_info(list_node *node) {
	if (!node->add_info) {
		node->add_info = (client_info*) malloc(sizeof(client_info));
	}
	node->add_info->logged = 0;
	memset(node->add_info->username, '\0', sizeof(node->add_info->username));
	memset(node->add_info->password, '\0', sizeof(node->add_info->password));
	return 0;
}
