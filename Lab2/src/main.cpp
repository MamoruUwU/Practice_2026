#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <cmath>
#include <conio.h>

using namespace std;

// Constants
const int WIDTH = 100;
const int HEIGHT = 30;
const int SPEED = 1;
const int DELAY_MS = 100;
const int RADIUS = 10;

// Mutex for synchronized console output
mutex printMutex;

/* =========================
   WORKER ANT
   ========================= */
class WorkerAnt {
public:
    string name;
    int x, y;
    int startX, startY;
    bool goingToCorner;

    WorkerAnt(string name, int x, int y)
        : name(name), x(x), y(y),
          startX(x), startY(y),
          goingToCorner(true) {}

    void move() {
        while (true) {
            {
                lock_guard<mutex> lock(printMutex);
                cout << name << " (worker) x=" << x << " y=" << y << endl;
            }

            if (goingToCorner) {
                if (x > 0) x -= SPEED;
                if (y > 0) y -= SPEED;

                if (x == 0 && y == 0)
                    goingToCorner = false;
            } else {
                if (x < startX) x += SPEED;
                if (y < startY) y += SPEED;

                if (x == startX && y == startY)
                    goingToCorner = true;
            }

            this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
        }
    }
};

/* =========================
   WARRIOR ANT
   ========================= */
class WarriorAnt {
public:
    string name;
    double angle;
    int centerX, centerY;
    int radius;

    WarriorAnt(string name, int cx, int cy, int r)
        : name(name), angle(0.0),
          centerX(cx), centerY(cy), radius(r) {}

    void move() {
        while (true) {
            int x = centerX + static_cast<int>(radius * cos(angle));
            int y = centerY + static_cast<int>(radius * sin(angle));

            {
                lock_guard<mutex> lock(printMutex);
                cout << name << " (warrior) x=" << x << " y=" << y << endl;
            }

            angle += 0.1 * SPEED;

            this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
        }
    }
};

/* =========================
              main
   ========================= */
int main() {
    vector<WorkerAnt> workers = {
        WorkerAnt("Worker_1", 20, 10),
        WorkerAnt("Worker_2", 40, 20)
    };

    vector<WarriorAnt> warriors = {
        WarriorAnt("Warrior_1", 50, 15, RADIUS),
        WarriorAnt("Warrior_2", 70, 10, RADIUS)
    };

    vector<thread> threads;

    threads.emplace_back(&WorkerAnt::move, &workers[0]);
    threads.emplace_back(&WorkerAnt::move, &workers[1]);

    threads.emplace_back(&WarriorAnt::move, &warriors[0]);
    threads.emplace_back(&WarriorAnt::move, &warriors[1]);

    for (auto& t : threads) {
        t.join();
        
    }

    return 0;
}
