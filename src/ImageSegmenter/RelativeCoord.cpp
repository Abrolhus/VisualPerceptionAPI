#include "RelativeCoord.h"
#include "CartesianCoord.h"
#include "RobotDefs.h"
#include <cmath>
#include <iostream>

using namespace std;

RelativeCoord::RelativeCoord()
{
    this->distance = 0;
    this->yaw = 0;
    this->pitch = 0;
    this->x = 0.0f;
    this->y = 0.0f;
}

RelativeCoord::RelativeCoord(const RelativeCoord &coord)
{
    this->distance = coord.distance;
    this->yaw = coord.yaw;
    this->pitch = coord.pitch;
}

RelativeCoord::RelativeCoord(float distance, float yaw, float pitch)
{
    this->distance = distance;
    this->yaw = yaw;
    this->pitch = pitch;
}

float RelativeCoord::getDistance()
{
    return distance;
}

float RelativeCoord::getYaw()
{
    return yaw;
}

float RelativeCoord::getPitch()
{
    return pitch;
}

void RelativeCoord::setDistance(float distance)
{
    this->distance = distance;
}

void RelativeCoord::setYaw(float yaw)
{
    this->yaw = yaw;
}

void RelativeCoord::setPitch(float pitch)
{
    this->pitch = pitch;
}

void RelativeCoord::fromPixel(int w, int h, float headYaw, float headPitch, bool upper)
{
    h = CAM_BALL_H - h;
    yaw = ((w / (float)CAM_BALL_W) - 0.5f) * H_FOV;
    pitch = -((h / (float)CAM_BALL_H) - 0.5f) * V_FOV;
    if(!upper)
        pitch += CAM_OFSET_ANGLE;

    yaw = yaw + headYaw;
    pitch = pitch + headPitch;

    // this->x = ROBOT_HEIGHT / tan(-pitch);
    // this->y = x*tan(-yaw);
    float dist = ROBOT_HEIGHT/ tan(-pitch);
    this->x = dist*cos(yaw);
    this->y = dist*sin(yaw);
    distance = sqrt(x*x + y*y);
}

void RelativeCoord::toCartesian(float *x, float *y, float headYaw, float headPitch)
{
    float forward = distance;
    if(distance > ROBOT_HEIGHT)
        forward = sqrt(distance*distance - ROBOT_HEIGHT*ROBOT_HEIGHT);
    *x = forward*cos(yaw + headYaw);
    *y = forward*sin(yaw + headYaw);
}

void RelativeCoord::toCartesian(CartesianCoord &coord, float headYaw, float headPitch)
{
    float forward = distance;
    if(distance > ROBOT_HEIGHT)
        forward = sqrt(distance*distance - ROBOT_HEIGHT*ROBOT_HEIGHT);
    coord.setX(forward*cos(yaw + headYaw));
    coord.setY(forward*sin(yaw + headYaw));
    coord.setZ(0);
}
