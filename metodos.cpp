#include <cfloat>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

#define DAYS 10 // 0.04166

#define LINES 45
#define RESERVED 5

#define REGULAR_OPERATORS 31
#define SILVER_OPERATORS 3
#define GOLD_OPERATORS 2

/* ------------------------- CLASSES ------------------------- */
class phone_operator {
  // 0 regular 1 silver 2 gold
public:
  int type;
  double available_time;

  phone_operator(int type) {
    this->type = type;
    this->available_time = 0;
  }

  bool operator>(const phone_operator &right) const {
    return this->available_time < right.available_time;
  }

  bool operator<(const phone_operator &right) const {
    return this->available_time > right.available_time;
  }
};

class client {
  // 0 regular 1 silver 2 gold
public:
  int type;
  double dialing_time = 0;
  double waiting_in_line;
  double service_time;
  int operation;
  client(int type, double dialing_time) {
    this->type = type;
    this->dialing_time = dialing_time;
    this->waiting_in_line = 0;
    double r = (double)rand() / RAND_MAX;
    if (r < .16) {
      this->operation = 0;
    } else if (r < 76) {
      this->operation = 1;
    } else {
      this->operation = 2;
    }
  }

  client(const client &c) {
    this->type = c.type;
    this->dialing_time = c.dialing_time;
    this->waiting_in_line = c.waiting_in_line;
    this->service_time = c.service_time;
    this->operation = c.operation;
  }

  bool operator>(const client &right) const {
    if (this->type > right.type) {
      return true;
    } else if (this->type == right.type) {
      return this->dialing_time < right.dialing_time;
    } else {
      return false;
    }
  }

  bool operator<(const client &right) const {
    if (this->type < right.type) {
      return true;
    } else if (this->type == right.type) {
      return this->dialing_time > right.dialing_time;
    } else {
      return false;
    }
  }
};

/* ------------------------- FUNCTION DECLARATION ------------------------- */

double expDist(double);

client *nextClient(queue<client> *, queue<client> *, queue<client> *);

bool serve(client *, priority_queue<phone_operator> *,
           priority_queue<phone_operator> *, priority_queue<phone_operator> *,
           priority_queue<client> *);

double triangularDist(double *);

double uniformDist(double *);

double max(double, double);

/* ------------------------- MATRIX ------------------------- */

int arrival_rates[12][3] = {
    {0, 87, 89},   {1, 165, 243}, {2, 236, 221},  {3, 323, 180},
    {4, 277, 301}, {5, 440, 490}, {6, 269, 294},  {7, 342, 347},
    {8, 175, 240}, {9, 273, 269}, {10, 115, 145}, {11, 56, 69},
};

double service_times[3][3] = {
    {1.2, 3.75, 2.05},
    {2.25, 8.6, 2.95},
    {1.2, 5.8, 1.9},
};

double efficiency[3] = {1, 0.95, 0.88};
// double efficiency[3] = {100, 100, 1000};

double after_call_times[3][3] = {
    {0.05, 0.10},
    {0.5, 0.8},
    {0.4, 0.6},
};

/* ------------------------- FUNCTIONS ------------------------- */

double expDist(double lambda) {
  return (-1.0 / lambda) * log(1 - (double)rand() / RAND_MAX);
}

