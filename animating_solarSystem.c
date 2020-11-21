#include <stdlib.h>
#include <gl/glut.h>	// System and OpenGL Stuff

static GLfloat angle = 0.0f;	// for Earth system 
static GLfloat angle2 = 360.0f;	// for Mars system
static GLint speed = 35;

void ProcessMenu(int value)
{
	//[Q] write code for speed control / Visibility using switch stmt.
	if (value == 0)
		speed += 10;
	else if (value == 1)
		speed = 35;
	else if (value == 2)
		speed -= 10;
	else if (value == 3)
		glEnable(GL_DEPTH_TEST);
	else if (value == 4)
		glDisable(GL_DEPTH_TEST);

	glutPostRedisplay();  // apply the change to the scene
}


void MyDisplay()
{
	glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 30.0, 300.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glColor3ub(200, 0, 200);
	glutSolidSphere(13.0f, 15, 15);	// Sun

	glPushMatrix();			// remember current position 
		glRotatef(angle, 0.0f, 1.0f, 0.0f);	// rotate earth
		glTranslatef(70.0f, 0.0f, 0.0f);
		glColor3ub(0, 255, 0);
		glutSolidSphere(8.0f, 15, 15);	// Earth

		glPushMatrix();
			glRotatef(angle, 0.0f, 1.0f, 0.0f);  // rotate moon
			glTranslatef(15.0f, 0.0f, 0.0f);
			glColor3ub(255, 255, 0);	// yellow
			glutSolidSphere(2.5f, 15, 15);		// Moon
			glPopMatrix();
		glPopMatrix(); // restore the previous position saved

	// Mars
		glPushMatrix(); //  remember current position
			glRotatef(45.0, 0.0f, 0.0f, 1.0f);// rotate Mars orbit
			glRotatef(angle2, 0.0f, 1.0f, 0.0f);	// rotate mars planet
			glTranslatef(-100.0f, 0.0f, 0.0);	// distance from the sun
			glColor3ub(255,0,0);		// red
			glutSolidSphere(5.0f, 15, 15);				// Mars

		glPushMatrix();
			glRotatef(angle2, 0.0f, 1.0f, 0.0f);		// rotate mars moon
			glTranslatef(10.0f, 0.0f, 0.0f);	// distance from Mars
			glColor3ub(0, 0, 255);
			glutSolidSphere(2.0f, 15, 15);			// Mars Moon
		glPopMatrix();
	glPopMatrix(); // restore the previous position saved

	glutSwapBuffers();
}


void TimerFunc(int value)
{
	angle += 10.0f;	// increase rotation angle for earth and moon 
	if (angle > 360.0f)	// if angle is greater than 360, reset it to 0
		angle = 0.0f;
	angle2 -= 5.0f;// increase rotation angle for Mars and moon 
	if (angle2 < 0.0f)//[Q] if angle2 is below 0, restore it to 360. 
		angle2 = 360.0f;
	glutPostRedisplay(); // apply the angle change to the scene
	glutTimerFunc(speed, TimerFunc, 1); // register Timer callback again
}

void ChangeSize(int w, int h)
{
	//GLfloat nRange = 100.0f;
	GLfloat aspect;

	if (h == 0) h = 1;
	aspect = (GLfloat)w / (GLfloat)h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, aspect, 1.0, 1500.0);

}

int main(int argc, char* argv[])
{
	int nMenu;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Solar System");

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glutReshapeFunc(ChangeSize);

	//[Q] register Display callback function
	glutDisplayFunc(MyDisplay);
	// [Q] Create speed control and visibility menu here
	nMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("slow", 0);
	glutAddMenuEntry("normal", 1);
	glutAddMenuEntry("fast", 2);
	glutAddMenuEntry("depth on", 3);
	glutAddMenuEntry("depth off", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON)
		;
	glutTimerFunc(speed, TimerFunc, 1); // register Timer callback function

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

	return 0;
}