/* 
 * File:   main.cpp
 * Author: piter cf16.eu
 *
 * Created on September 26, 2013, 5:52 AM
 */

#include <cstdlib>
#include <iostream>
using namespace std;

/*
 * 
 */
class Node{
public:
  char LastName[20] ;
  char FirstName[20] ;
  int IDnumber ;
  Node *Next ;

 Node();
 void printNode();
};

Node::Node(){

cout << "Enter ID number: " << endl;
cin >> IDnumber;
cout << "Enter last name: " << endl;
cin >> LastName;
cout << "Enter first name: " << endl;
cin >> FirstName;
Next=NULL;
}

void Node::printNode(){
cout << "ID number: " << IDnumber << endl;
cout << "Last name: "  << LastName <<endl;
cout << "First name: "  << FirstName << endl;
}


class LinkedList{

private:
static Node* list;
Node* createNode();
Node* searchLocation(int);

public:

LinkedList();
~LinkedList(){}

void InsertNode();
void SearchNode();
void PrintList();
void DeleteNode(int);

};
Node* LinkedList::list = NULL;

LinkedList::LinkedList(){
Node* list = NULL;
}

Node* LinkedList::createNode(){
Node *NewNode = new Node();
return NewNode;
}

void LinkedList::InsertNode(){
Node* insert = createNode();
if(list==NULL)list=insert;
else
    list->Next = insert;
}

void LinkedList::PrintList(){
Node* temp = list;
while (temp != NULL){
temp->printNode();
temp = temp->Next;
}
}


//#ifndef _BORDERS_COMMON_LOGGER_LOGGER_HH_INCLUDED
//#define _BORDERS_COMMON_LOGGER_LOGGER_HH_INCLUDED

#include "logger.h"

namespace {
  static borders::common::log::Logger* _global_logger = NULL;
}

namespace borders {

  namespace common {

    namespace log {
        


      inline bool is_global_instance_initialized() {
        return _global_logger != NULL;
      };

      inline Logger& get_global_instance() {
        if (_global_logger == NULL) 
            _global_logger = new Logger;
        return *_global_logger;
      };

    } // namespace log

  } // namespace common

} // namespace borders

#define LOG_INFO() (borders::common::log::get_global_instance())

#define LOG_START()
#define LOG_STOP() \
  if (borders::common::log::is_global_instance_initialized()) \
    delete &borders::common::log::get_global_instance(); \
  else \
    (void) 0;

int main(){

    LOG_INFO() << "Foo" << "Bar";
    LOG_STOP()
    LOG_INFO() << "Foo2" << "Bar2";
    
int num = 0;
    LinkedList list;

  int menu=0;

  cout << endl << "Choose a menu option." <<endl
   << "1. Insert node " << endl << "2. Delete node " << endl
   << "3. Print list" << endl << "4. Search a node & print info" << endl
   << "5. Quit program  " << endl;



     list.InsertNode();
     list.InsertNode();

    list.PrintList();


return 0;

  }

