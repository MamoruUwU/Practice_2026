#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

struct Row {
    double x, T, U;
};

/* ---------- Зчитування таблиці ---------- */
vector<Row> readTable(const string& filename) {
    ifstream file(filename);
    if (!file.is_open())
        throw runtime_error("File not found");

    vector<Row> table;
    Row r;
    while (file >> r.x >> r.T >> r.U)
        table.push_back(r);

    return table;
}

/* ---------- Лінійна інтерполяція ---------- */
double interpolate(double x, const vector<Row>& table, bool isT) {
    for (size_t i = 0; i + 1 < table.size(); ++i) {
        if (table[i].x <= x && x <= table[i + 1].x) {
            double x1 = table[i].x, x2 = table[i + 1].x;
            double y1 = isT ? table[i].T : table[i].U;
            double y2 = isT ? table[i + 1].T : table[i + 1].U;
            return y1 + (y2 - y1) * (x - x1) / (x2 - x1);
        }
    }
    throw runtime_error("Interpolation error");
}

/* ---------- T(x), U(x) ---------- */
double Tfunc(double x) {
    string file;
    if (fabs(x) <= 1)
        file = "dat_X_1_1.dat";
    else if (x < -1) {
        x = 1 / x;
        file = "dat_X00_1.dat";
    } else {
        x = 1 / x;
        file = "dat_X1_00.dat";
    }

    auto table = readTable(file);
    return interpolate(x, table, true);
}

double Ufunc(double x) {
    string file;
    if (fabs(x) <= 1)
        file = "dat_X_1_1.dat";
    else if (x < -1) {
        x = 1 / x;
        file = "dat_X00_1.dat";
    } else {
        x = 1 / x;
        file = "dat_X1_00.dat";
    }

    auto table = readTable(file);
    return interpolate(x, table, false);
}

/* ---------- Srz ---------- */
double Srz(double x, double y, double z) {
    if (x > y)
        return Tfunc(x) + Ufunc(z) - Tfunc(y);
    else
        return Tfunc(y) + Ufunc(y) - Ufunc(z);
}

/* ---------- Gold ---------- */
double Gold(double x, double y) {
    if (x > y && y != 0)
        return x / y;
    if (x < y && x != 0)
        return y / x;
    throw runtime_error("Gold error");
}

/* ---------- Glr ---------- */
double Glr(double x, double y) {
    double r = sqrt(x * x + y * y - 4);
    if (fabs(x) < 1)
        return x;
    if (fabs(x) >= 1 && fabs(y) < 1)
        return y;
    if (fabs(x) >= 1 && fabs(y) >= 1 && r > 0.1)
        return y * r;
    throw runtime_error("Glr error");
}

/* ---------- Grs ---------- */
double Grs(double x, double y) {
    return 0.1389 * Srz(x + y, Gold(x, y), Glr(x, x * y))
         + 1.8389 * Srz(x - y, Gold(y, x / 5), Glr(5 * x, x * y))
         + 0.83   * Srz(x - 0.9, Glr(y, x / 5), Gold(5 * y, y));
}

/* ---------- Алгоритм 1 ---------- */
double Algorithm1(double x, double y, double z) {
    return x * x * Grs(y, z)
         + y * y * Grs(x, z)
         + 0.33 * x * y * Grs(x, z);
}

/* ---------- Алгоритм 2 ---------- */
double Algorithm2(double x, double y, double z) {
    return x * (x + y)
         + y * (y + z)
         + z * (z + x);
}

/* ---------- Алгоритм 3 ---------- */
double Algorithm3(double x, double y, double z) {
    return 1.3498 * z + 2.2362 * y - 2.348 * x * y;
}

/* ---------- main ---------- */
int main() {
    double x, y, z;
    cin >> x >> y >> z;

    try {
        cout << "fun = " << Algorithm1(x, y, z) << endl;
    }
    catch (...) {
        try {
            cout << "fun = " << Algorithm2(x, y, z) << endl;
        }
        catch (...) {
            cout << "fun = " << Algorithm3(x, y, z) << endl;
        }
    }

    return 0;
}
