#ifndef _MATH_H_
#define _MATH_H_

#define PI 3.141592653589793f
#define Deg2Rad(d) (d*0.017453293f)
#define Rad2Deg(r) (r*57.295779513f)
#define SIG(v) (v < 0 ? -1 : 1)

extern "C" float FixAngle(float rad);
extern "C" float FixAngled(float deg);

#endif