#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

typedef struct {
	int x,y;
} Point;

Point P[4];
int n=-1;
float m=1;
float r=0;
int a=0, b=0;

void MouseEventHandler(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state ==  GLUT_UP)
		{   n++;
			P[n].x=x-300;
			P[n].y=300-y;		printf("\n n=%i x=%d y=%d",n,P[n].x,P[n].y);
			if(n==2){
				//m = float(P[1].y - P[0].y)/float(P[1].x - P[0].x);
				//r = sqrt(pow(P[1].x - P[0].x,2) + pow(P[1].y - P[0].y ,2));
				a = abs(P[1].x - P[0].x);
				b = abs(P[2].y - P[0].y);
				//printf("\n r=%f",r);
				n=-1;
			}
			glutPostRedisplay();
		}
}

void put4pixel(int xc,int yc, int x, int y){
	glBegin(GL_POINTS);
	glVertex2i(x+xc, y+yc);
	glVertex2i(x+xc,-y+yc);
	glVertex2i(xc-x, yc-y);
	glVertex2i(xc-x, yc+y);
	glEnd();
}

void ElipBres(int xc,int yc, int a, int b){

	double x,y,p,x0, y0,a2,b2;
	a2=a*a; b2=b*b;
	x=0; y=b; p=-2*b+1+2*b2/(a2);
	x0=a2/(sqrt(a2+b2)); y0=b2/(sqrt(a2+b2));
	while (x<=x0){

		put4pixel(xc,yc,x,y);
		if (p<0) p+=2*b2*(2*x+3)/a2;
		else{

			p+=4*(1-y)+ 2*b2 * (2*x+3)/a2;
			y--;

		}
		x++;

	}
	x=a; y=0; p=2*a2/b2 - 2*a+1;
	while (y<=y0){

		put4pixel(xc,yc,x,y);
		if (p<0 ) p+=2*a2*(2*y+3)/b2;
		else{

			p+=4*(1-x) + 2*a2*(2*y+3)/b2;
			x--;

		}	
		y++;

	}

}

void MyDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	if(a!=0 && b!=0) {	
		ElipBres(P[0].x, P[0].y, a, b);
		a=0;
		b=0;
	}
	glFlush();
}


int main(int argc,char* arg[]){

	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize (600, 600); 
	glutInitWindowPosition (10, 10); 
	glutCreateWindow("Circle 1");
	gluOrtho2D(-300, 300, -300, 300);
	glClearColor(0,0,0,0);
	glutMouseFunc(MouseEventHandler);	
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
}

