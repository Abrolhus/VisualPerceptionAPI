#include "CartesianCoord.h"
#include "RelativeCoord.h"
#include "RobotDefs.h"
#include <cmath>
#include <iostream>

using namespace std;

CartesianCoord::CartesianCoord()
{
    this->z = 0;
    this->y = 0;
    this->z = 0;
}

CartesianCoord::CartesianCoord(const CartesianCoord &coord)
{
    this->x = coord.x;
    this->y = coord.y;
    this->z = coord.z;
}

CartesianCoord::CartesianCoord(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float CartesianCoord::getX()
{
    return x;
}

float CartesianCoord::getY()
{
    return y;
}

float CartesianCoord::getZ()
{
    return z;
}

void CartesianCoord::setX(float x)
{
    this->x = x;
}

void CartesianCoord::setY(float y)
{
    this->y = y;
}

void CartesianCoord::setZ(float z)
{
    this->z = z;
}

float CartesianCoord::norm()
{
    return sqrt(x*x + y*y + z*z);
}

float CartesianCoord::distance(const CartesianCoord &other)
{
    float x = this->x - other.x;
    float y = this->y - other.y;
    float z = this->z - other.z;
    return sqrt(x*x + y*y + z*z);
}

float CartesianCoord::angle()
{
    return atan2(y, x);
}


void CartesianCoord::toRelative(float *distance, float *angle)
{
    
}

void CartesianCoord::toRelative(RelativeCoord &coord)
{

}