#include "GL/glut.h"
#include <math.h>
#include <stdlib.h>
#include <fstream>

const float pi = 3.141592653589;
GLint ancho = 1300, alto = 650;
GLint xbt1, xbt2, ybt1, ybt2;
GLint Mov = 10;
GLint PivoteTrasX = 650;
GLint PivoteTrasY = 325;
GLfloat RED = 0, GREEN = 0, BLUE = 1;
GLfloat Rf = 0.5, Gf = 0.5, Bf = 1;
GLfloat signoRf = 1, signoGf = 1, signoBf = 1, signoEsc = 1;

bool auxEscalado = NULL;
bool auxRot = NULL;
bool Ymov = false, Xmov = false;
GLfloat rho = 10 * (pi / 180), rhoAux = 1; //CONVERTIR GRADOS A RADIANES
GLfloat tx = 0, ty = 0;
GLint rx, ry;
GLfloat sx = 1, sy = 1;
GLfloat k = 1.0;

GLfloat MatrizPentagono[2][6] = {
	{320, 302, 350, 397, 379, 320},
	{395, 339, 304, 339, 395, 395}, };
GLfloat MAux[2][6] = {
	{320, 302, 350, 397, 379, 320},
	{395, 339, 304, 339, 395, 395}, };
GLfloat MTras[3][3] = {
	{1,0,tx},
	{0,1,ty},
	{0,0,1}, };
GLfloat MRot[3][3] = {
	{cos(rho),sin(rho),0},
	{-sin(rho),cos(rho),0},
	{0,0,1}, };
GLfloat MEsca[3][3] = {
	{sx,0,0},
	{0,sy,0},
	{0,0,1}, };

void plano();
void setPixel(int, int, float, float, float);
void Bersenham(int, int, int, int, float, float, float);
void keyboard(unsigned char, int, int);
void traslacionCircularFigura();
void escaladoFigura();
void rotarFigura();
void moverFigura();
void keyboardKeys(int, int, int);
void limpiar();
void dibujar();
void coloresFondo();