int main(int argc, char **argv) {
  srand(time(NULL));
  queue<client> regular_clients;
  queue<client> silver_clients;
  queue<client> gold_clients;
  priority_queue<client> waiting_line;

  priority_queue<phone_operator> regular_operators;
  priority_queue<phone_operator> silver_operators;
  priority_queue<phone_operator> gold_operators;
  // queue<client> waiting_regular_clients;
  // queue<client> waiting_silver_clients;
  // queue<client> waiting_gold_clients;
  vector<client> left;
  vector<client> busy;
  vector<client> done;

  double elapsed_time = 0;

  client latest_client(0, 0);
  long busy_regulars = 0;
  long busy_cardholders = 0;

  // for (int i = 0; i < atoi(argv[1]); i++){
  // srand(23456);
  while (elapsed_time < DAYS * 1440) {
    regular_clients.push(latest_client);
    double arrival_time =
        expDist(arrival_rates[(int)elapsed_time / 60 % 12][1]);
    elapsed_time += arrival_time * 60;
    latest_client = client(0, elapsed_time);
  }

  elapsed_time = 0;

  double type = (double)rand() / RAND_MAX;
  latest_client = client((type < 0.68) + 1, 0);

  while (elapsed_time < DAYS * 1440) {
    if (latest_client.type == 2) {
      silver_clients.push(latest_client);
    } else if (latest_client.type == 1) {
      gold_clients.push(latest_client);
    } else {
      cout << "Error" << endl;
    }

    double arrival_time =
        expDist(arrival_rates[(int)elapsed_time / 60 % 12][2]);
    elapsed_time += arrival_time * 60;
    type = (double)rand() / RAND_MAX;
    latest_client = client((type < 0.68) + 1, elapsed_time);
  }

  long regulars = regular_clients.size();
  long silvers = silver_clients.size();
  long golds = gold_clients.size();

  long cardholders = silvers + golds;

  elapsed_time = 0;

  cout << "Regular: " << regular_clients.size() << endl;
  cout << "Silver: " << silver_clients.size() << endl;
  cout << "Gold: " << gold_clients.size() << endl;

  for (int i = 0; i < REGULAR_OPERATORS; i++) {
    regular_operators.push(phone_operator(0));
  }

  for (int i = 0; i < SILVER_OPERATORS; i++) {
    silver_operators.push(phone_operator(1));
  }

  for (int i = 0; i < GOLD_OPERATORS; i++) {
    gold_operators.push(phone_operator(2));
  }
  client *next;

  // cout << "DEBUG" << endl;

  int r;

  while (
      (next = nextClient(&regular_clients, &silver_clients, &gold_clients))) {
    if (waiting_line.size() >= 45) {
      // std::cout << "-----------------------------" << '\n';
      // std::cout << waiting_line.size() << '\n';
      // std::cout << next->type << '\n';
      // std::cout << next->dialing_time << '\n';
      // std::cout << regular_operators.top().available_time << '\n';
      // std::cout << silver_operators.top().available_time << '\n';
      // std::cout << gold_operators.top().available_time << '\n';
    }
    if (!next->type && waiting_line.size() >= LINES) {
      busy.push_back(*next);
    } else if (next->type && waiting_line.size() >= LINES + RESERVED) {
      busy.push_back(*next);
    } else {
      waiting_line.push(*next);
      // std::cout << waiting_line.size() << '\n';
      r = (double)rand() / RAND_MAX;
      if (r < .33) {
        r = 0;
      } else if (r < .66) {
        r = 1;
      } else {
        r = 2;
      }
      elapsed_time += service_times[next->operation][r];
      client to_be_served = waiting_line.top();
      while (!waiting_line.empty() &&
             serve(&to_be_served, &regular_operators, &silver_operators,
                   &gold_operators, &waiting_line)) {
        // printf("serving client type: %ul\n", to_be_served.type);
        waiting_line.pop();
        done.push_back(to_be_served);
        if (waiting_line.empty())
          // printf("empty\n");
          break;
        to_be_served = waiting_line.top();
      }
    }
  }

  for (auto it = busy.begin(); it != busy.end(); it++) {
    if ((*it).type) {
      busy_cardholders++;
    } else {
      busy_regulars++;
    }
  }

  cout << "Busy regulars: " << busy_regulars << " "
       << 100.0 * busy_regulars / regulars << "%" << endl;
  cout << "Busy cardhodlers: " << busy_cardholders << " "
       << 100.0 * busy_cardholders / cardholders << "%" << endl;

  cout << "Done: " << done.size() << endl;
  cout << "Busy: " << busy.size() << endl;

  // gold_operators = priority_queue<phone_operator>();
  // silver_operators = priority_queue<phone_operator>();
  // regular_operators = priority_queue<phone_operator>();
  // waiting_line = priority_queue<client>();
  //
  // busy.clear();
  // done.clear();
  //
  // cout << regular_operators.size() << endl;
  // cout << gold_operators.size() << endl;
  // cout << silver_operators.size() << endl;
  // cout << regular_clients.size() << endl;
  // cout << silver_clients.size() << endl;
  // cout << gold_clients.size() << endl;
  // cout << waiting_line.size() << endl;
  // cout << busy.size() << endl;
  //
  // elapsed_time = 0;
  // busy_regulars = 0;
  // busy_cardholders = 0;
  // }

  return 0;
}

