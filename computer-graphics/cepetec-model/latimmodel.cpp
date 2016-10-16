#include "latimmodel.h"
#include <math.h>
#include <iostream>

LaTIMModel::LaTIMModel() {
  doorPos = 1;
  doorAngle = 0.0f;
  desk_y = 0.7f;

  wall1 = Object(6.90f, 3.0f, 0.05f);
  wall2 = Object(7.80f, 3.0f, 0.05f);
  deskArm = Object(1.40f, 0.05f, 0.55f);
  deskCen = Object(1.40f, 0.05f, 0.55f);
  nDeskR = Object(4.16f, 0.05f, 0.55f);
  nDeskL = Object(1.63f, 0.05f, 0.55f);
  deskDiv1 = Object(deskArm.w*2 + 0.15f, 1.20f, 0.05f);
  deskDiv2 = Object(deskArm.d*4 + deskCen.w*2 + 0.05f, 1.20f, 0.05f);
  cabinet1 = Object(0.80f, 2.08f, 0.57f);
  cabinet2 = Object(1.0f, 2.20f, 0.57f);
  door = Object(1.0f, 2.20f, 0.03f);
  computer1 = Object();
  window1 = Object(0.575f, 1.15f, 0.05f);
  window2 = Object(0.575f, 0.575f, 0.05f);
  blackboard = Object(3.0f, 1.40f, 0.06f);
  chair1 = Object();
  ac = Object(0.90f, 0.30f, 0.15f);
  keyboard = Object(0.15f, 0.02f, 0.45f);
}

void LaTIMModel::draw() {
  glPushMatrix();
    //door
    drawDoor();
    //Walls
    drawWalls();
    //Cabinets
    drawCabinets();
    //Desks and Dividers
    drawDesks();
    //Shelfs (new desks)
    drawShelf();
    //Computers
    drawComputers();
    //Blackboard
    drawWhiteboard();
    //Ceiling
    drawCeiling();
    //Floor
    drawFloor();
    //Lamps
    drawLamps();
    //AC
    drawAC();
    //Chairs
    //drawChairs();
  glPopMatrix();
  /*
   * Chairs
   * Windows
   * Mouse
   */
}

void LaTIMModel::halfCylinder3d(GLdouble radius, GLdouble width, bool bottom, bool top) {
  GLdouble x              = 0.0f;
  GLdouble y              = 0.0f;
  GLdouble angle          = 0.0f;
  GLdouble angle_stepsize = 0.05f;

  if(bottom) {
      // Draw the circle on bottom of cylinder
    glBegin(GL_POLYGON);
    angle = 0.0;
    while( angle < PI ) {
      x = radius * sin(angle);
      y = radius * cos(angle);
      glVertex3f(x, y, 0.0f);
      angle = angle + angle_stepsize;
    }
    //glVertex3f(radius, 0.0, 0.0f);
    glEnd();
  }

  // Draw the tube
  glBegin(GL_QUAD_STRIP);
  angle = 0.0;
  while( angle < PI ) {
    x = radius * cos(angle);
    y = radius * sin(angle);
    glVertex3f(x, y, width);
    glVertex3f(x, y, 0.0);
    angle = angle + angle_stepsize;
  }
  //glVertex3f(radius, 0.0, width);
  //glVertex3f(radius, 0.0, 0.0);
  glEnd();

  if(top) {
    // Draw the circle on top of cylinder
    glBegin(GL_POLYGON);
    angle = 0.0;
    while( angle < PI ) {
      x = radius * cos(angle);
      y = radius * sin(angle);
      glVertex3f(x, y , width);
      angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, width);
    glEnd();
  }
}

