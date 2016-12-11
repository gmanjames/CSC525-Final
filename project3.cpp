/*==================================================================================================
PROGRAMMERS: Jamie Johnson, Matthew Wilson and Garren Ijames
TRACE FOLDERS: Jamie029, Wilson10101, Ijames160
COURSE: CSC 525/625
MODIFIED BY:	Jamie Johnson, Matthew Wilson and Garren Ijames
LAST MODIFIED DATE: 12/11/2016
CONTRIBUTIONS:
	Matt   - 33.3%
		-Lighting
		-Documentation
		-Object Placement
	Garren - 33.3%
		-View rotation
		-Object Placement
		-Floor
	Jamie  - 33.3%
		-Object shape definitions
		-Object Placement



DESCRIPTION: Project 3 - 3D Event/Advertisement

NOTE: This 3D scene of a graduation includes all of the listed requirements to the project:
			3D shapes
			Interactive view through graphics window
		And Additionally:
			Simple Scene/object Lighting

FILES:Project3.cpp

IDE/COMPILER: MicroSoft Visual Studio 2013
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on projProject.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+Shift+B		to BUILD (COMPILE+LINK)
4.		Press Ctrl+F5					to EXECUTE
==================================================================================================*/
#include <iostream>
#include <GL/glut.h>				// include GLUT library
#include <cmath>


//from initial position, pos Z = front, pos X = right
enum ShapeFace {_Bottom, _Top, _Left, _Right, _Front, _Back, _Hat};

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int WINDOW_DEPTH = 600; // for viewable cube

const int TILE_SIZE = 10; // leave as an integer that evenly divides window width and depth

const float DARK_BLUE[] = { 131.0f / 255.0f, 157.0f / 255.0f, 183.0f / 255.0f };
const float LIGHT_BLUE[] = { 183.0f / 255.0f, 201.0f / 255.0f, 217.0f / 255.0f };

int lastX; // for keeping track of mouse position


int infoWindowId;
int mainWindowId;


GLfloat light_diffuse[] = { 1, 1, 1, 1 }; //Light color: bright white light
GLfloat light_position[] = { 10, 300, -50.0, 1 };  // Light location, set as a point light above the scene

GLubyte MPattern[128] = {
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x0f, 0x00, 0x00, 0xf0,
	0x0f, 0x00, 0x00, 0xf0,
	0x0f, 0x00, 0x00, 0xf0,
	0x0f, 0x00, 0x00, 0xf0,
	0x0f, 0x00, 0x00, 0xf0,
	0x0f, 0x00, 0x00, 0xf0,
	0x0f, 0x00, 0x00, 0xf0,
	0x0f, 0x00, 0x00, 0xf0,
	0x0f, 0x00, 0x00, 0xf0,
	0x0f, 0x00, 0x00, 0xf0,
	0x0f, 0x00, 0x00, 0xf0,
	0x0f, 0x00, 0x00, 0xf0,

	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,

	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,

	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,

	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
};

void polygon(float v1[], float v2[], float v3[], float v4[], float xOffset, float zOffset, int face)
{
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	float v1XOffset = v1[0] + xOffset;
	float v1ZOffset = v1[2] + zOffset;

	float v2XOffset = v2[0] + xOffset;
	float v2ZOffset = v2[2] + zOffset;

	float v3XOffset = v3[0] + xOffset;
	float v3ZOffset = v3[2] + zOffset;

	float v4XOffset = v4[0] + xOffset;
	float v4ZOffset = v4[2] + zOffset;



	glBegin(GL_POLYGON);

	switch (face){
		case 0: glNormal3f(0, 0, -1);
			break;
		case 1: glNormal3f(0, 0, 1);
			break;
		case 2: glNormal3f(-1, 0, 0);
			break;
		case 3: glNormal3f(1, 0, 0);
			break;
		case 4: glNormal3f(0, 1, 0);
			break;
		case 5: glNormal3f(0, -1, 0);
			break;
		case 6: glNormal3f(0, 1600, -240);
			break;
	}

	glVertex4f(v1XOffset, v1[1], v1ZOffset, v1[3]);
	glVertex4f(v2XOffset, v2[1], v2ZOffset, v1[3]);
	glVertex4f(v3XOffset, v3[1], v3ZOffset, v1[3]);
	glVertex4f(v4XOffset, v4[1], v4ZOffset, v1[3]);
	glEnd();
}

