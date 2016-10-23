//Doubly Linked List

typedef struct node {
	int id;
	Node *prev;
	NOde *next;
}Node;

Node* removeNode(Node* list, int id) {
	Node* new = (Node*) malloc(sizeof(Node));
	new = list;
	while(new->next!=NULL) {
		if(new->prev == NULL && new->id == id) {
			if(new->next!=NULL){
				new->next->prev = NULL;
			}
			list = new;
			free(new);
			return list;
		}
		else if(new->id==id && new->next==NULL){
			new->prev->next = NULL;
			list = new;
			free(new);
			return list;
		}
		else if(new->id == id) {
			new->prev->next = new->next; 
			new->next->prev = new->prev;
			list = new;
			free(new);
			return list;
		}
		new = new->next;
	}
	return NULL;
} 
/*
			 \/
NULL<(-+)> <(-+)> <(-+)> <(-+)>NULL

*/