void LaTIMModel::cylinder3d(GLdouble radius, GLdouble width, bool bottom, bool top) {
  GLdouble x              = 0.0f;
  GLdouble y              = 0.0f;
  GLdouble angle          = 0.0f;
  GLdouble angle_stepsize = 0.05f;

  if(bottom) {
    // Draw the circle on bottom of cylinder
    glBegin(GL_POLYGON);
    angle = 0.0;
    while( angle < 2*PI ) {
      x = radius * sin(angle);
      y = radius * cos(angle);
      glVertex3f(x, y, 0.0f);
      angle = angle + angle_stepsize;
    }
    //glVertex3f(radius, 0.0, 0.0f);
    glEnd();
  }

  // Draw the tube
  glBegin(GL_QUAD_STRIP);
  angle = 0.0;
  while( angle < 2*PI ) {
    x = radius * cos(angle);
    y = radius * sin(angle);
    glVertex3f(x, y, width);
    glVertex3f(x, y, 0.0);
    angle = angle + angle_stepsize;
  }
  glVertex3f(radius, 0.0, width);
  glVertex3f(radius, 0.0, 0.0);
  glEnd();

  if(top) {
    // Draw the circle on top of cylinder
    glBegin(GL_QUADS);
    angle = 0.0;
    while( angle < 2*PI ) {
      x = radius * cos(angle);
      y = radius * sin(angle);
      glVertex3f(x, y , width);
      angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, width);
    glEnd();
  }
}

void LaTIMModel::solidCylinder(GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks) {
  GLUquadricObj* quadric = gluNewQuadric();
  gluQuadricOrientation(quadric, GLU_INSIDE);
  gluQuadricTexture(quadric, GL_TRUE);

  glPushMatrix();
  gluCylinder(quadric, base, top, height, slices, stacks);
  glRotatef(180, 1,0,0);
  gluDisk(quadric, 0.0f, base, slices, 1);
  glRotatef(180, 1,0,0);
  glTranslatef(0.0f, 0.0f, height);
  gluDisk(quadric, 0.0f, top, slices, 1);
  glTranslatef(0.0f, 0.0f, -height);
  glPopMatrix();
}

void LaTIMModel::drawBox(GLdouble size, int *tex) {
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  for (i = 5; i >= 0; i--) {
    if(tex[i] >= 0) {
      glBindTexture(GL_TEXTURE_2D, texture_id[tex[i]]);
    }
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    if(i==1)
      glTexCoord2f(1.0f, 0.0f);
    else
      glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(&v[faces[i][0]][0]);
    if(i==1)
      glTexCoord2f(0.0f, 0.0f);
    else
      glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(&v[faces[i][1]][0]);
    if(i==1)
      glTexCoord2f(0.0f, 1.0f);
    else
      glTexCoord2f(1.0f, 1.0f);
    glVertex3fv(&v[faces[i][2]][0]);
    if(i==1)
      glTexCoord2f(1.0f, 1.0f);
    else
      glTexCoord2f(0.0f, 1.0f);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
    if(tex[i] >= 0) {
      glBindTexture(GL_TEXTURE_2D, 0);
    }
  }
}

void LaTIMModel::hexahedron3d(GLdouble w, GLdouble h, GLdouble d, int* id) {
  glPushMatrix();

  glTranslated(w/2, h/2, d/2); //centering the object
  glScalef(1.0f, h/w, d/w); //scaling to the actual size
  drawBox(w, id);

  glPopMatrix();
}

void LaTIMModel::hexahedron3d(GLdouble w, GLdouble h, GLdouble d) {
  glPushMatrix();

  glTranslated(w/2, h/2, d/2); //centering the object
  glScalef(1.0f, h/w, d/w); //scaling to the actual size
  glutSolidCube(w);

  glPopMatrix();
}

void LaTIMModel::rect3d(GLdouble p1_x, GLdouble p1_y, GLdouble p1_z,
                        GLdouble p2_x, GLdouble p2_y, GLdouble p2_z,
                        GLdouble p3_x, GLdouble p3_y, GLdouble p3_z,
                        GLdouble p4_x, GLdouble p4_y, GLdouble p4_z, int id) {
	if(id >= 0)
    glBindTexture(GL_TEXTURE_2D, texture_id[id]);
  glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(p1_x, p1_y, p1_z); //bottom left
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(p2_x, p2_y, p2_z); //bottom right
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(p3_x, p3_y, p3_z); //top right
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(p4_x, p4_y, p4_z); //top left
  glEnd();
  if(id >= 0)
    glBindTexture(GL_TEXTURE_2D, 0);
}

