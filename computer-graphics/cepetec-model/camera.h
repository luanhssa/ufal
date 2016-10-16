#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <math.h>

// expanded 3D vector struct
typedef struct Vec3 {
    // 3D vector coordinates
    GLdouble x, y, z;

    Vec3() {}	// constructor
    Vec3(GLdouble new_x, GLdouble new_y, GLdouble new_z) {
        x = new_x;
        y = new_y;
        z = new_z;
    }
    // overload + operator so that we easier can add vectors
    Vec3 operator+(Vec3 nVector) {
        return Vec3(nVector.x+x, nVector.y+y, nVector.z+z);
    }
    // overload - operator that we easier can subtract vectors
    Vec3 operator-(Vec3 nVector) {
        return Vec3(x-nVector.x, y-nVector.y, z-nVector.z);
    }
    // overload * operator that we easier can multiply by scalars
    Vec3 operator*(GLdouble number) {
        return Vec3(x*number, y*number, z*number);
    }
    // overload / operator that we easier can divide by a scalar
    Vec3 operator/(GLdouble number) {
        return Vec3(x/number, y/number, z/number);
    }
}Vec3;

class Camera
{
public:
    GLdouble MOVESPEED;
    GLdouble CAMERASPEED;
    Vec3 eye, view, up;
    int oldMouse_x, oldMouse_y;

    Camera();
    void moveCamera(int direction);
    void rotateView(GLdouble speed);
    void moveMouse(int x, int y, int width, int height);
    void moveSideways(int direction);
    void moveForward(int direction);
    void moveUp(int direction);
};

#endif // CAMERA_H
