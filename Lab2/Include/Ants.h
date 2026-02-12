#ifndef ANT_H
#define ANT_H

#include <string>
#include <mutex>
#include <atomic>

extern std::mutex printMutex;
extern std::atomic<bool> running;

const int SPEED = 1;
const int DELAY_MS = 100;
const int RADIUS = 10;

/* =========================
   ABSTRACT BASE CLASS
   ========================= */
class Ant {
protected:
    std::string name;

public:
    Ant(const std::string& name);
    virtual ~Ant();

    void run();               // запуск потоку

protected:
    virtual void moveStep() = 0;  // поліморфізм
};

/* =========================
   WORKER ANT
   ========================= */
class WorkerAnt : public Ant {
private:
    int x, y;
    int startX, startY;
    bool goingToCorner;

public:
    WorkerAnt(const std::string& name, int x, int y);

protected:
    void moveStep() override;
};

/* =========================
   WARRIOR ANT
   ========================= */
class WarriorAnt : public Ant {
private:
    double angle;
    int centerX, centerY;
    int radius;

public:
    WarriorAnt(const std::string& name, int cx, int cy, int r);

protected:
    void moveStep() override;
};

#endif
