/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on January 30, 2014, 1:05 PM
 */

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm> 

template<typename T, typename Param>
class Task
{
 public:
   typedef void (T::*Func)(Param);

    T* object;
    Func func;
    Param param;
    int priority;

    Task(T& obj_, Func f_, Param p_, int pp)
         :object(&obj_), func(f_), param(p_),priority(pp) { }
    virtual ~Task() {}
    virtual void operator()() const { (object->*func)(param); }

    Task(const Task& obj)
     :object(obj.object), func(obj.func), param(obj.param),priority(obj.priority)
      {  
      }

    Task& operator=(const Task obj){
        object= obj.object; func = obj.func; param = obj.param;
        priority = obj.priority;            
        return *this;
     }
};

struct TaskCompare
{
   template<typename T, typename Param>
   bool operator()(const Task< T,Param > &t1, const Task< T,Param > &t2) const 
  {
    return t1.priority < t2.priority;       
   }
};


template<typename T, typename Param>
class taskQ
{
public:
    std::priority_queue<Task< T,Param >, std::vector<Task< T,Param > >,
                                              TaskCompare> queue;

    void addTask(T& t, void (T::*f)(Param), Param p_, int pri) {
    queue.push(Task< T,Param >( t, f, p_, pri));
     }

     void executeTask() {   
         while( !queue.empty()) {
             queue.top()();
             queue.pop();
            }

     }
};

typedef struct Param_t {           
    int prio;   
}Param_t;

class Core {
public:
    Core() {}
    void print(Param_t p) { std::cout<<p.prio;}
};


int main(int argc, char ** argv) {
  taskQ<Core,Param_t> t;
  Core *c = new Core();
  Param_t param;
  param.prio= 3;    
  t.addTask(*c,&Core::print, param,param.prio);
  Param_t param1;
  param1.prio= 1;        
  t.addTask(*c,&Core::print, param1,param1.prio);
  Param_t param2;
  param2.prio= 2;    
  t.addTask(*c,&Core::print, param2,param2.prio);
  Param_t param3;
  param3.prio = 4;
  t.addTask(*c,&Core::print, param3,param3.prio);
  t.executeTask();
  delete c;

  return 0;
 }