void LaTIMModel::drawDesk() {
  int texture[] = {4, 4, 4, 4, 4, 4};
  //right side
  hexahedron3d(deskArm.w, deskArm.h, deskArm.d, texture);
  glTranslated(0.02f, -desk_y, 0.0f);
  hexahedron3d(deskArm.h, desk_y, deskArm.d, texture);
  glTranslated(-0.02f, desk_y, 0.0f);
  //middle
  glTranslated(deskArm.w, 0.0f, -(deskCen.w));
  glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
  hexahedron3d(deskCen.w, deskCen.h, deskCen.d, texture);
  glRotated(90.0f, 0.0f, 1.0f, 0.0f);
  glTranslated(-deskArm.w, 0.0f, (deskCen.w));
  // left side
  glTranslated(0.0f, 0.0f, -(deskCen.w + deskArm.d));
  hexahedron3d(deskArm.w, deskArm.h, deskArm.d, texture);
  glTranslated(0.02f, -desk_y, 0.0f);
  hexahedron3d(deskArm.h, desk_y, deskArm.d, texture);
  glTranslated(-0.02f, desk_y, 0.0f);
  glTranslated(0.0f, 0.0f, (deskCen.w + deskArm.d));
}

void LaTIMModel::drawCabinet(GLdouble w, GLdouble h, GLdouble d) {
  int texture[] = {3, 3, 3, 3, 3, 3};
  glPushMatrix();
  //right side
  hexahedron3d(0.01f, h, d, texture);
  //bottom side
  hexahedron3d(w + 0.015f, 0.01f, d, texture);
  //right door
  hexahedron3d(w/2 - 0.005f, h, 0.01f, texture);
  glTranslated(0.0f, h, 0.0f);
  //top side
  hexahedron3d(w + 0.015f, 0.01f, d, texture);
  glTranslated(w/2 + 0.01f, -h, 0.0f);
  //left door
  hexahedron3d(w/2 - 0.005f, h, 0.01f, texture);
  glTranslated(w/2 - 0.005f, 0.0f, 0.0f);
  //left side
  hexahedron3d(0.01f, h, d, texture);
  glTranslated(-w, 0.0f, d);
  //back side
  hexahedron3d(w, h, 0.01f, texture);

  glPopMatrix();
}

void LaTIMModel::drawDoor() {
  glColor3f(0.7f, 0.7f, 0.7f); //door colors
  int texture[] = { -1, -1, -1, -1, 13, 14};
  glPushMatrix();
    glTranslated(0.1f, 0.0f, wall1.d);
    glRotated((doorAngle), 0.0f, 1.0f, 0.0f);
    hexahedron3d(door.w, door.h, -door.d, texture);
    glRotated(-(doorAngle), 0.0f, 1.0f, 0.0f);
    glTranslated(0.1f, 0.0f, -wall1.d);
  glPopMatrix();
}

void LaTIMModel::moveDoor(GLdouble length) {
  length *= doorPos;
  doorAngle += length;
  if(doorAngle > 0.0f) {
    doorPos *= -1;
  } else if (doorAngle < -80.0f){
    doorPos *= -1;
  }
}