int main(int argc, char** argv) {
	printf("Hey Hola\n");
	printf("Cosas a considerar:\n");
	printf("Deberas tener las MAYUSCULAS ACTIVADA \n");
	printf("Para empezar, oprime W para pintar la figura \n");
	printf("Al desplazarte por el plano con las flechas de direccion, te moveras de 10px en 10px \n");
	printf("Al desplazarte circularme con R, rotaras cada 10 grados respecto a tu nuevo punto pivote \n");
	printf("Al escalar con E, lo haras 10 veces su tamano actual, ya sea para mayor o menor\n");
	glutInit(&argc, argv); // Iniciamos OpenGL
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE); // Iniciamos Ventana
	glutInitWindowPosition(40, 50);
	glutInitWindowSize(ancho, alto);
	glutCreateWindow("Transformaciones Geometricas");
	glutDisplayFunc(plano);
	glutKeyboardFunc(keyboard); // Para poder ingresar por teclado
	glutSpecialFunc(keyboardKeys);
	gluOrtho2D(0, ancho, alto, 0);
	glutMainLoop();
	return 0;
}
void plano() {
	for (int i = 0; i < 5; i++)
	{
		Bersenham(MatrizPentagono[0][i], MatrizPentagono[1][i], MatrizPentagono[0][i + 1], MatrizPentagono[1][i + 1], 0, 0, 0);
	}
	glFlush();
}
void setPixel(int xi, int yi, float r, float g, float b) {
	glPointSize(4);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2f(xi, yi);
	glEnd();
}
void Bersenham(int xi, int yi, int xf, int yf, float R, float G, float B) {
	int Dx, Dy, x, y;
	float m, b;
	Dx = xf - xi;
	Dy = yf - yi;
	if (Dx == 0)
	{
		if (yi <= yf)
		{
			for (y = yi; y <= yf; y++)
			{
				setPixel(xi, y, Rf, Gf, Bf);
			}
		}
		else
		{
			for (y = yf; y <= yi; y++)
			{
				setPixel(xi, y, Rf, Gf, Bf);
			}
		}
	}
	if (Dy == 0)
	{
		if (xi <= xf)
		{
			for (x = xi; x <= xf; x++)
			{
				setPixel(x, yi, Rf, Gf, Bf);
			}
		}
		else
		{
			for (x = xf; x <= xi; x++)
			{
				setPixel(x, yi, Bf, Gf, Rf);
			}
		}
	}
	else
	{
		m = float(Dy) / float(Dx);
		b = yi - (m * xi);
		if (abs(Dx) >= abs(Dy))
		{
			if (xi <= xf)
			{
				for (x = xi; x <= xf; x++)
				{
					y = (m * x) + b;
					setPixel(x, y, Rf, Bf, Gf);
				}
			}
			else
			{
				for (x = xf; x <= xi; x++)
				{
					y = (m * x) + b;
					setPixel(x, y, Rf, Gf, Bf);
				}
			}
		}
		else
		{
			if (yi <= yf)
			{
				for (y = yi; y <= yf; y++)
				{
					x = (y - b) / m;
					setPixel(x, y, Gf, Rf, Bf);
				}
			}
			else
			{
				for (y = yf; y <= yi; y++)
				{
					x = (y - b) / m;
					setPixel(x, y, Bf, Gf, Rf);
				}
			}
		}
	}
}
void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'T':
		traslacionCircularFigura();
		break;
	case 'W':
		auxEscalado = true;
		escaladoFigura();
		break;
	case 'E':
		auxEscalado = false;
		escaladoFigura();
		break;
	case 'R':
		auxRot = true;
		rotarFigura();
		break;
	}
}
void keyboardKeys(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		tx = +Mov;
		Xmov = true;
		moverFigura();
		break;
	case GLUT_KEY_LEFT:
		tx = -Mov;
		Xmov = true;
		moverFigura();
		break;
	case GLUT_KEY_UP:
		ty = -Mov;
		Ymov = true;
		moverFigura();
		break;
	case GLUT_KEY_DOWN:
		ty = +Mov;
		Ymov = true;
		moverFigura();
		break;
	}
}
void traslacionCircularFigura() {

}
void rotarFigura() {
	if (auxRot == true)
	{
		MRot[0][0] = cos(rho * rhoAux);
		MRot[0][1] = -sin(rho * rhoAux);
		MRot[1][0] = sin(rho * rhoAux);
		MRot[1][1] = cos(rho * rhoAux);

		GLfloat xPivote = (PivoteTrasX);
		GLfloat yPivote = (PivoteTrasY);

		for (int i = 0; i < 6; i++)
		{
			MAux[0][i] = (((MRot[0][0] * MatrizPentagono[0][i]) + (MRot[0][1] * MatrizPentagono[1][i])) + xPivote);
			MAux[1][i] = (((MRot[1][0] * MatrizPentagono[0][i]) + (MRot[1][1] * MatrizPentagono[1][i])) + yPivote);
		}
		limpiar();
		dibujar();
	}
	rhoAux++;
	auxRot = false;
}
void escaladoFigura() {
	if (auxEscalado == true)
	{
		k = 1.00; //CONSTANTE QUE DETERMINA EL ESCALADO
		for (int i = 0; i < 6; i++)
		{
			MAux[0][i] = (k * MatrizPentagono[0][i]) + PivoteTrasX * (1 - k);
			MAux[1][i] = (k * MatrizPentagono[1][i]) + PivoteTrasY * (1 - k);
		}
		limpiar();
		dibujar();
	}
	if (auxEscalado == false)
	{
		if (k < 1) {
			signoEsc = 1;
		}
		if (k >= 4) {
			signoEsc = (-1);
		}
		k += 1 * signoEsc;

		GLfloat xPivote  = 350 * (1 - k);
		GLfloat yPivote = 350 * (1 - k);

		MEsca[0][0] = MEsca[1][1] = k;
		for (int i = 0; i < 6; i++)
		{
			MAux[0][i] = MEsca[0][0] * MatrizPentagono[0][i] + xPivote;
			MAux[1][i] = MEsca[1][1] * MatrizPentagono[1][i] + yPivote;
		}
		limpiar();
		dibujar();
	}
	auxEscalado = NULL;
	k += .2;
}
void moverFigura() {
	if (Xmov == true)
	{
		PivoteTrasX += tx;
		MTras[0][2] = tx;
		for (int i = 0; i < 6; i++) {
			MAux[0][i] = ((MTras[0][0] * MAux[0][i]) + (MTras[1][0] * MAux[1][i])) + MTras[0][2];
		}
		limpiar();
		dibujar();
	}

	if (Ymov == true)
	{
		PivoteTrasY += ty;
		MTras[1][2] = ty;
		for (int i = 0; i < 6; i++) {
			MAux[1][i] = (MTras[0][1] * MAux[1][i]) + (MTras[1][1] * MAux[1][i]) + MTras[1][2];
		}
		limpiar();
		dibujar();
	}
	Ymov = Xmov = NULL;
	tx = ty = 0;
}
void limpiar() {
	coloresFondo();
	glClearColor(Rf, Gf, Bf, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	dibujar();
}
void dibujar() {
	for (int i = 0; i < 5; i++)
	{
		Bersenham(MAux[0][i], MAux[1][i], MAux[0][i + 1], MAux[1][i + 1], 0,0, 0);
	}
	glFlush();
}
void coloresFondo()
{ /*
	if (Rf < 0) //VARIACION DE ROJO
	{
		signoRf = 1;
	}
	if (Rf >= 1)
	{
		signoRf = (-1);
	}
	Rf += 0.1 * signoRf;
	// VARIACION DE VERDE
	if (Gf < 0)
	{
		signoGf = 1;
	}
	if (Gf >= 1)
	{
		signoGf = (-1);
	}
	Gf += 0.5 * signoGf;
	//VARIACION DE AZUL
	if (Bf < 0)
	{
		signoBf = 1;
	}
	if (Bf >= 1)
	{
		signoBf = (-1);
	}
	Bf += 0.2 * signoBf; */
}