/*Assignment -3 : Implementation of lagrence polynomial and Newton's forward difference method polynomial

Author : Sadnan Kibria Kawshik

Roll :  AE-15*/

#include <bits/stdc++.h>
#include <GL/glut.h>

#define W 1600
#define H 1000
#define N 4
using namespace std;

struct Data /*point(x,y)*/
{
    float x, y;
};

Data f[] = {{-200,0}, {-100,30.10}, {0, 47.71}, {100, 60.21}};/*4 given points*/
float divTable[10][10];/*divided difference table for newton's divided difference method*/
// calculating u mentioned in the formula
float u_cal(float u, int n)
{
	float temp = u;             /**used to calculate u terms multiplication**/
	for (int i = 1; i < n; i++)
		temp = temp * (u - i);
	return temp;
}

// calculating factorial of given number n
int fact(int n)
{
	int f = 1;
	for (int i = 2; i <= n; i++)
		f *= i;
	return f;
}



void dividedDiffTable(Data f[], float divTable[][10], int n)
/*formulation of divided difference table
Here,div[0][0],div[1][0],div[2][0],div[3][0] are y values of the point,div[0][1] will be same as f[x0,x1] and
div[1][1] is equivalent to f[x1,x2],div[2][1] is equivalent to f[x2,x3],div[0][2] is equivalent to f[x0,x1,x2],
div[1][2] is equivalent to f[x1,x2,x3] and div[0][3] is equivalent to f[x0,x1,x2,x3]
*/
{
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            divTable[j][i] = (divTable[j+1][i - 1] - divTable[j][i - 1]);

        }
    }
}

/*Implementation of newton's divided difference ,here the formula for newton's divided difference is

f(x)=f(x0)+(x-x0)f[x0,x1]+(x-x0)(x-x1)f[x0,x1,x2]+....+(x-x0)(x-x1)...(x-xk-1)f[x0,x1,...,xk]

Here, f[x0,x1]=f(x0)-f(x1)/(x0-x1),f[x0,x1,x2]=f[x0,x1]-f[x1,x2]/(x0-x2)*/

float newton_divided_method(float xi, Data f[], float divTable[][10], int n)
{
    float sum = divTable[0][0];/*initialize f(x)=f(x0)*/
    float u = (xi - f[0].x) / (f[1].x - f[0].x);

    for (int i = 1; i < n; i++)
    {
        sum = sum + (u_cal(u, i) * divTable[0][i])/fact(i) ;/*applying the formula*/
    }
    return sum;
}

/*for debugging purpose*/
void printDiffTable(float divTable[][10],int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            cout << "div"<<"[ "<<i<<"]"<<"["<<j<<"] = "<<divTable[i][j] <<endl;
        }

    }
}
double lagrence(Data f[], double xi, int n)
{
    double yi = 0; // Initialize result

    for (int i=0; i<n; i++)
    {
        // Compute individual terms of above formula
        double L = f[i].y;
        for (int j=0; j<n; j++)
        {
            if (j!=i)
                L *= (xi - f[j].x)/double(f[i].x - f[j].x);
        }

        // Add current term to result
        yi += L;
    }
    return yi;
}



void display(void)  //callback
{
    int i;
    double X,Y;

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    /*drawing x and y axis*/

    glColor3ub(128, 128, 128);
    glPointSize(1);
    glBegin(GL_LINES);
    glVertex2i(0,-H/2);
    glVertex2i(0, H/2);
    glVertex2i(-W/2,0);
    glVertex2i(W/2,0);
    glEnd();

    /*Plotting given points*/

    glColor3ub(255, 0, 255);
    glPointSize(5);
    glBegin(GL_POINTS);
    for (i = 0; i < N; i++)
    {
        glVertex2d(f[i].x, f[i].y);
    }
    glEnd();

  /*  Curve for lagrence polynomial from x=-800 to 800

    glPointSize(1);
    glColor3ub(0, 255, 0);
    glBegin(GL_POINTS);
    for(X = -800.0; X < 800; X+=0.01)
    {
        Y=lagrence(f, X, N);
        glVertex2d(X,Y);
    }
    glEnd();
*/
    /*Curve for newton's divided difference method polynomial from x=-800 to 800*/

   glPointSize(1);
    glColor3ub(255, 0, 0);
    glBegin(GL_POINTS);
    for(X = -800.0; X < 800.0; X+=0.01)
    {
        Y=newton_divided_method(X,f,divTable,N);
        glVertex2d(X,Y);/*as the curves overlap so it has been shifted 5 unit along y axis*/
    }
    glEnd();

    glPopMatrix();
    glFlush();
}

void reshape(int w, int h)   //projection setting
{
    GLfloat aspect = (GLfloat) w / (GLfloat) h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-W/2, W/2, -H/2, H/2, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()  //lighting setting
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char **argv)
{
    for(int i=0;i<N;i++)
    {
        divTable[i][0]=f[i].y;
    }

    dividedDiffTable(f,divTable,N);/*formulation of divided difference table*/
    printDiffTable(divTable,N);/*printing the table for debugging purpose*/
    glutInit(&argc, argv); //initialization
    glutInitDisplayMode(GLUT_RGB); //24 bit color
    glutInitWindowSize(W, H); //WxH window
    glutCreateWindow("Lagrange Polynomial and Newton's Divided Difference Method Polynomial"); //title
    init();//lighting
    glutReshapeFunc(reshape);//projection
    glutDisplayFunc(display);//callback
    glutMainLoop();
    return(0);
}