void LaTIMModel::drawWalls() {
  int texture[] = {0, 0, 0, 0, 0, 0};
  glPushMatrix();

  glPushMatrix();
  glColor3f(1.0f, 1.0f, 1.0f); //wall colors
  //Wall1 (door)
  //wall on the right of the door
  hexahedron3d(0.1f, wall1.h, wall1.d, texture);
  //wall above the door
  glTranslated(0.1f, door.h, 0.0f);
  hexahedron3d(door.w, wall1.h - door.h, wall1.d, texture);
  glTranslated(0.0f, -door.h, 0.0f);
  //wall on the left of the door
  glTranslated(-(0.1f), 0.0f, 0.0f);
  glTranslated((0.1f + door.w), 0.0f, 0.0f);
  hexahedron3d(wall1.w - 0.1f - door.w, wall1.h, wall1.d, texture);
  glTranslated(-(0.1f + door.w), 0.0f, 0.0f);

  glPopMatrix();

  glPushMatrix();
  //Wall1 (windows)
  //front wall
  //space between windows
  GLdouble space = (wall1.w - (window1.w*4)*2) / 3;
  glTranslated(0.0f, 0.0f, (wall2.w - wall2.d));
  hexahedron3d(space, wall1.h, wall1.d, texture);
  glTranslated(space, 0.0f, 0.0f);
  hexahedron3d((window1.w*4), 1.0f, wall1.d, texture);
  //draw right window
  drawWindow();
  glTranslated((window1.w*4), 0.0f, 0.0f);
  hexahedron3d(space, wall1.h, wall1.d, texture);
  glTranslated(space, 0.0f, 0.0f);
  hexahedron3d((window1.w*4), 1.0f, wall1.d, texture);
  //draw left window
  drawWindow();
  glTranslated((window1.w*4), 0.0f, 0.0f);
  hexahedron3d(space, wall1.h, wall1.d, texture);

  glTranslated(-((window1.w*8) + space*2), 0.0f, -(wall2.w - wall2.d));

  glPopMatrix();

  //Wall2 (in front of the AC wall)
  glPushMatrix();
  glTranslated(wall1.w, 0.0f, wall2.w);
  glRotated(-90.0f, 0.0f, -1.0f, 0.0f);
  hexahedron3d(wall2.w, wall2.h, wall2.d, texture);

  glPopMatrix();

  //Wall2 (AC)
  glPushMatrix();
  glRotated(90.0f, 0.0f, -1.0f, 0.0f);
  hexahedron3d(wall2.w, wall2.h, wall2.d, texture);

  glPopMatrix();

  glPopMatrix();
}

void LaTIMModel::drawCabinets() {
  glPushMatrix();

  //cabinets
  //cabinet 1 (in front of the AC wall)
  glColor3f(0.85f, 0.85f, 0.85f); //cabinet color
  glTranslated( (wall1.w - cabinet1.d - wall1.d), 0.0f,  (cabinet1.w + wall1.d + 0.2f));
  glRotated(90.0f, 0.0f, 1.0f, 0.0f);
  drawCabinet(cabinet1.w, cabinet1.h, cabinet1.d);
  glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
  glTranslated(-(wall1.w - cabinet1.d - wall1.d), 0.0f, -(cabinet1.w + wall1.d + 0.2f));
  glPopMatrix();

  glPushMatrix();
  //cabinet 2 (AC)
  glColor3f(0.85f, 0.85f, 0.85f); //cabinet color
  glTranslated( (cabinet2.d + wall2.d), 0.0f,  (wall2.w - nDeskR.w - cabinet2.w - 0.01f - wall2.d));
  glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
  drawCabinet(cabinet2.w, cabinet2.h, cabinet2.d);

  glPopMatrix();
}

