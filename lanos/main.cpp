#include<windows.h>
#include <GLU/GL.H>
#include <GLU/glut.h>
#include <GLU/GLAux.h>


GLuint car, kap, bag, win_lob, win_l_1;
float car_angle = 180;
float kap_angle = 0;
float bag_angle = 0;
float i = 0;
GLuint texture;

void light()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	float light_ambient[] = { 0.1f,0.1f,0.1f,1.0f };
	float light_diffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	float light_specular[] = { 1.0f,1.0f,1.0f,1.0f };
	float light_position[] = { -1000.0f,500.0f,0.0f,1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT_AND_BACK, GL_POSITION, light_ambient);
}
void textures() {

	AUX_RGBImageRec *textures = auxDIBImageLoadA("win_glass.bmp");
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textures->sizeX, textures->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textures->data);
}
void reshape(int w, int h)
{
	textures();
	glEnable(GL_TEXTURE_2D);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, (GLfloat)w / (GLfloat)h, 0.5f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	//gluLookAt(100, 100, -100, 0, 0, 0, 0, 1, 0);
}
GLuint loadDetail(char* filename);
void rotate_car(float l_car_angle, GLuint l_car) {
	glTranslatef(0, 0, -250);
	glScalef((GLfloat)0.5, (GLfloat)0.5, (GLfloat)0.5);
	glRotatef(l_car_angle, 0, 1, 0);
	glCallList(l_car);
}
void rotate_kap(float l_kap_angle, GLuint l_kap) {
	glRotatef(-l_kap_angle, 1, 0, 0);
	glTranslatef(0, -l_kap_angle*2.5, 0);
	glCallList(l_kap);
	glTranslatef(0, l_kap_angle*2.5, 0);
	glRotatef(l_kap_angle, 1, 0, 0);
}
void rotate_bag(float l_bag_angle, GLuint l_bag) {
	glRotatef(l_bag_angle, 1, 0, 0);
	glTranslatef(0, -l_bag_angle*4.4, 0);
	glCallList(l_bag);
	glTranslatef(0, l_bag_angle*4.4, 0);
	glRotatef(-l_bag_angle, 1, 0, 0);
}
void drawCar()
{
	rotate_car(car_angle, car);
	rotate_kap(kap_angle, kap);
	rotate_bag(bag_angle, bag);
	glCallList(win_lob);
	glCallList(win_l_1);
	car_angle = car_angle + 0.1f;
	if (car_angle>360) car_angle = car_angle - 360;
	if (i > 30) i= -30; else i += 0.1;
	kap_angle = (i < 0) ? (0 - i) : i;
	bag_angle = (i < 0) ? (0 - i) : i;
}

void display(void)
{
	glClearColor((GLclampf)0.0, (GLclampf)0.0, (GLclampf)0.8, (GLclampf)1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	drawCar();
	glutSwapBuffers(); //swap the buffers
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("lanos");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	car = loadDetail("karkas2.obj");
	kap = loadDetail("kap1.obj");
	bag = loadDetail("bag1.obj");
	//win_lob = loadDetail("win_lob.obj");
	//win_l_1 = loadDetail("win_l_1.obj");
	light();
	textures();
	glutMainLoop();
	return 0;
}