void drawHat(int xOffset, int zOffset)
{
	float hatVerts[][4] = {
		-20, 107, 20, 1, 20, 107, 20, 1, 20, 101, -20, 1, -20, 101, -20, 1
	};

	float color[] = { .7, 0, 0, 0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	polygon(hatVerts[0], hatVerts[1], hatVerts[2], hatVerts[3], xOffset, zOffset, _Hat);

	float colort[] = { 1, .7, 0, 0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colort);
	glLineWidth(3);
	glBegin(GL_LINES);
		glNormal3f(0, 1600, -240);
		glVertex4i(xOffset, 105, zOffset, 1);
		glVertex4i(xOffset, 101, zOffset - 22, 1);
	glEnd();
}

void drawHead(int xOffset, int zOffset)
{
	float headVerts[][4] = {
		-10, 80, 10, 1, -10, 80, -10, 1, 10, 80, -10, 1, 10, 80, 10, 1,
		-10, 100, 10, 1, -10, 100, -10, 1, 10, 100, -10, 1, 10, 100, 10, 1
	};

	float color[] = { .65, .25, .15, 0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	polygon(headVerts[0], headVerts[1], headVerts[2], headVerts[3], xOffset, zOffset, _Bottom);
	polygon(headVerts[4], headVerts[5], headVerts[6], headVerts[7], xOffset, zOffset, _Top);
	polygon(headVerts[0], headVerts[4], headVerts[5], headVerts[1], xOffset, zOffset, _Left);
	polygon(headVerts[5], headVerts[6], headVerts[2], headVerts[1], xOffset, zOffset, _Back);
	polygon(headVerts[6], headVerts[7], headVerts[3], headVerts[2], xOffset, zOffset, _Right);
	polygon(headVerts[4], headVerts[7], headVerts[3], headVerts[0], xOffset, zOffset, _Front);
}

void drawBody(int xOffset, int zOffset)
{
	float bodyVerts[][4] = {
		-15, 45, 15, 1, -15, 45, -15, 1, 15, 45, -15, 1, 15, 45, 15, 1,
		-15, 80, 15, 1, -15, 80, -15, 1, 15, 80, -15, 1, 15, 80, 15, 1
	};

	float color[] = { .7, 0, 0, 0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	polygon(bodyVerts[0], bodyVerts[1], bodyVerts[2], bodyVerts[3], xOffset, zOffset, _Bottom);
	polygon(bodyVerts[4], bodyVerts[5], bodyVerts[6], bodyVerts[7], xOffset, zOffset, _Top);
	polygon(bodyVerts[0], bodyVerts[4], bodyVerts[5], bodyVerts[1], xOffset, zOffset, _Left);
	polygon(bodyVerts[5], bodyVerts[6], bodyVerts[2], bodyVerts[1], xOffset, zOffset, _Back);
	polygon(bodyVerts[6], bodyVerts[7], bodyVerts[3], bodyVerts[2], xOffset, zOffset, _Right);
	polygon(bodyVerts[4], bodyVerts[7], bodyVerts[3], bodyVerts[0], xOffset, zOffset, _Front);
}

void drawLegs(int xOffset, int zOffset)
{

	float legVerts[][4] = {
		-12.5, 0, 12.5, 1, -12.5, 0, -12.5, 1, 12.5, 0, -12.5, 1, 12.5, 0, 12.5, 1,
		-12.5, 45, 12.5, 1, -12.5, 45, -12.5, 1, 12.5, 45, -12.5, 1, 12.5, 45, 12.5, 1
	};

	float color[] = { .7, 0, 0, 0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	polygon(legVerts[0], legVerts[1], legVerts[2], legVerts[3], xOffset, zOffset, _Bottom);
	polygon(legVerts[4], legVerts[5], legVerts[6], legVerts[7], xOffset, zOffset, _Top);
	polygon(legVerts[0], legVerts[4], legVerts[5], legVerts[1], xOffset, zOffset, _Left);
	polygon(legVerts[5], legVerts[6], legVerts[2], legVerts[1], xOffset, zOffset, _Back);
	polygon(legVerts[6], legVerts[7], legVerts[3], legVerts[2], xOffset, zOffset, _Right);
	polygon(legVerts[4], legVerts[7], legVerts[3], legVerts[0], xOffset, zOffset, _Front);
}

void drawArms(int xOffset, int zOffset)
{
	float armVerts[][4] = {
		-25, 50, 7.5, 1, -25, 50, -7.5, 1, 25, 50, -7.5, 1, 25, 50, 7.5, 1,
		-25, 75, 7.5, 1, -25, 75, -7.5, 1, 25, 75, -7.5, 1, 25, 75, 7.5, 1,
	};

	float handVerts[][4] = {
		-25, 45, 7.5, 1, -25, 45, -7.5, 1, 25, 45, -7.5, 1, 25, 45, 7.5, 1,
		-25, 50, 7.5, 1, -25, 50, -7.5, 1, 25, 50, -7.5, 1, 25, 50, 7.5, 1,
	};

	float color[] = { .7, 0, 0, 0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	polygon(armVerts[0], armVerts[1], armVerts[2], armVerts[3], xOffset, zOffset, _Bottom);
	polygon(armVerts[4], armVerts[5], armVerts[6], armVerts[7], xOffset, zOffset, _Top);
	polygon(armVerts[0], armVerts[4], armVerts[5], armVerts[1], xOffset, zOffset, _Left);
	polygon(armVerts[5], armVerts[6], armVerts[2], armVerts[1], xOffset, zOffset, _Back);
	polygon(armVerts[6], armVerts[7], armVerts[3], armVerts[2], xOffset, zOffset, _Right);
	polygon(armVerts[4], armVerts[7], armVerts[3], armVerts[0], xOffset, zOffset, _Front);

	float colorh[] = { .65, .25, .15, 0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorh);
	polygon(handVerts[0], handVerts[1], handVerts[2], handVerts[3], xOffset, zOffset, _Bottom);
	polygon(handVerts[4], handVerts[5], handVerts[6], handVerts[7], xOffset, zOffset, _Top);
	polygon(handVerts[0], handVerts[4], handVerts[5], handVerts[1], xOffset, zOffset, _Left);
	polygon(handVerts[5], handVerts[6], handVerts[2], handVerts[1], xOffset, zOffset, _Back);
	polygon(handVerts[6], handVerts[7], handVerts[3], handVerts[2], xOffset, zOffset, _Right);
	polygon(handVerts[4], handVerts[7], handVerts[3], handVerts[0], xOffset, zOffset, _Front);
}

void drawPerson(int xOffset, int zOffset)
{
	drawHat(xOffset, zOffset);
	drawHead(xOffset, zOffset);
	drawBody(xOffset, zOffset);
	drawLegs(xOffset, zOffset);
	drawArms(xOffset, zOffset);
}

void drawPeople()
{
	int shiftX = 0;
	int shiftZ = 0;

	for (int i = 0; i < 12; i++)
	{
		if (i % 4 == 0)
		{
			shiftX = 0;
			shiftZ -= 60;
		}

		drawPerson(shiftX, shiftZ);

		shiftX -= 100;
	}
}

//Remove for final
void drawLines()
{
	//draw coordinate axis labels
	glLineWidth(1);
	glColor3f(0, 0, 0);
	glRasterPos3i(155, 4, 0);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'X'); //x axis

	glRasterPos3i(-5, 155, 0);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Y'); //y axis

	glRasterPos3i(-0, 4, 170);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Z'); //z axis


	glBegin(GL_LINES);
		glVertex4i(-150, 3, 0, 1);
		glVertex4i(150, 3, 0, 1);
		glVertex4i(0, -150, 0, 1);
		glVertex4i(0, 150, 0, 1);
		glVertex4i(0, 3, -150, 1);
		glVertex4i(0, 3, 150, 1);
	glEnd();
}

//Draw Functions

//Draws an individual tile for the floor
void drawTile(int x, int z, const float color[3]) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color); //set tile material and color for lighting
	glBegin(GL_POLYGON);
		glNormal3f(0, 1, 0); //set normal vector for lighting
		glVertex4i(x, 0, z, 1);
		glVertex4i(x + TILE_SIZE, 0, z, 1);
		glVertex4i(x + TILE_SIZE, 0, z + TILE_SIZE, 1);
		glVertex4i(x, 0, z + TILE_SIZE, 1);
	glEnd();
}

//Draws the floor made of individual tiles alternating in color
void drawFloor() {
	bool isLight = false;
	for (int z = WINDOW_DEPTH ; z >= -WINDOW_DEPTH; z--) {
		if (z % TILE_SIZE == 0) {
			for (int x = -WINDOW_WIDTH ; x <= WINDOW_WIDTH ; x++) {
				if (x % TILE_SIZE == 0) {
					if (isLight) //if this is a light tile
						drawTile(x, z, LIGHT_BLUE); //color it light
					else //otherwise
						drawTile(x, z, DARK_BLUE); //color it dark
					isLight = !isLight;
				}
			}
		}
	}
}

void drawBanner()
{
	float color[] = { .7, 0, 0, 0 };
	glLineWidth(2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glVertex3f(-100, 120, 210);
	glVertex3f(100, 120, 210);
	glVertex3f(100, 30, 210);
	glVertex3f(-100, 30, 210);
	glNormal3f(0, 0, 1);
	glVertex3f(-100, 30, 211);
	glVertex3f(100, 30, 211);
	glVertex3f(100, 120, 211);
	glVertex3f(-100, 120, 211);
	glEnd();
}

void drawBannerSyms()
{
	glBegin(GL_POLYGON);
	glVertex4f(30, 115, 209, 1);
	glVertex4f(2, 95, 209, 1);
	glVertex4f(30, 75, 209, 1);
	glVertex4f(62, 95, 209, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex4f(30, 70, 209, 1);
	glVertex4f(15, 80, 209, 1);
	glVertex4f(15, 55, 209, 1);
	glVertex4f(30, 45, 209, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex4f(30, 70, 209, 1);
	glVertex4f(45, 80, 209, 1);
	glVertex4f(45, 55, 209, 1);
	glVertex4f(30, 45, 209, 1);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex4f(10, 95, 209, 1);
	glVertex4f(10, 45, 209, 1);
	glEnd();

	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex4f(-10, 105, 209, 1);
	glVertex4f(-10, 60, 209,  1);
	glEnd();

	glBegin(GL_LINES);
	glVertex4f(-10, 55, 209, 1);
	glVertex4f(-10, 45, 209, 1);
	glEnd();

	glBegin(GL_LINES);
	glVertex4f(-30, 105, 209, 1);
	glVertex4f(-30, 60, 209,  1);
	glEnd();

	glBegin(GL_LINES);
	glVertex4f(-30, 55, 209, 1);
	glVertex4f(-30, 45, 209, 1);
	glEnd();

	glBegin(GL_LINES);
	glVertex4f(-50, 105, 209, 1);
	glVertex4f(-50, 60, 209,  1);
	glEnd();

	glBegin(GL_LINES);
	glVertex4f(-50, 55, 209, 1);
	glVertex4f(-50, 45, 209, 1);
	glEnd();
}
//Display Callbacks

//Primary Display callback
void displayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	drawLines(); //remove for final
	glutWireCube(50.0); //remove for final
	drawFloor();
	drawPeople();
	drawBanner();
	drawBannerSyms();
	glFlush();
}


// Initialization Functions


//Primary Init Function
void init()
{
	glClearColor(.1, .8, .2, 0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(200.0, 200.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 10.0, 1150.0);

	//lighting
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); //set light color/type
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); //set light position
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
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

//Rotates view based on mouse movement when mouse button is pressed
void motionCallback(int x, int y)
{
  glMatrixMode(GL_MODELVIEW); // switch to model view stack

  float worldCoordX = x - WINDOW_WIDTH;
  float distX = worldCoordX - lastX;

  glRotatef(distX, 0.0, 1.0, 0.0);

  lastX = worldCoordX;

  displayCallback();
}


///Draws info text to info window
void infoInstructions() {
	glClear(GL_COLOR_BUFFER_BIT);					//draw background
	glColor3f(0.1, .20, 0.3);

	//Information strings
	std::string myArray[] = {
		"To circle around the scene:",
		"Press the Left mouse button",
		"and move the mouse left or right"
	};

	for (int i = 0; i < 3; i++) {					//for each line of info text
		//set position to draw from
		glRasterPos2i(-180, 100 - 45 * i);
		for (int j = 0; j < myArray[i].size(); j++) { //for each character in the string
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, myArray[i][j]);
		}
	}
}

///Display callback for info window
void infoDisplayCallback() {
	glClear(GL_COLOR_BUFFER_BIT);					//draw the background
	infoInstructions();								//draw instructions to screen
	glFlush();
}

///Info selection menu for hiding info window
void info_menu(int id) {
	if (id == 1) {
		glutHideWindow();							//hide info window
	}
}


///Window and document initialization
void InfoInit(){


	glClearColor(1, 1, 1, 0);			            // specify a background color: white
	gluOrtho2D(-200, 200, -350, 350);  // specify a viewing area


}


//Main program function
int main(int argc, char **argv){
	//3d window
	glutInit(& argc, argv);			// optional
	glutInitDisplayMode(GLUT_DEPTH);	// optional

	//info window
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(925, 0);
	infoWindowId = glutCreateWindow("Info");

	InfoInit();											//Initialize info window

	glutCreateMenu(info_menu);
	glutAddMenuEntry("CLOSE", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(infoDisplayCallback);


	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 0);
	mainWindowId = glutCreateWindow("Display in 3D");

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
