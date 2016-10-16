#include "main.h"

void drawFloor() {
    glPushMatrix();
    int size = 40;
    for(float i = -size; i <= size; i += 5) {
          glBegin(GL_LINES);
              glColor3f(1.0f, 1.0f, 1.0f);
              glVertex3f(-size, 0, i);
              glVertex3f(size, 0, i);
              glVertex3f(i, 0,-size);
              glVertex3f(i, 0, size);
          glEnd();
      }
    glPopMatrix();
}

void Draw_Skybox(float x, float y, float z, float width, float height, float length)
{
	// Center the Skybox around the given x,y,z position
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;

  glPushMatrix();
	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, latim.texture_id[21]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height,	z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, latim.texture_id[22]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y+height, z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, latim.texture_id[23]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y+height,	z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height,	z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, latim.texture_id[24]);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z+length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height,	z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, latim.texture_id[25]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height,	z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, latim.texture_id[26]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
	glEnd();
  glPopMatrix();
}


void loadTextureFromFile(char const *filename,int index)
{

  int width, height;
  unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

    printf("%d %d\n", width, height);

  glGenTextures(1, &latim.texture_id[index]);
  glBindTexture(GL_TEXTURE_2D, latim.texture_id[index]);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void initTextures(){
	loadTextureFromFile("tex/wall.jpg", 0);
	loadTextureFromFile("tex/wboard.jpg", 1);
	loadTextureFromFile("tex/ac.jpg", 2);
	loadTextureFromFile("tex/cabinet.jpg", 3);
	loadTextureFromFile("tex/desk.jpg", 4);
	loadTextureFromFile("tex/floor.jpg", 5);
	loadTextureFromFile("tex/screen.png", 6);
	loadTextureFromFile("tex/keyboard.jpg", 7);
	loadTextureFromFile("tex/chair.jpg", 8);
	loadTextureFromFile("tex/mouse.png", 9);
	loadTextureFromFile("tex/ac_front.jpg", 10);
	loadTextureFromFile("tex/ac_right.jpg", 11);
	loadTextureFromFile("tex/ac_left.jpg", 12);
	loadTextureFromFile("tex/door_front.jpg", 13);
	loadTextureFromFile("tex/door_back.jpg", 14);
	loadTextureFromFile("tex/cpu_front.jpg", 15);
	loadTextureFromFile("tex/cpu_back.jpg", 16);
	loadTextureFromFile("tex/cpu_right.jpg", 17);
	loadTextureFromFile("tex/cpu_left.jpg", 18);
	loadTextureFromFile("tex/cpu_top.jpg", 19);
	loadTextureFromFile("tex/cpu_bottom.jpg", 20);

	loadTextureFromFile("tex/SunSetFront.png", 21);
  loadTextureFromFile("tex/SunSetBack.png", 22);
  loadTextureFromFile("tex/SunSetLeft.png", 23);
  loadTextureFromFile("tex/SunSetRight.png", 24);
  loadTextureFromFile("tex/SunSetUp.png", 25);
  loadTextureFromFile("tex/SunSetDown.png", 26);
}

void initLights(){
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_NORMALIZE);
	// Enable Gouraud color model
	glShadeModel(GL_SMOOTH);

/*
	// Defines material reflectance
	glMaterialfv(GL_FRONT,GL_SPECULAR, especular);
	// Defines brightness concentration
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientlight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0color);
	glLightfv(GL_LIGHT0, GL_POSITION, ligh0pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0dir);
	glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, shininess);
	glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, spot_light0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1color);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1color);
	glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1dir);
	glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, shininess);
	glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, spot_light1);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
*/
  int k;

  for (k = 0; k < NUM_LIGHTS; ++k) {
    int lt = GL_LIGHT1 + k;
    Light *light = &spots[k];

    glEnable(lt);
    glLightfv(lt, GL_AMBIENT, light->amb);
    glLightfv(lt, GL_DIFFUSE, light->diff);

    glLightfv(lt, GL_SPECULAR, light->amb);

    glLightf(lt, GL_SPOT_EXPONENT, light->spotExp);
    glLightf(lt, GL_SPOT_CUTOFF, light->spotCutoff);
    glLightf(lt, GL_CONSTANT_ATTENUATION, light->atten[0]);
    glLightf(lt, GL_LINEAR_ATTENUATION, light->atten[1]);
    glLightf(lt, GL_QUADRATIC_ATTENUATION, light->atten[2]);
  }

	glEnable(GL_COLOR_MATERIAL);
}

