/* 
 * File:   linkedlist.h
 * Author: Piotr Gregor  piter@cf16.eu
 *
 * Created on October 6, 2013, 3:28 AM
 */
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
 
class Node
{
public:
        int coef;
        int expo;
        Node *next;
        Node(int coef=0, int expo=0, Node *next=NULL)
        {
                this->coef = coef;
                this->expo = expo;
                this->next = next;
        }
};
//
class LinkedList
{
private:
        Node *head;
        int size;
public:
        LinkedList()
        {
                head = new Node(0, 0, NULL);
                head->coef = 0;
                head->expo = 0;
                head->next = NULL;
                size = 0;
        }
        int degree();
        int coefficient(int);
        bool match(LinkedList *, LinkedList*);
        void insert();
        LinkedList sum(LinkedList *, LinkedList *);
        LinkedList dot(LinkedList *, LinkedList *);
};LinkedList x, y, z;
#endif /* LINKEDLIST_H_ */

