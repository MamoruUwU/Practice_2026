#include "Ants.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

using namespace std;

/* =========================
   ANT BASE CLASS
   ========================= */

Ant::Ant(const string& name) : name(name) {}

Ant::~Ant() {}

void Ant::run() {
    while (running) {
        moveStep();
        this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
    }
}

/* =========================
   WORKER ANT
   ========================= */

WorkerAnt::WorkerAnt(const string& name, int x, int y)
    : Ant(name),
      x(x), y(y),
      startX(x), startY(y),
      goingToCorner(true) {}

void WorkerAnt::moveStep() {

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

    lock_guard<mutex> lock(printMutex);
    cout << name << " (worker) x=" << x << " y=" << y << endl;
}

/* =========================
   WARRIOR ANT
   ========================= */

WarriorAnt::WarriorAnt(const string& name, int cx, int cy, int r)
    : Ant(name),
      angle(0.0),
      centerX(cx),
      centerY(cy),
      radius(r) {}

void WarriorAnt::moveStep() {

    int x = centerX + static_cast<int>(radius * cos(angle));
    int y = centerY + static_cast<int>(radius * sin(angle));

    angle += 0.1 * SPEED;

    lock_guard<mutex> lock(printMutex);
    cout << name << " (warrior) x=" << x << " y=" << y << endl;
}
