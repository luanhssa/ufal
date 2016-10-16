#ifndef LATIM_H
#define LATIM_H

#include <GL/gl.h>
#include <GL/glut.h>

#define PI 3.14159265f

typedef struct Object {
  GLdouble w, h, d;

  Object() {}	// constructor
  Object(GLdouble width, GLdouble height, GLdouble depth) {
    w = width;
    h = height;
    d = depth;
  }
}Object;

class LaTIMModel
{
public:
  LaTIMModel();
  void draw();
  void moveDoor(GLdouble lenght);
  int doorPos;
  GLdouble doorAngle;
  //texture variables
  GLuint texture_id[30];

private:
  /**
   * wall1: wall that contains the window or the door
   * wall2: wall that contains cabinets
   * deskArm: desk arm side
   * deskCen: desk centre side
   * nDeskL: new desk left side
   * nDeskR: new desk right side
   */
  Object wall1,
          wall2,
          deskArm,
          deskCen,
          nDeskR,
          nDeskL,
          deskDiv1,
          deskDiv2,
          cabinet1,
          cabinet2,
          door,
          computer1,
          window1,
          window2,
          blackboard,
          chair1,
          ac,
          keyboard;

  /**
   * desk_y: height of the desk from the floor
   */
  GLdouble desk_y;


  void cylinder3d(GLdouble radius, GLdouble width, bool bottom, bool top);
  void halfCylinder3d(GLdouble radius, GLdouble width, bool bottom, bool top);
  void solidCylinder(GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks);
  void hexahedron3d(GLdouble width, GLdouble height, GLdouble depth);
  void hexahedron3d(GLdouble width, GLdouble height, GLdouble depth, int* texture_ids);
  void drawBox(GLdouble size);
  void drawBox(GLdouble size, int* texture_ids);
  void rect3d(GLdouble p1_x, GLdouble p1_y, GLdouble p1_z,
                GLdouble p2_x, GLdouble p2_y, GLdouble p2_z,
                GLdouble p3_x, GLdouble p3_y, GLdouble p3_z,
                GLdouble p4_x, GLdouble p4_y, GLdouble p4_z, int texture_id);
  void drawDesk();
  void drawCabinet(GLdouble w, GLdouble h, GLdouble d);
  void drawDoor();
  void drawWalls();
  void drawCabinets();
  void drawDesks();
  void drawShelf();
  void drawWindow();
  void drawComputers();
  void drawCPU(GLdouble x, GLdouble y, GLdouble z);
  void drawMonitor(GLdouble x, GLdouble y, GLdouble z);
  void drawWhiteboard();
  void drawCeiling();
  void drawFloor();
  void drawLamp(GLdouble radius, GLdouble width);
  void drawLamps();
  void drawAC();
  void drawChairs();

};

#endif // LATIM_H
