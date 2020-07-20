#include "GEL.cpp"
#include <math.h>
#include <random>
#include <vector>
#include "packet.cpp"
#include <queue>

using namespace std;

int length;
double time;
double mu = 1; // service rate
double lambda = 0.8; // rate
const int MAXBUFFER = 20; //can change the size
const int RANDOM_SEED = 500;

/*Initialize;
for (i = 0; i < 100000; i++){
1. get the first event from the GEL;
2. If the event is an arrival then process-arrival-event;
3. Otherwise it must be a departure event and hence
process-service-completion;
output-statistics; */

double negative_exponentially_distributed_time (double rate) {
  double u = rand() / (RAND_MAX + 1.);
  return ((-1/rate)*log(1-u));
}

int main() {
  srand(RANDOM_SEED);
  // Initialize values
  queue<packet> buffer;
  GEL list;
  length = 0;
  time = 0.0;
  int drop = 0;
  // Initialize pseudo-random number generator
  double inter_time = negative_exponentially_distributed_time(lambda);
  list.add(time + inter_time, true);
  vector<pair<double,int>> simulation{{0.0,0}}; // all (timestamp, current length) during the simulation
  
  for (int i = 0; i < 10000; i++) {
    auto tmp_ = list.remove();
    bool is_arrival = tmp_.first;
    double n_time = tmp_.second;
    if (is_arrival) {
      time = n_time;
      inter_time = negative_exponentially_distributed_time(lambda); //time beteween packet arrival
      double service_time = negative_exponentially_distributed_time(mu); //time for processing of packets
      list.add(time + inter_time, true); //schedule next arrival
      if (length == 0){
        list.add(time + service_time, false); //schedule current packet departure
        length = 1;
        simulation.emplace_back(time, length);
      }
      else { //length > 0
        if (buffer.size() < MAXBUFFER) { // if packet can enter
          buffer.emplace(service_time);
          length++;
          simulation.emplace_back(time, length);
        }
        else {
          drop++;
        }
      }
    }
    else {
      time = n_time;
      length--;
      simulation.emplace_back(time, length);
      if (length > 0) {
        packet temp = buffer.front();
        buffer.pop();
        list.add(time + temp.service_time, false); //schedule next departure event
      }
    }
  }
  
  cout << "drop number: " << drop << endl;
  
  // calcuate utilization
  double util_time = 0.0;
  // simulation are (timestamp,length) pairs
  for (int i = 1; i < simulation.size(); ++i) {
    if (simulation[i-1].second)
      util_time += simulation[i].first - simulation[i-1].first;
  }
  cout << "utilization: " << util_time / time << endl;

  // calculate mean queue length
  double total = 0.0;
  for (int i = 1; i < simulation.size(); ++i) {
    total += (simulation[i].first - simulation[i-1].first) * simulation[i-1].second;
  }
  cout << "mean queue length: " << total / time << endl;

  // uncomment to output simluation values as (timestamp, current length) pairs.
  //for (auto [a,b] : simulation)
  //  cout << a << " " << b << endl;
  return 0;
}


