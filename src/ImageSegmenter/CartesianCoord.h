#ifndef _CARTESIAN_COORDS_H_
#define _CARTESIAN_COORDS_H_

class RelativeCoord;

class CartesianCoord
{
    private:
        float x, y, z;
    public:
        CartesianCoord();
        CartesianCoord(const CartesianCoord &coord);
        CartesianCoord(float x, float y, float z = 0);

        float getX();
        float getY();
        float getZ();

        void setX(float x);
        void setY(float y);
        void setZ(float z);
        
        float norm();
        float distance(const CartesianCoord &other);
        float angle();

        void toRelative(float *distance, float *angle);
        void toRelative(RelativeCoord &coord);
};

#endif
