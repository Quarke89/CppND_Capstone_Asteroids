#include "CVector.h"
#include "constants.h"


CVector::CVector(double mag, double angle)
    : _mag(mag), _angle(angle)
{
    calculateProjection();
}

void CVector::calculateProjection()
{
    _x = _mag * std::cos(_angle/180 * AsteroidConstants::PI);
    _y = _mag * std::sin(_angle/180 * AsteroidConstants::PI);
}

double CVector::getXProjection()
{
    return _x;
}


double CVector::getYProjection()
{
    return _y;
}