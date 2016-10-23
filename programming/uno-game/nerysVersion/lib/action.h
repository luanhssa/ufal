#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

Queue* createQueueAction();

Event* creatEvent(char action);

int isEmptyQueue(Queue* queue);

void insertEvent(Event* event,Queue* queue);

Event* removeEvent(Queue* queue);



#endif // ACTION_H_INCLUDED