void LaTIMModel::drawDesks() {
  glPushMatrix();

  //desks
  glColor3f(0.65f, 0.65f, 0.65f); //desk color
  glTranslated((nDeskL.d + nDeskL.w + wall2.d), desk_y, (wall2.w - nDeskL.d - wall2.d));
  //desk 1
  drawDesk();
  //desk 2
  glTranslated(0.0f, 0.0f, -(deskArm.d*2 + deskCen.w + 0.05f));
  drawDesk();
  //desk 4
  glTranslated((deskArm.w*2 + 0.05f), 0.0f, -(deskCen.w));
  glRotated(180.0f, 0.0f, 1.0f, 0.0f);
  drawDesk();
  glRotated(-180.0f, 0.0f, 1.0f, 0.0f);
  glTranslated(-(deskArm.w*2 + 0.05f), 0.0f, (deskCen.w));
  //desk 3
  glTranslated((deskCen.w*2 + 0.05f), 0.0f, (deskArm.d*2 + 0.05f));
  glRotated(180.0f, 0.0f, 1.0f, 0.0f);
  drawDesk();
  glRotated(-180.0f, 0.0f, 1.0f, 0.0f);
  glTranslated(-(deskArm.w*2 + 0.05f), 0.0f, -(deskArm.d*2 + 0.05f));
  glTranslated(0.0f, 0.0f, (deskArm.d*2 + 0.05f));
  glTranslated(-(nDeskL.d + nDeskL.w + wall2.d), -desk_y, -(wall2.w - nDeskL.d - wall2.d));

  glPopMatrix();
  int texture[] = {4, 4, 4, 4, 4, 4};
  glPushMatrix();

  //desks divider
  glColor3f(0.85f, 0.85f, 0.85f); //divider color
  //divider 1
  glTranslated((nDeskL.w + nDeskR.d + wall2.d - deskDiv1.d), 0.0f, (wall2.w - (deskArm.d*2 + deskCen.w) - 0.05f - wall2.d));
  hexahedron3d(deskDiv1.w, deskDiv1.h, deskDiv1.d, texture);
  //divider 2
  glTranslated(0.0f, 0.0f, -(deskCen.w + deskArm.d*2 + deskDiv1.d));
  hexahedron3d(deskDiv1.w, deskDiv1.h, deskDiv1.d, texture);
  glTranslated(0.07f, 0.0f, (deskCen.w + deskArm.d*2 + deskDiv1.d));
  //divider 3
  glTranslated((deskArm.w - 0.02f), 0.0f, (deskCen.w + deskArm.d*2 + deskDiv2.d));
  glRotated(90.0f, 0.0f, 1.0f, 0.0f);
  hexahedron3d(deskDiv2.w, deskDiv2.h, deskDiv2.d, texture);
  glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
  glTranslated(-(deskArm.w - 0.02f), 0.0f, -(deskCen.w + deskArm.d*2 + deskDiv2.d));
  glTranslated(-(nDeskL.w + nDeskR.d + wall2.d - deskDiv1.d), 0.0f, -(wall2.w - (deskArm.d*2 + deskCen.w) - 0.05f - wall2.d));

  glPopMatrix();
}

void LaTIMModel::drawShelf() {
  int texture[] = {4, 4, 4, 4, 4, 4};
  glPushMatrix();

  //Shelfs
  //Shelf Right (AC)
  glColor3f(0.75f, 0.75f, 0.75f); //desk color
  glTranslated(wall2.d, desk_y, (wall2.w - wall2.d));
  glTranslated(0.0f, 0.0f, -nDeskR.w);
  hexahedron3d(nDeskR.d, nDeskR.h, nDeskR.w, texture);
  glTranslated(0.0f, 0.0f, nDeskR.w);
  glTranslated(-wall2.d, -desk_y, -(wall2.w - wall2.d));

  //Shelf Left (windows)
  glTranslated((nDeskL.d + wall2.d), desk_y, (wall2.w - nDeskL.d - wall2.d));
  hexahedron3d(nDeskL.w, nDeskL.h, nDeskL.d, texture);
  glTranslated(-(nDeskL.d + wall2.d), -desk_y, -(wall2.w - nDeskL.d - wall2.d));

  glPopMatrix();
}

