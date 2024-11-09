#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>

struct Point {
    float x, y;
};

std::vector<Point> shape;  

void multiplyMatrixVector(const float matrix[3][3], float &x, float &y) {
    float tx = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2]*1;
    float ty = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2]*1;
    x = tx;
    y = ty;
}

void translateShape(float tx, float ty) {
    float matrix[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {tx, ty, 1}
    };
    for (int i = 0; i < shape.size(); ++i) {
        multiplyMatrixVector(matrix, shape[i].x, shape[i].y);
        shape[i].x += tx;
        shape[i].y += ty;
    }
    
}

void scaleShape(float sx, float sy, float x0, float y0) {
    float matrix[3][3] = {
        {sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1}
    };
    for (int i = 0; i < shape.size(); ++i) {
        multiplyMatrixVector(matrix, shape[i].x, shape[i].y);
    }
}

void rotateShape(float angle, float x0, float y0) {
    float rad = angle * M_PI / 180.0;
    float cosA = cos(rad);
    float sinA = sin(rad);
    float matrix[3][3] = {
        {cosA, sinA, 0},
        {-sinA, cosA, 0},
        {0, 0, 1}
    };
    for (int i = 0; i < shape.size(); ++i) {
        multiplyMatrixVector(matrix, shape[i].x, shape[i].y);
    }
}

void reflectX() {
    float matrix[3][3] = {
        {1, 0, 0},
        {0, -1, 0},
        {0, 0, 1}
    };
    for (int i = 0; i < shape.size(); ++i) {
        multiplyMatrixVector(matrix, shape[i].x, shape[i].y);
    }
}
void reflectY() {
    float matrix[3][3] = {
        {-1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    for (int i = 0; i < shape.size(); ++i) {
        multiplyMatrixVector(matrix, shape[i].x, shape[i].y);
    }
}
void reflectO() {
    float matrix[3][3] = {
        {-1, 0, 0},
        {0, -1, 0},
        {0, 0, 1}
    };
    for (int i = 0; i < shape.size(); ++i) {
        multiplyMatrixVector(matrix, shape[i].x, shape[i].y);
    }
}

void reflectLine(float a, float b) {
    float matrix[3][3];

    float denominator = 1 + a * a;
    matrix[0][0] = (1 - a * a) / denominator;
    matrix[0][1] = (2 * a) / denominator;
    matrix[0][2] = (2 * a * b) / denominator;
    
    matrix[1][0] = (2 * a) / denominator;
    matrix[1][1] = (a * a - 1) / denominator;
    matrix[1][2] = (2 * b) / denominator;

    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;

    for (int i = 0; i < shape.size(); ++i) {
        multiplyMatrixVector(matrix, shape[i].x, shape[i].y);
    }
}

void drawLine(float a, float b) {
    glBegin(GL_LINES);
    float x1 = -50; 
    float y1 = a * x1 + b;  
    float x2 = 50;  
    float y2 = a * x2 + b;  

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < shape.size(); ++i) {
        glVertex2f(shape[i].x, shape[i].y);
    }
    
    glEnd();
    
	drawLine(-1, 0);
	
    glutSwapBuffers();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
    glMatrixMode(GL_MODELVIEW);
	
    shape.push_back({10, 20});
    shape.push_back({20, 0});
    shape.push_back({10, 0});
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        translateShape(1, 1);
        break;
    case '2':
        scaleShape(1.1, 1.1, 0, 0);
        break;
    case '3':
        rotateShape(10, 0, 0);
        break;
    case '4':
        reflectX();
        break;
    case '5':
        reflectY();
        break;
    case '6':
        reflectO();
        break;
    case '7':
    	reflectLine(-1, 0);
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Transformations");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

