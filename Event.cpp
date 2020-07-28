struct event {
  double time;
  bool is_arrival; // true if arrival, else is departure.
  event *prev;
  event *next;
};
