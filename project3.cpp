/*==================================================================================================
 PROGRAMMERS: Jamie Johnson, Matthew Wilson and Garren Ijames
 TRACE FOLDERS: ---, ---, ---
 COURSE: CSC 525/625
 MODIFIED BY:	Jamie Johnson, Matthew Wilson and Garren Ijames
 LAST MODIFIED DATE: 20161204
 CONTRIBUTIONS:
      Matt   - 33.3%

      Garren - 33.3%

      Jamie  - 33.3%

 DESCRIPTION:
 NOTE:
 FILES:
 IDE/COMPILER: MicroSoft Visual Studio 2013
 INSTRUCTION FOR COMPILATION AND EXECUTION:
	1.		Double click on myCPPproj.sln	to OPEN the project
	2.		Press Ctrl+F7					to COMPILE
	3.		Press Ctrl+Shift+B		to BUILD (COMPILE+LINK)
	4.		Press Ctrl+F5					to EXECUTE
==================================================================================================*/
#include <iostream>
#include <GL/glut.h>				// include GLUT library
#include <cmath>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int WINDOW_DEPTH = 600; // for viewable cube

const int TILE_SIZE = 10; // leave as an integer that evenly divides window width and depth

const float DARK_BLUE[] = { 131.0f / 255.0f, 157.0f / 255.0f, 183.0f / 255.0f };
const float LIGHT_BLUE[] = { 183.0f / 255.0f, 201.0f / 255.0f, 217.0f / 255.0f };

int lastX; // for keeping track of mouse position

int mainWindow;


void drawLines()
{
	//draw coordinate axis labels
	glColor3f(0, 0, 0);
	glRasterPos3i(155, -4, 0);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'X'); //x axis

	glRasterPos3i(-5, 155, 0);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Y'); //y axis

	glRasterPos3i(-0, -4, 170);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Z'); //z axis


	glBegin(GL_LINES);
		glVertex4i(-150, 0, 0, 1);
		glVertex4i(150, 0, 0, 1);
		glVertex4i(0, -150, 0, 1);
		glVertex4i(0, 150, 0, 1);
		glVertex4i(0, 0, -150, 1);
		glVertex4i(0, 0, 150, 1);
	glEnd();
}


void drawTile(int x, int z, const float color[3])
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3fv(color);
	
	glBegin(GL_POLYGON);
	glVertex4i(x, 0, z, 1);
	glVertex4i(x + TILE_SIZE, 0, z, 1);
	glVertex4i(x + TILE_SIZE, 0, z + TILE_SIZE, 1);
	glVertex4i(x, 0, z + TILE_SIZE, 1);
	glEnd();
}

void drawFloor()
{
	bool isLight = false;
	for (int z = WINDOW_DEPTH / 2; z >= -WINDOW_DEPTH / 2; z--) {
		if (z % TILE_SIZE == 0) {
			for (int x = -WINDOW_WIDTH / 2; x <= WINDOW_WIDTH / 2; x++) {
				if (x % TILE_SIZE == 0) {
					if (isLight)
						drawTile(x, z, LIGHT_BLUE);
					else
						drawTile(x, z, DARK_BLUE);
					isLight = !isLight;
				}
			}
		}
	}
}


// Display Callbacks

void displayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	drawLines();
	glutWireCube(5.0);
	drawFloor();
	drawObject();
	glFlush();
}


// Initialization Functions

void init()
{
	glClearColor(1, 1, 1, 0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(50.0, 50.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 10.0, 1000.0);
}


// Menu if needed

void topMenuCallback(int entryId)
{
}


// Motion Callbacks

void passiveMotionCallback(int x, int y)
{
    lastX = x - WINDOW_WIDTH;
}

void motionCallback(int x, int y)
{
  glMatrixMode(GL_MODELVIEW); // switch to model view stack

  float worldCoordX = x - WINDOW_WIDTH;
  float distX = worldCoordX - lastX;

  glRotatef(distX, 0.0, 1.0, 0.0);

  lastX = worldCoordX;

  displayCallback();
}


int main(int argc, char ** argv)
{
	glutInit(& argc, argv);			// optional
	glutInitDisplayMode(GLUT_DEPTH);	// optional

	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 0);
	mainWindow = glutCreateWindow("Display in 3D");

	init();

  int mainMenu = glutCreateMenu(topMenuCallback);
  glutAddMenuEntry("EXIT", 3);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(displayCallback);
  glutMotionFunc(motionCallback);
  glutPassiveMotionFunc(passiveMotionCallback);

	glutMainLoop();

	return 0;
}