void LaTIMModel::drawComputers() {
  GLdouble pc_x[4], pc_z[4];
  pc_x[0] = nDeskR.d + nDeskL.w + deskArm.w - 0.62f;
  pc_z[0] = wall2.w - 0.20f;
  pc_x[1] = nDeskR.d + nDeskL.w + deskArm.w - 0.62f;
  pc_z[1] = wall2.w - 0.25f - deskCen.w;
  pc_x[2] = nDeskR.d + nDeskL.w + deskArm.w - 0.62f;
  pc_z[2] = wall2.w - 0.20f - (deskArm.d*2 + deskCen.w);
  pc_x[3] = nDeskR.d + nDeskL.w + deskArm.w - 0.62f;
  pc_z[3] = wall2.w - 0.25f- (deskArm.d + deskCen.w)*2;

  glPushMatrix();
    glTranslated(0.15f, 0.0f, 0.0f);

    drawMonitor(pc_x[0] + 0.40f, desk_y + deskArm.h, pc_z[0] - 0.50f);
    drawCPU(pc_x[0], desk_y + deskArm.h, pc_z[0]);
    drawMonitor(pc_x[1] + 0.40f, desk_y + deskArm.h, pc_z[1]);
    drawCPU(pc_x[1], desk_y + deskArm.h, pc_z[1] - 0.70f);
    drawMonitor(pc_x[2] + 0.40f, desk_y + deskArm.h, pc_z[2] - 0.50f);
    drawCPU(pc_x[2], desk_y + deskArm.h, pc_z[2]);
    drawMonitor(pc_x[3] + 0.40f, desk_y + deskArm.h, pc_z[3]);
    drawCPU(pc_x[3], desk_y + deskArm.h, pc_z[3] - 0.70f);
  glPopMatrix();

  glPushMatrix();
    glRotated(180.0f, 0.0f, 1.0f, 0.0f);
    glTranslated(-(wall1.w + 0.27f), 0.0f, -(wall2.w + wall2.w/3 - 0.05f));

    drawMonitor(pc_x[0] + 0.40f, desk_y + deskArm.h, pc_z[0] - 0.50f);
    drawCPU(pc_x[0], desk_y + deskArm.h, pc_z[0]);
    drawMonitor(pc_x[1] + 0.40f, desk_y + deskArm.h, pc_z[1]);
    drawCPU(pc_x[1], desk_y + deskArm.h, pc_z[1] - 0.70f);
    drawMonitor(pc_x[2] + 0.40f, desk_y + deskArm.h, pc_z[2] - 0.50f);
    drawCPU(pc_x[2], desk_y + deskArm.h, pc_z[2]);
    drawMonitor(pc_x[3] + 0.40f, desk_y + deskArm.h, pc_z[3]);
    drawCPU(pc_x[3], desk_y + deskArm.h, pc_z[3] - 0.70f);

    glTranslated((wall1.w + 0.12f), 0.0f, (wall2.w + wall2.w/3 - 0.05f));
    glRotated(-180.0f, 0.0f, 1.0f, 0.0f);
  glPopMatrix();
}

void LaTIMModel::drawCPU(GLdouble x, GLdouble y, GLdouble z) {
  //int texture[] = {18, 19, 17, 20, 16, 15};
  int texture[] = {-1, -1, -1, -1, -1, -1};
  glColor3f(0.1f, 0.1f, 0.1f); //cpu color
  glPushMatrix();
    glTranslated(x, y, z);
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    hexahedron3d(0.20f, 0.35f, 0.50f, texture);
  glPopMatrix();
}

void LaTIMModel::drawMonitor(GLdouble x, GLdouble y, GLdouble z) {
  glColor3f(0.1f, 0.1f, 0.1f); //cpu color
  glPushMatrix();
    glTranslated(x, y + 0.10f, z);
    glRotated(90.0f, 0.0f, 1.0f, 0.0f);
    //Screen
    hexahedron3d(0.40f, 0.30f, 0.02f);
    glTranslated(0.0f, -0.10f, 0.0f);
    glTranslated((0.40f/2 - 0.05f/2), 0.0f, 0.0f);
    hexahedron3d(0.05f, 0.10f, 0.02f);
    glTranslated(-(0.40f/2 - 0.05f/2), 0.0f, 0.0f);
    //Base
    glTranslated(0.125f, 0.0f, -0.10f);
    hexahedron3d(0.15f, 0.01f, 0.15f);
    glTranslated(-0.125f, 0.0f, 0.10f);
    glPushMatrix();
      glColor3f(0.3f, 0.3f, 0.3f);
      glTranslated(0.0f, 0.0f, -0.2f);
      glRotated(90.0f, 0.0f, 1.0f, 0.0f);
      int texKeyboard[] = {-1, 7, -1, -1, -1, -1};
      hexahedron3d(keyboard.w, keyboard.h, keyboard.d, texKeyboard);
    glPopMatrix();
  glPopMatrix();
}

