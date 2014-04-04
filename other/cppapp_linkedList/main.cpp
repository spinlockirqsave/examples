/* 
 * File:   main.cpp
 * Author: Piotr Gregor  piter@cf16.eu
 *
 * Created on October 6, 2013, 3:28 AM
 */

#include <iostream>
#include <stdio.h>
//#include <conio.h>
#include "linkedlist.h"
 
using namespace std;
 
void LinkedList::insert()
{
        Node *newNode = new Node;
        char ch;
        // Adding the Node to the list
        do
        {
                cout << "\nEnter the coefficient: " << endl;
                cin >> newNode->coef;
                cout << "Enter the exponent: " << endl;
                cin >> newNode->expo;
                newNode->next = NULL;
                size++;
                cout << "Continue? (Y/N): ";
                cin >> ch;
        }
        while (ch == 'y' || ch == 'Y');
}
//
int LinkedList::degree()
{
        Node *tmp = head;
        int val = tmp->expo;
        while (tmp->next != NULL)
        {
                if (tmp->expo <= val)
                        tmp = tmp->next;
                else
                {
                        val = tmp->expo;
                        tmp = tmp->next;
                }
        }
        return val;
}
//
int LinkedList::coefficient(int power)
{
        Node *tmp = head;
        while (tmp->next != NULL)
        {
                // Checks if it exists
                if (tmp->expo == power)
                        return tmp->coef;
                else
                        tmp = tmp->next;
        }
        cout << "The coefficient is not found.\n";
        return 0;
}
//
bool LinkedList::match(LinkedList *expr1, LinkedList *expr2)
{
        // Check if both expressions have a same length
        if (expr1->size != expr2->size)
        {
                cout << "The expressions do not match in length." << endl;
                return false;
        }
        else if (expr1->size == expr2->size)
        {
                // Both expressions are the same in length, but not equal
                while (*(expr1->head).coef && *(expr2->head).coef) {}
        }
}

int main() {
    LinkedList l, g, h;
    l.match(&g,&h);
    
    return 0;
}