void setLights() {
  int k;

  for (k = 0; k < NUM_LIGHTS; ++k) {
    int lt = GL_LIGHT1 + k;
    Light *light = &spots[k];

    glPushMatrix();
    glTranslatef(light->trans[0], light->trans[1], light->trans[2]);
    glRotatef(light->rot[0], 1, 0, 0);
    glRotatef(light->rot[1], 0, 1, 0);
    glRotatef(light->rot[2], 0, 0, 1);
    glLightfv(lt, GL_POSITION, light->pos);
    glLightfv(lt, GL_SPOT_DIRECTION, light->spotDir);
    glPopMatrix();
  }
}

void drawLines() {
  int k;

  glDisable(GL_LIGHTING);
  for (k = 0; k < NUM_LIGHTS; ++k) {
    Light *light = &spots[k];

    glColor4fv(light->diff);

    glPushMatrix();
    glBegin(GL_LINES);
    glVertex3f(light->pos[0], light->pos[1], light->pos[2]);
    //glVertex3f(light->spotDir[0], light->spotDir[1], light->spotDir[2]);
    GLfloat dir[3] = {0.0f, 0.0f, 0.0f};
    dir[0] = light->pos[0] + light->spotDir[0];
    dir[1] = light->pos[1] + light->spotDir[1];
    dir[2] = light->pos[2] + light->spotDir[2];
    glVertex3fv(dir);

    glEnd();
    glPopMatrix();
  }
  glEnable(GL_LIGHTING);
}

void display(void) {
  glEnable(GL_DEPTH_TEST);

  glDepthMask(GL_TRUE);
  glClearColor(0.1,0.1,0.1,1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

  gluLookAt(cam.eye.x, cam.eye.y, cam.eye.z, cam.view.x, cam.view.y, cam.view.z, cam.up.x, cam.up.y, cam.up.z);

  glPushMatrix();
    glRotatef(spin, 0, 1, 0);
    initLights();
    setLights();
  glPopMatrix();

  drawFloor();
  Draw_Skybox(0,0,0,50,50,50);	// Draw the Skybox
  latim.draw();

  //drawLines();

  glPopMatrix();

  animate();

  glutSwapBuffers();
}

void special(int key, int x, int y) {
  float fraction = 1;
  switch (key) {
    case GLUT_KEY_UP:
      cam.moveCamera(1);
      break;
    case GLUT_KEY_DOWN:
      cam.moveCamera(-1);
      break;
    case GLUT_KEY_LEFT:
      cam.moveSideways(-1);
      break;
    case GLUT_KEY_RIGHT:
      cam.moveSideways(1);
      break;
  }
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'w':
      cam.moveCamera(1);
      break;
    case 's':
      cam.moveCamera(-1);
      break;
    case 'a':
      cam.moveSideways(-1);
      break;
    case 'd':
      cam.moveSideways(1);
      break;
    case 'o':
      latim.moveDoor(1.0f);
      break;
    case 27:
      exit(0);
      break;
  }
  glutPostRedisplay();
}

void mouseMotion(int mx, int my) {
      //std::cout << "X: " << mx << " Y: " << my << std::endl;
      cam.moveMouse(mx, my, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

      glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

  if(button == 3) { //scroll up
    cam.moveUp(1);
  } else if(button == 4) { //scroll down
    cam.moveUp(-1);
  } else { //normal button

  }
  glutPostRedisplay();
}

void init() {
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
  glPointSize(20.0);

  glMatrixMode(GL_MODELVIEW);

  // habilitando as texturas
  initTextures();
  //draw();
}

void reshape(int width, int height) {
  glViewport(0,0,(GLint)width,(GLint)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(70.0, (GLfloat) width/ (GLfloat) height, 0.1, 200.0);
  //gluPerspective(80.0,width/(float)height,0.1,200.0);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char **argv) {
  glutInitWindowPosition(0,0);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);

  if(!glutCreateWindow("CEPETEC - Instituto de Computação - UFAL")) {
    fprintf(stderr,"Error opening a window.\n");
    exit(-1);
  }
  //glutFullScreen();

  init();

  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutDisplayFunc(display);
  glutPassiveMotionFunc(mouseMotion);
  glutMouseFunc(mouse);
  glutReshapeFunc(reshape);

  glutIdleFunc(animate);

  glutMainLoop();
  return(0);
}
