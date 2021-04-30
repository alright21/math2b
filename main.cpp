#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct planet {
  int id;
  vector<int> tanks;
  vector<int> neigh;
  vector<int> fuel;
};

int main() {
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");

  int n_planets;
  int fuel;
  int n_tanks;

  in >> n_planets >> fuel >> n_tanks;

  std::vector<int> tanks;

  for (int i = 0; i < n_tanks; ++i) {
    int capacity;

    in >> capacity;

    tanks.push_back(capacity);
  }

  std::vector<planet> planets(n_planets);

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

  while (in >> src >> dst >> fuel) {
    planets[src].neigh[dst] = fuel;
    planets[dst].neigh[src] = fuel;
  }
  return 0;
}
