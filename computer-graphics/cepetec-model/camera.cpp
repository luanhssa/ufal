#include "camera.h"

Camera::Camera()
{
    MOVESPEED = 0.05f;
    CAMERASPEED = 0.001f;

    this->eye = Vec3(1.5f, 2.0f, -2.0f);
    this->view = Vec3(2.2f, 1.5f, 0.0f);
    this->up = Vec3(0.0f, 1.0f, 0.0f);
}

void Camera::moveCamera(int direction)
{
    GLdouble speed = direction * MOVESPEED;
    Vec3 aux = Vec3(0.0f, 0.0f, 0.0f);
    aux = view - eye;


    eye.x  = eye.x  + aux.x * speed;
    eye.z  = eye.z  + aux.z * speed;
    view.x = view.x + aux.x * speed;
    view.z = view.z + aux.z * speed;
}

void Camera::rotateView(GLdouble speed)
{
    Vec3 aux = Vec3(0.0f, 0.0f, 0.0f);
    aux = view - eye;

    view.x = (float)(eye.x + cos(speed)*aux.x - sin(speed)*aux.z);
    view.z = (float)(eye.z + sin(speed)*aux.x + cos(speed)*aux.z);
}

void Camera::moveMouse(int x, int y, int width, int height)
{
    //POINT mousePos;
    int mid_x = width  >> 1;
    int mid_y = height >> 1;
    float angle_y  = 0.0f;
    float angle_z  = 0.0f;

    //GetCursorPos(&mousePos);

    if( (x == mid_x) && (y == mid_y) ) return;

    //SetCursorPos(mid_x, mid_y);

    // Get the direction from the mouse cursor, set a resonable maneuvering speed
    angle_y = (float)( (mid_x - x) ) / 10000;
    angle_z = (float)( (mid_y - y) ) / 10;

    // The higher the value is the faster the camera looks around.
    view.y += angle_z * 0.001;

    // limit the rotation around the x-axis
    int limit = 10000;
    if((view.y - eye.y) > limit)  view.y = eye.y + limit;
    if((view.y - eye.y) < -limit)  view.y = eye.y - limit;

    rotateView(-angle_y); // Rotate
}

void Camera::moveSideways(int direction)
{
    GLdouble speed = direction * MOVESPEED;
    Vec3 aux = Vec3(0.0f, 0.0f, 0.0f);
    aux = view - eye;
    Vec3 ortho = Vec3(0.0f, 0.0f, 0.0f);
    ortho.x = -aux.z;
    ortho.y = aux.y;
    ortho.z = aux.x;

    eye.x  = eye.x  + ortho.x * speed;
    eye.z  = eye.z  + ortho.z * speed;
    view.x = view.x + ortho.x * speed;
    view.z = view.z + ortho.z * speed;
}

void Camera::moveUp(int direction)
{
    GLdouble speed = direction * MOVESPEED;
    GLdouble aux_y = view.y - eye.y;


    eye.y  = eye.y  + aux_y * speed;
    view.y = view.y + aux_y * speed;
}
