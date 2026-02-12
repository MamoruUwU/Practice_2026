#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include "Ants.h"

using namespace std;

/* =========================
   GLOBAL VARIABLES
   ========================= */

mutex printMutex;
atomic<bool> running(true);

/* =========================
              MAIN
   ========================= */

int main() {

    vector<unique_ptr<Ant>> ants;

    ants.push_back(make_unique<WorkerAnt>("Worker_1", 20, 10));
    ants.push_back(make_unique<WorkerAnt>("Worker_2", 40, 20));

    ants.push_back(make_unique<WarriorAnt>("Warrior_1", 50, 15, RADIUS));
    ants.push_back(make_unique<WarriorAnt>("Warrior_2", 70, 10, RADIUS));

    vector<thread> threads;

    for (auto& ant : ants) {
        threads.emplace_back(&Ant::run, ant.get());
    }

    // Робота 10 секунд
    this_thread::sleep_for(chrono::seconds(10));
    running = false;

    for (auto& t : threads) {
        t.join();
    }

    cout << "Simulation finished." << endl;

    return 0;
}