void LaTIMModel::drawWhiteboard() {
  int texture[] = {-1, -1, -1, -1, 1, -1};
  glPushMatrix();

  glTranslated(wall1.w - door.w - blackboard.w, wall1.h/2 - blackboard.h/2 - 0.10f, wall1.d);

  glPushMatrix();
  glColor3f(1.0f, 1.0f, 1.0f); //blackboard color
  glTranslated(blackboard.d, (blackboard.d), 0.0f);
  hexahedron3d(blackboard.w - blackboard.d*2, blackboard.h - blackboard.d*2, blackboard.d/2, texture);
  glTranslated(-(blackboard.d), -(blackboard.d), 0.0f);
  glPopMatrix();

  int texture1[] = {1, 1, 1, 1, 1, 1};
  glPushMatrix();
  glColor3f(0.5f, 0.5f, 0.5f); //blackboard border color
  glTranslated(0.0f, blackboard.d, 0.0f);
  hexahedron3d(blackboard.d, blackboard.h - blackboard.d*2, blackboard.d, texture1);
  glTranslated(0.0f, -blackboard.d, 0.0f);

  hexahedron3d(blackboard.w, blackboard.d, blackboard.d, texture1);

  glTranslated((blackboard.w - blackboard.d), blackboard.d, 0.0f);
  hexahedron3d(blackboard.d, blackboard.h - blackboard.d*2, blackboard.d, texture1);
  glTranslated(-(blackboard.w - blackboard.d), -blackboard.d, 0.0f);

  glTranslated(0.0f, (blackboard.h - blackboard.d), 0.0f);
  hexahedron3d(blackboard.w, blackboard.d, blackboard.d, texture1);
  glTranslated(0.0f, -(blackboard.h - blackboard.d), 0.0f);
  glPopMatrix();

  glPopMatrix();
}

void LaTIMModel::drawCeiling() {
  int texture[] = {0, 0, 0, 0, 0, 0};
  glPushMatrix();

  glColor3f(1.0f, 1.0f, 1.0f); //wall colors
  glTranslated(-wall1.d, (wall1.h), 0.0f);
  hexahedron3d(wall1.w + (wall1.d*2), 0.01f, wall2.w, texture);

  glPopMatrix();
}

void LaTIMModel::drawFloor() {
  int texture[] = {-1, 5, -1, -1, -1, -1};
  glPushMatrix();

  glColor3f(0.7f, 0.7f, 0.7f); //wall colors
  glTranslated(0.0f, -0.01f, 0.0f);
  hexahedron3d(wall1.w, 0.01f, wall2.w, texture);

  glPopMatrix();
}

void LaTIMModel::drawWindow() {
  int texture[] = {0, 0, 0, 0, 0, 0};
  glPushMatrix();

  glTranslated(0.0f, 1.0f, 0.0f);
  //drawWindow1
  glTranslated(0.0f, window1.h, 0.0f);
  hexahedron3d((window1.w*4), 0.10f, wall1.d, texture);
  glTranslated(0.0f, 0.10f, 0.0f);
  //drawWindow2
  glTranslated(0.0f, window2.h, 0.0f);
  hexahedron3d((window1.w*4), (wall1.h - 1.10f - window1.h - window2.h), wall1.d, texture);

  glTranslated(0.0f, -window2.h, 0.0f);
  glTranslated(0.0f, -0.10f, 0.0f);
  glTranslated(0.0f, -window1.h, 0.0f);
  glTranslated(0.0f, -1.0f, 0.0f);

  glPopMatrix();
}

