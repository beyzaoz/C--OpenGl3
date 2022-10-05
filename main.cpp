#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <bits/stdc++.h>
#include <GL/glut.h>


const double PI = 3.1415926535;
float** transformation;
int length =3;
int numberPoints;

struct point{
        int points[2];
};
point* points;


void myInit (void)
{
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glColor3f(0.0f, 0.0f, 0.0f);
        glPointSize(4.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}



float** multiplyMatrix(float** a, float** b, int length){
        float** result = new float*[length];
        for(int i=0; i<length; i++){
                result[i] = new float[length];
        }
        for(int i=0; i<length; i++){
                for(int j=0; j<length; j++){
                        result[i][j] = 0;
                }
        }

        for(int i=0; i<length; i++){
                for(int j=0; j<length; j++){
                        for(int k=0; k<length; k++){
                                result[i][j] = result[i][j] + (a[i][k] * b[k][j]);
                        }
                }
        }

        return result;
}

float* multiplyVector(float** a, float* b, int length){
        float* result = new float[length];
        for(int i=0; i<length; i++){
                result[i] = 0;
        }

        for(int i=0; i<length; i++){
                for(int j=0; j<length; j++){
                        result[i] = result[i] + (a[i][j] * b[j]);
                }
        }

        return result;
}

float** createI(int length){
        float** result = new float*[length];
        for(int i=0; i<length; i++){
                result[i] = new float[length];
        }

        for(int i=0; i<length; i++){
                for(int j=0; j<length; j++){
                        if(i!=j)
                                result[i][j] = 0;
                        else
                                result[i][j] = 1;
                }
        }
        return result;
}

float** translateAbout(point a, int length){
        float** result = createI(length);

        for(int i=0; i<length-1; i++){
                result[i][length-1] = a.points[i];
        }

        return result;
}

float** rotateAbout(float theta, int length){
        float** result = createI(length);

        result[0][0] = cos(theta*PI/180);
        result[0][1] = -sin(theta*PI/180);
        result[1][0] = sin(theta*PI/180);
        result[1][1] = cos(theta*PI/180);

        return result;
}

float** scaleAbout(int scale_x, int scale_y, int length){
        float** result = createI(length);

        result[0][0] = scale_x;
        result[1][1] = scale_y;
        return result;
}

void display(void){
    for (int i=0;i<numberPoints;i++)
        {
                float xp,yp;
                xp=transformation[0][0]*points[i].points[0]+transformation[0][1]*points[i].points[1]+transformation[0][2];
                yp=transformation[1][0]*points[i].points[0]+transformation[1][1]*points[i].points[1]+transformation[1][2];

                glBegin(GL_LINES);
                glColor3f (1.0, 1.0, 1.0);
                glPointSize(4.0);
                glVertex2f(xp,yp);
                if(i!=numberPoints) i++;
                else i=0;
                xp=transformation[0][0]*points[i].points[0]+transformation[0][1]*points[i].points[1]+transformation[0][2];
                yp=transformation[1][0]*points[i].points[0]+transformation[1][1]*points[i].points[1]+transformation[1][2];
                i--;
                glVertex2f(xp,yp);
        glEnd();
        }

    glFlush();
}

int main(int argc, char** argv){

    cout<<"Enter number of points :";
        cin>>numberPoints;
    cout<<"Enter the x,y co-ordinates of each point\n";
    points = new point[numberPoints];
    for(int i=0; i<numberPoints; i++){
        cin>>points[i].points[0]>>points[i].points[1];
        }


        point translateTo;
    cout<<"Enter the x,y co-ordinates to translate to :\n ";
    cin>>translateTo.points[0]>>translateTo.points[1];
        float theta;
    cout<<"Enter the angle to rotate the figure about :";
    cin>>theta;
        int scale_x, scale_y;
    cout<<"Enter the scaling factor for x and y : \n";
    cin>>scale_x>>scale_y;

    float** T = translateAbout(translateTo,length);
    float** R = rotateAbout(theta,length);
    float** S = scaleAbout(scale_x,scale_y,length);

    transformation = multiplyMatrix(T,multiplyMatrix(R,S, length),length);


        glutInit(&argc,argv);
        glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Basic Transformation");
    glutDisplayFunc(display);
        myInit();
    glutMainLoop();
        return 0;
}
