#ifndef _ROBOT_DEFS_H_
#define _ROBOT_DEFS_H_

#include "Math.h"

#define ROBOT_HEIGHT 0.51f

#define H_FOV Deg2Rad(60.97f)
#define V_FOV Deg2Rad(47.64f)

#define H_DOF Deg2Rad(80.0f)
#define V_DOF Deg2Rad(80.00f)

#define CAM_OFSET_ANGLE Deg2Rad(39.7f)

#define CAM_W 320
#define CAM_H 240

// #define CAM_W 640
// #define CAM_H 480

#define CAM_W_2 (CAM_W/2)
#define CAM_H_2 (CAM_H/2)

#define CAM_W_4 (CAM_W/4)
#define CAM_H_4 (CAM_H/4)

#define CAM_BALL_W CAM_W
#define CAM_BALL_H CAM_H

#endif