double max(double a, double b) { return a > b ? a : b; }

client *nextClient(queue<client> *regular, queue<client> *silver,
                   queue<client> *gold) {
  client *next = new client(0, DBL_MAX);
  client *d = next;

  queue<client> *clients[] = {regular, silver, gold};

  int list = -1;

  for (int i = 0; i < 3; i++) {
    if (!clients[i]->empty()) {
      if (clients[i]->front().dialing_time < next->dialing_time) {
        next = &clients[i]->front();
        list = i;
      }
    }
  }

  free(d);

  if (list != -1) {
    // client *c = new client(*next);
    clients[list]->pop();
    // cout << clients[list]->size() << endl;
    return next;
  }

  // cout << "No element to pop" << endl;

  return NULL;
}

bool serve(client *c, priority_queue<phone_operator> *regular,
           priority_queue<phone_operator> *silver,
           priority_queue<phone_operator> *gold,
           priority_queue<client> *waiting) {

  priority_queue<phone_operator> *ops[] = {regular, silver, gold};

  for (int i = c->type; i >= 0; i--) {
    double comp = c->dialing_time + c->waiting_in_line;
    if (ops[i]->top().available_time <= comp) {
      // cout << "Available: " << ops[i]->top().available_time << endl;
      // c->waiting_in_line =
      // cout << c->dialing_time << endl;
      phone_operator o = ops[i]->top();
      double service_time =
          triangularDist(service_times[c->operation]) * efficiency[i];
      double after_call = uniformDist(after_call_times[c->operation]);

      c->waiting_in_line = o.available_time - c->dialing_time;
      c->service_time = service_time;
      ops[i]->pop();
      o.available_time = o.available_time + service_time + after_call;
      // cout << "popping client with: " << c->dialing_time << "Type: " <<
      // c->type << endl; cout << "pushing operator with: " << o.available_time
      // << endl; cout << "gold size " << o.available_time << endl;

      ops[i]->push(o);
      return true;
    } else {

      waiting->pop();

      c->waiting_in_line = c->waiting_in_line + 5;

      waiting->push(*c);

      cout << "Operator available at " << ops[i]->top().available_time
           << " Cant attend client with dialing time: "
           << c->dialing_time + c->waiting_in_line << endl;
    }
  }

  return false;
}

double triangularDist(double *values) {
  // double a = 1.2, b = 3.75, c = 2.05;
  double a = values[0];
  double b = values[1];
  double c = values[2];
  double middle = (c - a) / (b - a);

  double u = (double)rand() / RAND_MAX;
  if (u < middle) {
    // return sqrt(u * (b - a) * (c - a)) + a;
    return a + sqrt(u * (b - a) * (c - a));
  } else {
    // return b - (u * (b - a) * (b - c))/2;
    return b - sqrt((1 - u) * (b - a) * (b - c));
  }
}

double uniformDist(double *values) {
  double a = values[0];
  double b = values[1];
  double u = (double)rand() / RAND_MAX;

  return u * (b - a) + a;
}