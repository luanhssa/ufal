#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

Queue* createQueueAction();

Event* creatEvent(char action);

int isEmptyQueue(Queue* queue);

void insertEvent(Event* event,Queue* queue);

Event* removeEvent(Queue* queue);

void runEvent(Event* event,Game* jogo);

#endif // ACTION_H_INCLUDED
