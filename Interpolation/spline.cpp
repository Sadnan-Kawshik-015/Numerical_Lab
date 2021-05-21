#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define n 4  //for n+1 points

static int Ym = 768, Xm = 1366;

float x[n + 1], a[n + 1], c[n], b[n], d[n];

void cubicSpline(void){
    int i, j;
    float h[n], A[n+1], u[n + 1], z[n + 1];

    for(i = 0; i < n + 1; ++i){ // Data input
        printf("enter the value of x[%d] : ", i);
        scanf("%f", &x[i]);
        printf("enter the value of y[%d] : ", i);
        scanf("%f", &a[i]);
    }

    /** Step 1: calculating hj = xj+1 - xj */
    for(j = 0; j < n; ++j) h[j] = x[j + 1] - x[j];

    /** Step 2 */
    A[0] = A[n] = 0;
    for(j = 1; j < n; ++j)
        A[j] = 3 * (a[j+1] - a[j]) / h[j] - 3 * (a[j] - a[j-1]) / h[j-1];

    /** Step 3 */
    u[0] = 0;
    z[0] = 0;

    /** Step 4 */
    for (i = 1; i < n; ++i) {
        u[i] = h[i] / (2 * (x[i + 1] - x[i - 1]) - h[i - 1] * u[i - 1]);
        z[i] = (A[i] - h[i - 1] * z[i - 1]) / (2 * (x[i + 1] - x[i - 1]) - h[i - 1] * u[i - 1]);
    }

    /** Step 5 */
    z[n] = 0;
    c[n] = 0;

    /** Step 6 */
    for(j = n-1; j >= 0; --j) {
        c[j] = z[j] - u[j] * c[j + 1];
        b[j] = (a[j+1] - a[j]) / h[j] - h[j] * (c[j+1] + 2 * c[j]) / 3;
        d[j] = (c[j+1] - c[j]) / (3 * h[j]);
    }

    /** Step 7 */
    printf("%2s %8s %8s %8s %8s\n", "i", "ai", "bi", "ci", "di");
    for(i = 0; i < n; ++i)
        printf("%2d %8.2f %8.2f %8.2f %8.2f\n", i, a[i], b[i], c[i], d[i]);

}

static void reShape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Xm/2, Xm/2 - 1, -Ym/2, Ym/2 - 1, -1, 1); //Xm*Ym
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void) {
    int i,j;
    float X, Y;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // plotting the curve
    glPushMatrix();
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3ub(255, 100, 255);
    for(i=0; i<=n; i++)
       glVertex2f(x[i], a[i]);
    glEnd();

    glPointSize(1);

    glPushMatrix();
    glColor3ub(128, 128, 128);
    glBegin(GL_LINES);
    glVertex2i(-Xm/2, 0);
    glVertex2i(Xm/2, 0);
    glVertex2i(0, -Ym/2);
    glVertex2i(0, Ym/2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POINTS);
    for(i=0; i<n; i++){
        glColor3ub(255-i*52, i*52, 0);
        X = x[i];
        for(j=0; j<1000; j++){
            X += (x[i+1]-x[i])/1000.0;
            Y = a[i] + b[i]*(X - x[i]) + c[i]*pow((X - x[i]),2.0) + d[i]*pow((X - x[i]),3.0);
            glVertex2f(X, Y);
            //printf("%0.4f  %0.4f\n", X, Y);
        }
    }
    glEnd();
    glPopMatrix();
    glFlush();
    //glutSwapBuffers();
}

static void idle(void) {
    glutPostRedisplay();
}

static void myinit(void) {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char* argv[]) {
    cubicSpline();
    float X, Y;
       for(int i=0; i<n; i++){
        glColor3ub(255-i*52, i*52, 0);
        X = x[i];
        for(int j=0; j<10; j++){
            X += (x[i+1]-x[i])/10.0;
            Y = a[i] + b[i]*(X - x[i]) + c[i]*pow((X - x[i]),2.0) + d[i]*pow((X - x[i]),3.0);
            printf("%0.4f  %0.4f\n", X, Y);
        }
    }

    glutInit(&argc, argv);
    glutInitWindowSize(Xm, Ym);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Spline Curve");
    myinit();
    glutReshapeFunc(reShape);
    glutDisplayFunc(display);
    //glutMouseFunc(OnMouseClick);
    glutIdleFunc(idle);
     //initValues();
    glutMainLoop();
    return EXIT_SUCCESS;
}

