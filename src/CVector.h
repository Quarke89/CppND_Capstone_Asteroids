#include <cmath>
#include <iostream>

enum class VectorType
{
    XY,
    POLAR
};

class CVector
{
    public:
        CVector();
        CVector(double mag, double angle, VectorType type);
        void calculateProjection();
        void calculatePolar();

        double getXProjection() const;
        double getYProjection() const;
        double getMag() const;
        double getAngle() const;

        CVector operator+(const CVector &vec);

        friend std::ostream& operator<<(std::ostream &out, const CVector &vec);

    private:
        double _mag;
        double _angle;
        double _x;
        double _y;

};

