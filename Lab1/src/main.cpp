#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

/* =======================
   Exceptions
   ======================= */

class ErrorRange {
public:
    double x;
    ErrorRange(double v) : x(v) {}
};

class ErrorNoFile {
public:
    string fname;
    ErrorNoFile(string s) : fname(s) {}
};

/* =======================
   Linear interpolation
   ======================= */

double interpolate(const string& filename, double x)
{
    if (x < -10 || x > 10)
        throw ErrorRange(x);

    ifstream in(filename);
    if (!in)
        throw ErrorNoFile(filename);

    double x0, y0, x1, y1;

    in >> x0 >> y0;

    while (in >> x1 >> y1)
    {
        if (x == x0) return y0;

        if (x0 < x && x < x1)
            return y0 + (y1 - y0) * (x - x0) / (x1 - x0);

        x0 = x1;
        y0 = y1;
    }

    return y0;
}

/* =======================
   T(x) and U(x)
   ======================= */

double T(double x)
{
    if (fabs(x) <= 1)
        return interpolate("dat_X_1_1.dat", x);

    if (x < -1)
        return interpolate("dat_X1_00.dat", -1.0 / x);

    return interpolate("dat_X00_1.dat", -1.0 / x);
}

double U(double x)
{
    return T(x);   // аналогічна логіка (за умовою використовуються ті ж файли)
}

/* =======================
   Algorithm 5 (fallback)
   ======================= */

double fun5(double x, double y, double z)
{
    return 4.349 * x * z + 23.23 * y - 2.348 * x * y * z;
}

/* =======================
   Forward declarations
   ======================= */

double Rrz(double, double, double);
double Krn(double, double, double);

/* =======================
   Srz
   ======================= */

double Srz(double x, double y, double z)
{
    if (x > y)
        return T(x) + U(z) - T(y);
    else
        return T(y) + U(y) - U(z);
}

/* =======================
   Srs
   ======================= */

double Srs(double x, double y, double z)
{
    if (z > y && z * z + x * y > 0)
        return Srz(x,y,z) + y * sqrt(z*z + x*y);

    if (z <= y && x*x + z*y > 0)
        return y + Srz(z,x,y) * sqrt(x*x + z*y);

    return fun5(x,y,z);
}

/* =======================
   Qrz
   ======================= */

double Qrz(double x, double y)
{
    if (fabs(x) < 1)
        return x * Srs(x,y,x);

    return y * Srs(y,x,y);
}

/* =======================
   Rrz (Algorithm 1)
   ======================= */

double Rrz(double x, double y, double z)
{
    if (x > y)
        return x * y * Qrz(y,z) - x;

    return y * z * Qrz(x,y) + y;
}

/* =======================
   Krn
   ======================= */

double Krn(double x, double y, double z)
{
    return 73.1389 * Rrz(x,y,z)
         + 14.838  * Rrz(x-z, z, y);
}

/* =======================
   FUN (Algorithm 1)
   ======================= */

double fun(double x, double y, double z)
{
    return x * Krn(x,y,z)
         + y * Krn(x,z,y)
         - z * Krn(x,z,y);
}

/* =======================
   MAIN
   ======================= */

int main()
{
    double x,y,z;

    cout << "Input x y z: ";
    cin >> x >> y >> z;

    try
    {
        double f = fun(x,y,z);
        cout << "fun(x,y,z) = " << f << endl;
    }
    catch(ErrorRange& e)
    {
        cout << "Range error. x=" << e.x << endl;
        cout << "Using Algorithm 5..." << endl;
        cout << "fun = " << fun5(x,y,z) << endl;
    }
    catch(ErrorNoFile& e)
    {
        cout << "File not found: " << e.fname << endl;
        cout << "Using Algorithm 5..." << endl;
        cout << "fun = " << fun5(x,y,z) << endl;
    }
    catch(...)
    {
        cout << "Unknown error. Using Algorithm 5..." << endl;
        cout << "fun = " << fun5(x,y,z) << endl;
    }

    return 0;
}
