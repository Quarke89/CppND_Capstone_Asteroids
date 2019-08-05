#include "CVector.h"
#include "constants.h"
#include <cmath>

CVector::CVector()
    :CVector(0,0,VectorType::POLAR)
{}

CVector::CVector(double a1, double a2, VectorType type)
{
    if(type == VectorType::POLAR){
        _mag = a1;
        _angle = a2;
        calculateProjection();
    }
    else{
        _x = a1;
        _y = a2;
        calculatePolar();
    }
    
}

void CVector::calculateProjection()
{
    _x = _mag * std::cos(_angle/180 * AsteroidConstants::PI);
    _y = _mag * std::sin(_angle/180 * AsteroidConstants::PI);
}

void CVector::calculatePolar()
{
    _mag = std::sqrt(std::pow(_x, 2) + std::pow(_y, 2));
    _angle = std::atan2(_y, _x)/AsteroidConstants::PI * 180;
}

double CVector::getXProjection() const
{
    return _x;
}


double CVector::getYProjection() const
{
    return _y;
}

double CVector::getMag() const
{
    return _mag;
}

double CVector::getAngle() const
{
    return _angle;
}
    
CVector CVector::operator+(const CVector &vec)
{
    double xProj = _x + vec.getXProjection();
    double yProj = _y + vec.getYProjection();
    
    return CVector(xProj, yProj, VectorType::XY);

}

std::ostream& operator<<(std::ostream &out, const CVector &vec)
{
    out << "mag: " << vec.getMag() << ", angle: " << vec.getAngle() << " (" << vec.getXProjection() << ", " << vec.getYProjection() << ")";
    return out;
}