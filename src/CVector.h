#include <cmath>

class CVector
{
    public:
        CVector(double mag, double angle);
        void calculateProjection();

        double getXProjection();
        double getYProjection();

    private:
        double _mag;
        double _angle;
        double _x;
        double _y;

};