void LaTIMModel::drawLamp(GLdouble radius, GLdouble width) {
  GLdouble caseWidth = width/7;
  GLdouble tubeRadius = radius - radius/3;
  GLdouble tubeWidth = width - (caseWidth)*2;

  glPushMatrix();

  //left case
  glColor3f(0.2f, 0.2f, 0.2f);
  cylinder3d(radius, caseWidth, true, false);

  glTranslated(0.0f, 0.0f, caseWidth/2);

  //Tube
  glColor3f(1.0f, 1.0f, 1.0f);
  cylinder3d(tubeRadius, tubeWidth, true, true);

  glTranslated(0.0f, 0.0f, caseWidth/2);

  //Top case
  glColor3f(0.2f, 0.2f, 0.2f);
  halfCylinder3d(radius, tubeWidth - caseWidth, false, false);

  glTranslated(0.0f, 0.0f, tubeWidth - caseWidth);

  //Right case
  glColor3f(0.2f, 0.2f, 0.2f);
  cylinder3d(radius, caseWidth, false, true);

  glTranslated(0.0f, 0.0f, -(tubeWidth));

  glPopMatrix();
}

void LaTIMModel::drawLamps() {
  GLdouble piece1 = wall1.w/3;
  GLdouble piece2 = wall2.w/4;
  GLdouble lampRadius = 0.02f;
  GLdouble lampWidth = 2.0f;

  glPushMatrix();

  glTranslated(0.0f, (wall1.h - lampRadius), 0.0f);
  glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
  glTranslated(0.0f, 0.0f, wall2.d);

  for(int i = 0; i < 3; ++i) {
      glTranslated((piece2 + i*piece2), 0.0f, -(piece1 + lampWidth/3));
      drawLamp(lampRadius, lampWidth);

      glTranslated(0.0f, 0.0f, -(piece1 + lampWidth/3));
      drawLamp(lampRadius, lampWidth);
      glTranslated(0.0f, 0.0f, (piece1 + lampWidth/3));

      glTranslated(-(piece2 + i*piece2), 0.0f, (piece1 + lampWidth/3));
  }

  glTranslated(0.0f, 0.0f, -wall2.d);
  glRotated(90.0f, 0.0f, 1.0f, 0.0f);
  glTranslated(0.0f, -(wall1.h - wall1.d/2), 0.0f);

  glPopMatrix();
}

void LaTIMModel::drawAC() {
  glPushMatrix();
  glTranslated(0.0f, 2.5f, 4.0f);
  glColor3f(1.0f, 1.0f, 1.0f);
  // { back, top, front, left, right, bottom }
  int texture[] = {1, 1, 2, 1, 1, 1};
  //drawBox(ac.w, tex);
  hexahedron3d(ac.d, ac.h, ac.w, texture);

  glPopMatrix();
}

void LaTIMModel::drawChairs() {
      glPushMatrix();
      glColor3f(0.1f, 0.1f, 0.1f);
      glTranslated(2.0f, 0.4f, 2.0f);
      glRotated(90.0f, 1.0f, 0.0f, 0.0f);
      solidCylinder(0.005f, 0.005f, 0.4f, 30, 5);
      glRotated(-90.0f, 1.0f, 0.0f, 0.0f);

      glTranslated(0.2f, 0.0f, 0.0f);
      glRotated(90.0f, 1.0f, 0.0f, 0.0f);
      solidCylinder(0.005f, 0.005f, 0.4f, 30, 5);
      glRotated(-90.0f, 1.0f, 0.0f, 0.0f);

      glTranslated(0.0f, 0.0f, 0.2f);
      glRotated(90.0f, 1.0f, 0.0f, 0.0f);
      solidCylinder(0.005f, 0.005f, 0.4f, 30, 5);
      glRotated(-90.0f, 1.0f, 0.0f, 0.0f);

      glTranslated(-0.2f, 0.0f, 0.0f);
      glRotated(90.0f, 1.0f, 0.0f, 0.0f);
      solidCylinder(0.005f, 0.005f, 0.4f, 30, 5);
      glRotated(-90.0f, 1.0f, 0.0f, 0.0f);

      glPopMatrix();
}
