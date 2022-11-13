#ifndef _RELATIVE_COORDS_H_
#define _RELATIVE_COORDS_H_

class CartesianCoord;

class RelativeCoord
{
    private:
        float distance, yaw, pitch;
    public:
        float x = 0.0f, y = 0.0f;
        RelativeCoord();
        RelativeCoord(const RelativeCoord &coord);
        RelativeCoord(float distance, float yaw, float pitch);

        float getDistance();
        float getYaw();
        float getPitch();

        void setDistance(float distance);
        void setYaw(float yaw);
        void setPitch(float pitch);

        void fromPixel(int w, int h, float headYaw = 0.0f, float headPitch = 0.0f, bool upper = false);   
        void toCartesian(float *x, float *y, float headYaw = 0.0f, float headPitch = 0.0f);
        void toCartesian(CartesianCoord &coord, float headYaw = 0.0f, float headPitch = 0.0f);
};

#endif
