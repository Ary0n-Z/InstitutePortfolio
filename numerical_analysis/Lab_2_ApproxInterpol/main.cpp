#include <string>
#include "Approximation.h"
#include <GL/GLUT.h>
#include <iostream>
#include "CSVFileReader.h"
#include <math.h>

using namespace std;
vector<Point> readTable(const char* filepath);
void processSpecialKeys(int key, int x, int y);

struct World {
	float left, right, bottom, top;
} world;

vector<Point> pointsApprox1;
vector<Point> pointsApprox2;

vector<Point> mainPointsApprox;
float max(const vector<Point>& v) {
	float ma = 0;
		for (auto a : v) if (a.y > ma)ma = a.y;
	return ma;
}
float min(const vector<Point>& v) {
	float mi = 0;
	for (auto a : v) if (a.y < mi)mi = a.y;
	return mi;
}
void Init(unsigned degree, double step){
	world.left = mainPointsApprox[0].x - 1; 
	world.right = mainPointsApprox[mainPointsApprox.size() - 1].x + 1; 
	pointsApprox1 = LeastSquaresPolynomialApprox(mainPointsApprox, degree, step);

	cout << "Points:\n";
	for (int i = 0; i < pointsApprox1.size(); i++)
		cout << "x = " << pointsApprox1[i].x << " y = " << pointsApprox1[i].y << '\n';

	
	pointsApprox2 = BesselPolynomialsApproximation(mainPointsApprox, degree, step);
	cout << "Points:\n";
	for (int i = 0; i < pointsApprox2.size(); i++)
		cout << "x = " << pointsApprox2[i].x << "\t y = " << pointsApprox2[i].y << '\n';

	float m1 = max(pointsApprox1), m2 = max(pointsApprox2);
	world.top = (m1 > m2?m1:m2) + 1;
	m1 = min(pointsApprox1), m2 = min(pointsApprox2);
	world.bottom = (m1 < m2 ? m1 : m2) -1;	
	cout << "\n\n\tRed - LeastSquaresPolynomialApprox\n Green - BesselPolynomialsApproximation\n";

}
vector<Point> readTable(const char* filepath) {
	CSVFileReader fr(filepath);
	return fr.readTable();
}
void reshape(int w, int h);
void display();
int width, height;
void startGlut(unsigned degree, double step,unsigned func) {
	if(func == 1)
		mainPointsApprox = readTable("1.csv");
	else {
		for (float i = -2; i <= 2; i += 0.5)
			mainPointsApprox.push_back({ i, sin(5 * i) * exp(i) });
	}


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutCreateWindow("Approximation");
	glClearColor(1, 1, 1, 0);
	Init(degree, step);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutSpecialFunc(processSpecialKeys);
	glutMainLoop();

}

int main(int argc, char * argv[])
{
	unsigned int degree = 0, func = 1;;
	double step;
	
	cout << "degree >>";
	cin >> degree;
	cout << "step >>";
	cin >> step;
	cout << "func >>";
	cin >> func;
	startGlut(degree, step, func);	
	return 0;
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		gluOrtho2D(
			world.left,
			world.right,
			world.bottom *(GLfloat)h / (GLfloat)w,
			world.top *(GLfloat)h / (GLfloat)w);
	else
		gluOrtho2D(
			world.left*(GLfloat)w / (GLfloat)h,
			world.right*(GLfloat)w / (GLfloat)h,
			world.bottom,
			world.top);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_LINES);
	glVertex2f(0, world.top);
	glVertex2f(0, world.bottom);
	glVertex2f(world.left, 0);
	glVertex2f(world.right, 0);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < pointsApprox1.size();i++)
		glVertex2f(pointsApprox1[i].x, pointsApprox1[i].y);
	glEnd();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < pointsApprox2.size(); i++)
		glVertex2f(pointsApprox2[i].x, pointsApprox2[i].y);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	for (int i = 0; i < mainPointsApprox.size(); i++)
		glVertex2f(mainPointsApprox[i].x, mainPointsApprox[i].y);
	glEnd();

	glutSwapBuffers();
}

void processSpecialKeys(int key, int x, int y) {
	glMatrixMode(GL_MODELVIEW);

	switch (key) {
	case GLUT_KEY_UP:
		glTranslated(0, 1, 0);
		break;
	case GLUT_KEY_DOWN:
		glTranslated(0, -1, 0);
		break;
	case GLUT_KEY_LEFT:
		glTranslated(-1, 0, 0);
		break;
	case GLUT_KEY_RIGHT:
		glTranslated(1, 0, 0);
		break;
	case GLUT_KEY_HOME:
		glScaled(1.2, 1.2, 1);
		break;
	case GLUT_KEY_END:
		glScaled(0.8,0.8,1);
		break;
	}

	glutPostRedisplay();
}