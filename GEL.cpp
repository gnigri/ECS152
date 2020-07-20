#include <utility>
#include <iostream>
#include "Event.cpp"

using namespace std;

class GEL {
public:
  // adds a new event to the list in increasing order of time
  void add (double time, bool is_arrival) {
    //checks if is an empty list
    if (!head) {
      head = new event{time, is_arrival, NULL, NULL};
      return;
    }
    //checks if it should be the first event 
    if (head->time >= time) {
      head = new event{time, is_arrival, NULL, head};
      return;
    }
    event * p = head;
    //finds the appropiate place for the new event
    while (p->next && p->next->time < time){
      p = p->next;
    }
    //check if it is the last
    if (!p->next) {
      p->next = new event{time, is_arrival, p, NULL};
    }
    //insert event otherwise
    else {
      event *temp = p->next;
      p->next = new event{time, is_arrival, p, temp};
      temp->prev = p->next; 
    }
  }
  
  // remove the first event from the list
  pair<bool, double> remove() {
    //check if is an empty list
    if (!head) {
      cout << "EMPTY LIST!";
      return {false, 0.0};
    }
    //check if list only cointains one event
    if (!head->next) {
      bool is_arrival = head->is_arrival;
      double time = head->time;
      delete(head);
      head = NULL;
      return {is_arrival, time};
    }
    //remove event otherwise
    head->next->prev = NULL;
    event * tmp = head;
    head = head->next;
    bool is_arrival = tmp->is_arrival;
    double time = tmp->time;
    delete(tmp);
    return {is_arrival, time};
  }
private:
  event * head = NULL;
};