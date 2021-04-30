#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct planet {
  int id;
  vector<int> tanks;
  vector<int> neigh;
  bool visited;
};

void solve();
bool routeAvailable(int p);

int n_planets;
int fuel;
int n_tanks;

set<int> visited;

std::vector<int> tanks;

std::vector<planet> planets;

std::ifstream in("input.txt");
std::ofstream out("output.txt");

int main() {
  in >> n_planets >> fuel >> n_tanks;

  for (int i = 0; i < n_tanks; ++i) {
    int capacity;

    in >> capacity;

    tanks.push_back(capacity);
  }

  planets.resize(n_planets);

  for (int i = 0; i < n_planets; ++i) {
    int id;
    in >> id;
    planets[i].id = id;
    planets[i].neigh.resize(n_planets);
    for (int j = 0; j < n_tanks; ++j) {
      int waste;
      in >> waste;
      planets[i].tanks.push_back(waste);
    }
  }
  for (planet p : planets) {
    p.neigh.resize(n_planets);
  }
  int src;
  int dst;
  int fuel_consumed;

  while (in >> src >> dst >> fuel_consumed) {
    planets[src].neigh[dst] = fuel_consumed;
    planets[dst].neigh[src] = fuel_consumed;
  }

  planets[0].visited = true;
  std::vector<bool> visited(n_planets, false);
  solve();

  return 0;
}

void solve() {
  planet position = planets[0];
  visited.insert(0);

  while (fuel > 0) {
    for (int i = 0; i < n_tanks; ++i) {
      int waste_taken =
          tanks[i] > position.tanks[i] ? position.tanks[i] : tanks[i];
      tanks[i] -= waste_taken;

      out << waste_taken << " " << i << " ";
    }

    planet highest_reward_planet;
    highest_reward_planet.id = -1;
    int trip_cost = INT32_MAX;
    int highest_reward = -1;
    for (int i = 0; i < n_planets; ++i) {
      int total_reward = 0;

      if (position.neigh[i] > 0 && visited.find(i) == visited.end()) {
        for (int j = 0; j < n_tanks; j++) {
          total_reward += planets[position.neigh[i]].tanks[j];
        }
        if (total_reward > highest_reward &&
            routeAvailable(position.neigh[i])) {
          highest_reward = total_reward;
          highest_reward_planet = planets[i];
          trip_cost = position.neigh[i];
        }
      }
    }

    out << highest_reward_planet.id << endl;

    position = highest_reward_planet;
    fuel -= trip_cost;
    visited.insert(position.id);
    cout << fuel << endl;
    if (position.id == -1) {
      return;
    }
  }
}

bool routeAvailable(int p) {
  for (int neighbour : planets[p].neigh) {
    if (visited.find(neighbour) == visited.end()) {
      return true;
    }
  }

  return false;
}

bool route5Available(int p) {}