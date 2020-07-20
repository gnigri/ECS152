struct event {
  double time; // not sure the unitstalk about it next meeting
  bool is_arrival; // true if arrival, else is departure.
  event *prev;
  event *next;
};
