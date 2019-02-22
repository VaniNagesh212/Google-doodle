#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <iostream>
#include<GL/glut.h>
#include<math.h>
#define PI 3.1416

void mydisplay();//decides which screen has to be displayed next
void drawObj();//draws the corresponding objects wrt string google
void animateObj();//applies animation to the drawed object
void* doSomeThing(void* arg);//to create a thread for background music
void displayCall();//to draw string google
void frontscreen();//to draw front screen
void myKeyboardFunc();//to specify the key board events
void drawstring(float,float,float,char*);//inorder to draw the text on front screen
void demo_menu(int);//to select the menu ids
void spin();//to apply animation by calling this in glutIdlefunction

int thr;
pthread_t tid;

static float theta=0.0;
static float scaling=1.0;
static float shearx=1.0f,sheary=0.0f;
int i;
GLfloat angle;

//int p,q;
int flag=0;

void *currentfont;//if data type is void * A program can probably convert a pointer to any type of data A program can probably convert a pointer to any type of data

//matrix for applying  shear transformation
GLfloat m[16]={1.0f, 0.0f, 0.0f, 0.0f,1.0f, 1.0f, 0.0f, 0.0f,0.0f, 0.0f, 1.0f, 0.0f,0.0f, 0.0f, 0.0f, 1.0f};


void spin()
{
    theta+=0.8;//for rotation
    if(theta>15.0)
    theta=-15;
    scaling+=0.009;//for scaling
    if(scaling>1.5)
    scaling-=0.5;
    shearx-=0.009;//to apply shear
    m[4]=shearx;
    if(shearx<0.0)
    {
        shearx=+0.5f;
        m[4]=shearx;
    }
    glutPostRedisplay();//marks the current window as needing to be redisplayed.
    glutSwapBuffers();
}


void drawstring(float x,float y,float z,char *string)
{
    char *c;
    glRasterPos3f(x,y,z);
    for(c=string;*c!='\0';c++)
    {
        glutBitmapCharacter(currentfont,*c);
    }
}

void frontscreen(void)
{
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    currentfont=GLUT_BITMAP_HELVETICA_18;
    glColor3f(0,0,1);
    drawstring(40.0,90.0,0.0,"PESIT BSC");
    glColor3f(0.7,0,1);
    drawstring(20,82,0.0,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
    glColor3f(1,0.5,0);
    drawstring(25,75,0.0,"A MINI PROJECT ON COMPUTER GRAPHICS");
    glColor3f(1,0,0);
    drawstring(30,60,0.0,"PROJECT TITLE: GOOGLE DOODLE");
    glColor3f(1,0.5,0);
    drawstring(10,50,0.0,"BY:");
    glColor3f(0.5,0,0.5);
    drawstring(5,40,0.0,"Srihari Joshi(1PE15CS162)");
    glColor3f(0.5,0,0.5);
    drawstring(5,34,0.0,"Srujana K(1PE15CS164)");
    glColor3f(1,0.5,0);
    drawstring(75,50,0.0,"GUIDES:");
    glColor3f(0.0,0.5,0.0);
    drawstring(73,40,0.0,"EVLIN VIDYULATHA");
    glColor3f(0.0,0.5,0.0);
    drawstring(73,34,0.0,"LAKSHMI");
    glColor3f(1,0.1,1);
    drawstring(32,10,0.0,"PRESS ENTER TO START");
    glFlush();
    glutSwapBuffers();
    glFlush();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch(key)
    {
        case 13:if(flag==0) //Ascii of 'enter' key is 13
                {
                    flag=1;
                    break;
                }
                if(flag==1)
                {
                    flag=2;
                    break;
                }
                if(flag==2)
                {
                    flag=3;
                    thr = pthread_create(&(tid), NULL, &doSomeThing, NULL);
                    sleep(0.5);
                    break;
                }
    }
    mydisplay();
}

void displayCall()
{
      glClearColor(1.0,1.0,1.0,0.0);
      glClear(GL_COLOR_BUFFER_BIT);
      glLineWidth(5);
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1,0xF00F);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 500.0);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(2, 2, 2, 2, 0.0, 0.0, 0.0, 1.0, 0.0);
      glPushMatrix();
      glScalef(0.0035,0.008,0.008);
      glTranslatef(300, 100.0, 0.0);
      glClearColor(0.0,0.0,0.0,0.0);
      glColor3f(0.5,0,0.5);

      glColor3f(0.0,0.0,1.0);
      glutStrokeCharacter(GLUT_STROKE_ROMAN, 'G');

      glColor3f(1.0,0.0,0.0);
      glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');

      glColor3f(1.0,1.0,0.0);
      glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');

      glColor3f(0.0,0.0,1.0);
      glutStrokeCharacter(GLUT_STROKE_ROMAN, 'g');

      glColor3f(0.0,1.0,0.0);
      glutStrokeCharacter(GLUT_STROKE_ROMAN, 'l');

      glColor3f(1.0,0.0,0.0);
      glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
      glPopMatrix();
      glutSwapBuffers();
    }

void mydisplay(void)
{
        glClear(GL_COLOR_BUFFER_BIT);
        if(flag==0)
            frontscreen();
        if(flag==1)
            displayCall();
        if(flag==2)
            drawObj();
        if(flag==3)
            animateObj();
}

void init()
{
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, 100, 0, 100);
      glColor3f(1.0, 1.0, 1.0);
}

void drawObj()
{
        glClearColor(0.0,0.0,0.0,0.0);
        glShadeModel(GL_FLAT);//Specifies a symbolic value representing a shading technique. Accepted values are GL_FLAT and GL_SMOOTH. The initial value is GL_SMOOTH.
        glViewport(0,0,(GLsizei)1000,(GLsizei)1000);//inorder to define where it has to be displayed
        glMatrixMode(GL_PROJECTION);//specify which matrix is the current matrix
        glLoadIdentity();//to initialize projection matrix stack with identity matrix
        glFrustum(-1.0,1.0,-1.0,1.0,1.5,20.0);//multiply the current matrix by a perspective matrix
        glMatrixMode(GL_MODELVIEW);
        glLineWidth(3);

        glClear(GL_COLOR_BUFFER_BIT);//to clear the screen
        glColor3f(1.0,1.0,1.0);
        glLoadIdentity();
        gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);//define a viewing transformation

        glPushMatrix();//following two transformations are applicable to all objects
        glScalef(1.5,0.9,1.0);
        glTranslatef(0.5,-0.5,0.0);;

        //instead of 'l'
        glPushMatrix();//for drawing candle
        glScalef(1.0,1.3,1.0);
        glTranslatef(0.15,-0.18,0.0);
        glColor3f(0.0,1.0,0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.25,0.25);
        glVertex2f(0.25,0.75);
        glVertex2f(0.35,0.75);
        glVertex2f(0.35,0.25);
        glEnd();

        glBegin(GL_LINES);//to draw a line in between candle
        glVertex2f(0.30,0.35);
        glVertex2f(0.30,0.65);
        glEnd();

        glColor3f(1.0,1.0,0.0);//to draw yellow light
        glScalef(0.90,3.0,0.0);
        glTranslatef(0.23,0.19,0.09);
        /*glutSolidCone(0.03,0.08,20,90);
        glColor3f(0.0,0.0,0.0);
        glutSolidCone(0.025,0.08,20,90);*/
        glBegin(GL_TRIANGLES);
        glVertex2f(0.10f,0.10f);
        glVertex2f(0.15f,0.15f);
        glVertex2f(0.20f,0.10f);
        glEnd();

        glPopMatrix();

        glPushMatrix();//to draw snow flake instead of G
        glTranslatef(-1.5,-1.07,0.0);
        glScalef(1.5,2.0,0.5);
        //snowflake
        glColor3f(0.0,0.0,1.0);
        glBegin(GL_LINES);
            glVertex2f(0.25,0.60);                  //s-n
            glVertex2f(0.25,01.00);

            glVertex2f(0.05,0.80);                   //w-e
            glVertex2f(0.45,0.80);

            glVertex2f(0.10,0.65);                  //sw-ne
            glVertex2f(0.40,0.95);

            glVertex2f(0.40,0.65);                  //se-nw
            glVertex2f(0.10,0.95);

            glVertex2f(0.25,0.90);                  //flake on north
            glVertex2f(0.28,0.93);
            glVertex2f(0.25,0.90);
            glVertex2f(0.22,0.93);

            glVertex2f(0.25,0.70);                  //flake on south
            glVertex2f(0.28,0.67);
            glVertex2f(0.25,0.70);
            glVertex2f(0.22,0.67);

            glVertex2f(0.35,0.80);                  //flake on east
            glVertex2f(0.38,0.83);
            glVertex2f(0.35,0.80);
            glVertex2f(0.38,0.77);

            glVertex2f(0.15,0.80);                  //flake on west
            glVertex2f(0.12,0.83);
            glVertex2f(0.15,0.80);
            glVertex2f(0.12,0.77);

            glVertex2f(0.37,0.87);                  //flake on north-east
            glVertex2f(0.32,0.87);
            glVertex2f(0.32,0.92);
            glVertex2f(0.32,0.87);

            glVertex2f(0.18,0.73);                  //flake on south-west
            glVertex2f(0.18,0.68);
            glVertex2f(0.18,0.73);
            glVertex2f(0.13,0.73);

            glVertex2f(0.32,0.73);                  //flake on south-east
            glVertex2f(0.37,0.73);
            glVertex2f(0.32,0.73);
            glVertex2f(0.32,0.68);

            glVertex2f(0.18,0.87);                  //flake on north-west
            glVertex2f(0.18,0.92);
            glVertex2f(0.18,0.87);
            glVertex2f(0.13,0.87);
        glEnd();
        glPopMatrix();


    //instead of 'e' new code to make gift box
    glPushMatrix();
    glTranslatef(-0.8,-1.13,0.0);
    glScalef(1.0,2.0,1.0);
    glBegin(GL_POLYGON);//to draw that white color box

            glColor3f(0.90,0.91,0.98);
            glVertex2f(1.450,0.600);
            glVertex2f(1.650,0.600);

            glVertex2f(01.650,0.600);
            glVertex2f(01.650,0.800);

            glVertex2f(01.650,0.800);
            glVertex2f(01.450,0.800);

            glVertex2f(01.450,0.800);
            glVertex2f(01.450,0.600);

    glEnd();
    glFlush();

    glScalef(1.0,0.4,1.0);//to draw vertical red tape
    glTranslatef(0.0,1.40,0.0);
    glBegin(GL_POLYGON);
            glColor3f(0.85 , 0.09, 0.09 );
            glVertex2f(01.540,0.600);
            glVertex2f(01.560,0.600);

            glVertex2f(1.560,0.0600);
            glVertex2f(1.560,0.0800);

            glVertex2f(1.560,0.0800);
            glVertex2f(1.540,0.0800);

            glVertex2f(1.540,0.0800);
            glVertex2f(1.540,0.0600);

    glEnd();
    glFlush();

    glTranslatef(0.0,-0.3,0.0);//to draw horizontal red tape
    glBegin(GL_POLYGON);
            glColor3f(  0.85 , 0.09, 0.09);
            glVertex2f(1.450,0.730);
            glVertex2f(1.650,0.730);

            glVertex2f(1.650,0.730);
            glVertex2f(1.650,0.750);

            glVertex2f(1.650,0.750);
            glVertex2f(1.450,0.750);

            glVertex2f(1.450,0.750);
            glVertex2f(1.450,0.730);

    glEnd();
    glFlush();

    glScalef(1.5,1.55,0.0);//to make that tying kind of tape on gift box
    glTranslatef(-0.52,-0.22,0.0);
        glBegin(GL_POLYGON);
            glColor3f(  0.85 , 0.09, 0.09 );
            glVertex2f(1.550,0.800);
            glVertex2f(1.640,0.870);

            glVertex2f(1.640,0.870);
            glVertex2f(1.600,0.810);

            glVertex2f(1.600,0.810);
            glVertex2f(1.550,0.800);

            glVertex2f(1.550,0.800);
            glVertex2f(1.500,0.840);

            glVertex2f(1.500,0.840);
            glVertex2f(1.520,0.880);

            glVertex2f(1.520,0.880);
            glVertex2f(1.550,0.800);

        glEnd();
    glPopMatrix();

        //bell code instead of second 'o'
        glPushMatrix();
        glTranslatef(-1.7,-3,0.0);
        glScalef(1.2,5.4,1.0);
        float rr1 = 0.020; // Radius of circle.
        float xx1 = 1.150; // X-coordinate of center of circle.
        float yy1 = 0.680; // Y-coordinate of center of circle.

        float rr2 = 0.010; // Radius of circle.
        float xx2 = 1.150; // X-coordinate of center of circle.
        float yy2 = 0.580; // Y-coordinate of center of circle.

        float RR = 0.060; // Radius of circle.
        float XX = 1.150; // X-coordinate of center of circle.
        float YY = 0.600; // Y-coordinate of center of circle.
        int nnumVertices = 25; // Number of vertices on circle.
        float tt = -0.01; // Angle parameter.
        int ii;
        glBegin(GL_LINE_LOOP);//to draw that white color bell curve
         glColor3f(0.90, 0.91, 0.98);
        for(int ii = 0; ii < nnumVertices; ++ii)
        {
            glVertex3f(XX - RR * cos(tt), YY + RR * sin(tt), 0.0);
            tt +=  PI / nnumVertices;
        }
        glEnd();
        glFlush();

        glBegin(GL_LINE_LOOP);//bottom rectangle below bell

            glColor3f(0.90, 0.91, 0.98);
            glVertex2f(1.070,0.600);
            glVertex2f(1.230,0.610);

            glVertex2f(1.230,0.610);
            glVertex2f(1.230,0.590);

            glVertex2f(1.230,0.590);
            glVertex2f(1.070,0.580);

            glVertex2f(1.070,0.580);
            glVertex2f(1.070,0.600);

        glEnd();
        glFlush();

        glBegin(GL_POLYGON);//to draw circle above that bell shape
        glColor3f(0.55, 0.47, 0.14);
        for(int ii = 0; ii < nnumVertices; ++ii)
        {
            glVertex3f(xx1 + rr1 * cos(tt), yy1 + rr1 * sin(tt), 0.0);
            tt += 2 * PI / nnumVertices;
        }
        glEnd();
        glFlush();

        glBegin(GL_POLYGON);//to draw a small color below that rectangle below that bell shape
        glColor3f(0.55, 0.47, 0.14);
        for(int ii = 0; ii < nnumVertices; ++ii)
        {
            glVertex3f(xx2 + rr2 * cos(tt), yy2 + rr2 * sin(tt), 0.0);
            tt += 2 * PI / nnumVertices;
        }
        glEnd();
        glFlush();
        glPopMatrix();

        //joker code
        glPushMatrix();
        glTranslatef(-1.45,-1.05,0.0);
        glScalef(1.0,2.0,1.0);
        float r3 = 0.040; // Radius of circle.
        float x3 = 0.800; // X-coordinate of center of circle.
        float y3 = 0.670;

        float r1 = 0.010; // Radius of circle.
        float x1 = 0.770; // X-coordinate of center of circle.
        float y1 = 0.730;

        float r2 = 0.010; // Radius of circle.
        float x2 = 0.830; // X-coordinate of center of circle.
        float y2 = 0.730;

        float R = 0.030; // Radius of circle.
        float X = 0.800; // X-coordinate of center of circle.
        float Y = 01.030; // Y-coordinate of center of circle.
        int numVertices = 25; // Number of vertices on circle.
        float t = 0; // Angle parameter.
        int i;

        //draw a line
        glBegin(GL_LINES);

            glColor3f(0.92, 0.78, 0.62);//to draw joker face
            glVertex2f(0.800,0.600);
            glVertex2f(0.900,0.650);

            glVertex2f(0.900,0.650);
            glVertex2f(0.900,0.750);

            glColor3f(0.137255, 0.556863, 0.137255);//0.0, 0.5, 0.0);
            glVertex2f(0.900,0.750);
            glVertex2f(0.800,0.800);

            glVertex2f(0.800,0.800);
            glVertex2f(0.700,0.750);

            glColor3f(0.92, 0.78, 0.62);
            glVertex2f(0.700,0.750);
            glVertex2f(0.7000,0.650);

            glVertex2f(0.700,0.650);
            glVertex2f(0.800,0.600);

            glColor3f( 0.137255, 0.556863, 0.137255);
            glVertex2f(0.900,0.750);
            glVertex2f(0.800,1.000);

            glVertex2f(0.800,1.000);
            glVertex2f(0.700,0.750);

        glEnd();
        glFlush();

        glBegin(GL_POLYGON);//to draw small circle above joker cap
        glColor3f(0.1, 0.9, 0.0);
        for(int i = 0; i < numVertices; ++i)
        {
            glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
            t += 2 * PI / numVertices;
        }
        glEnd();
        glFlush();

        glBegin(GL_POLYGON);//to draw left eye
        glColor3f(0.647059, 0.164706, 0.164706);
        for(int i = 0; i < numVertices; ++i)
        {
            glVertex3f(x1 + r1 * cos(t), y1 + r1 * sin(t), 0.0);
            t += 2 * PI / numVertices;
        }
        glEnd();
        glFlush();

        glBegin(GL_POLYGON);//to draw right eye
        glColor3f(0.647059, 0.164706, 0.164706);
        for(int i = 0; i < numVertices; ++i)
        {
            glVertex3f(x2 + r2 * cos(t), y2 + r2 * sin(t), 0.0);
            t += 2 * PI / numVertices;
        }
        glEnd();
        glFlush();

        glBegin(GL_POLYGON);//to draw joker mouth
        glColor3f(1.0, 0.7, 0.0);
        for(int i = 0; i < numVertices; ++i)
        {
            glVertex3f(x3 + r3 * cos(t), y3 + r3 * sin(t), 0.0);
            t += - PI / numVertices;
        }
        glEnd();
        glFlush();
        glPopMatrix();

        //snowman code
        glPushMatrix();
        glScalef(1.3,2.0,0.0);
        glTranslatef(-1.23,-0.42,0.0);
        float r5 = 0.010; // Radius of circle.
        float x5 = 01.320; // X-coordinate of center of circle.
        float y5 = 0.780;

        float r4 = 0.010; // Radius of circle.
        float x4 = 01.280; // X-coordinate of center of circle.
        float y4 = 0.780;

        float nr1 = 0.070; // Radius of circle.
        float nx1 = 01.300; // X-coordinate of center of circle.
        float ny1 = 0.750;

        float nr2 = 0.010; // Radius of circle.
        float nx2 = 01.300; // X-coordinate of center of circle.
        float ny2 = 0.630;

        float nR = 0.100; // Radius of circle.
        float nX = 01.300; // X-coordinate of center of circle.
        float nY = 0.580; // Y-coordinate of center of circle.
        int umVertices = 25; // Number of vertices on circle.
        float nt = 0; // Angle parameter.
        int j;

        //draw a line
        glBegin(GL_LINES);//to draw a line below hat

            glColor3f(0.737255, 0.560784, 0.560784);
            glVertex2f(01.220,0.820);
            glVertex2f(01.380,0.820);
        glEnd();
        glFlush();

        glBegin(GL_POLYGON);//to draw hat
            glColor3f(0.737255, 0.560784, 0.560784);
            glVertex2f(01.260,0.820);
            glVertex2f(01.260,0.880);

            glVertex2f(01.260,0.880);
            glVertex2f(01.340,0.880);

            glVertex2f(01.340,0.880);
            glVertex2f(01.340,0.820);

            glVertex2f(01.340,0.820);
            glVertex2f(01.260,0.820);

        glEnd();
        glFlush();

        glBegin(GL_POLYGON);//to draw nose of a snow man
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(01.300,0.760);
            glVertex2f(01.250,0.730);

            glVertex2f(01.250,0.730);
            glVertex2f(01.300,0.740);

            glVertex2f(01.300,0.740);
            glVertex2f(01.300,0.760);

        glEnd();
        glFlush();

        glBegin(GL_LINE_LOOP);//to draw circle for snow man body
        glColor3f(1.0, 1.0, 1.0);
        for(int i = 0; i < umVertices; ++i)
        {
            glVertex3f(nX + nR * cos(nt), nY + nR * sin(nt), 0.0);
            nt += 2 * PI / umVertices;
        }
        glEnd();
        glFlush();

        glBegin(GL_LINE_LOOP);//to draw circle for snow man face
        glColor3f(1.0,1.0,1.0);
        for(int i = 0; i < umVertices; ++i)
        {
            glVertex3f(nx1 + nr1 * cos(nt), ny1 + nr1 * sin(nt), 0.0);
            nt += 2 * PI / umVertices;
        }
        glEnd();
        glFlush();

        glBegin(GL_POLYGON);//to draw small circles inside snow man's body
        glColor3f(0.647059, 0.164706, 0.164706);
        for(int i = 0; i < umVertices; ++i)
        {
            glVertex3f(nx2 + nr2 * cos(nt), ny2 + nr2 * sin(nt), 0.0);
            nt += 2 * PI / umVertices;
        }
        glEnd();
        glFlush();

        glBegin(GL_POLYGON);//to draw left eye of snow man
        glColor3f(1.0, 0.7, 0.0);
        for(int i = 0; i < umVertices; ++i)
        {
            glVertex3f(x4 + r4 * cos(nt), y4 + r4 * sin(nt), 0.0);
            nt += 2 * PI / umVertices;
        }
        glEnd();
        glFlush();

        glBegin(GL_POLYGON);//to draw right eye of snow man
        glColor3f(1.0, 0.7, 0.0);
        for(int i = 0; i < numVertices; ++i)
        {
            glVertex3f(x5 + r5 * cos(nt), y5 + r5 * sin(nt), 0.0);
            nt += 2 * PI / numVertices;
        }
        glEnd();
        glFlush();
        glPopMatrix();

        glPopMatrix();
        glFlush();
        glutSwapBuffers();
        glFlush();

}

void animateObj()
{
        glutIdleFunc(spin);//for applying animation
        glClearColor(0.0,0.0,0.0,0.0);
        glViewport(0,0,(GLsizei)1500,(GLsizei)1500);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-1.0,1.0,-1.0,1.0,1.5,20.0);
        glMatrixMode(GL_MODELVIEW);

        glLineWidth(3);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1.0,0x0f0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0,1.0,1.0);
        glLoadIdentity();
        gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
        glPushMatrix();
        glScalef(0.9,0.6,3.0);
        glTranslatef(-0.3,-1.8,0.2);

        //instead of 'l'
        glPushMatrix();
        glScalef(1.0,scaling,1.0);//scale in y direction
        glTranslatef(0.15,-0.18,0.0);

        glColor3f(0.0,1.0,0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.25,0.25);
        glVertex2f(0.25,0.75);
        glVertex2f(0.35,0.75);
        glVertex2f(0.35,0.25);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(0.30,0.35);
        glVertex2f(0.30,0.65);
        glEnd();
            glColor3f(1.0,1.0,0.0);
             glScalef(0.90,3.0,0.0);
             glTranslatef(0.34,0.30,0.09);
            glutWireCone(0.04,0.08,20,90);
            glColor3f(0.0,0.0,0.0);
            glutWireCone(0.035,0.08,20,90);
            glColor3f(1.0,0.0,0.0);
            glutWireCone(0.025,0.08,20,90);
            glColor3f(0.0,0.0,0.0);
            glutWireCone(0.020,0.08,20,90);

        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.5,-1.07,0.0);
        glScalef(scaling,2.0,0.5);//scale in x-direction
        //snowflake
        glColor3f(0.0,0.0,1.0);
        glBegin(GL_LINES);
            glVertex2f(0.25,0.60);                  //s-n
            glVertex2f(0.25,01.00);

            glVertex2f(0.05,0.80);                   //w-e
            glVertex2f(0.45,0.80);

            glVertex2f(0.10,0.65);                  //sw-ne
            glVertex2f(0.40,0.95);

            glVertex2f(0.40,0.65);                  //se-nw
            glVertex2f(0.10,0.95);

            glVertex2f(0.25,0.90);                  //flake on north
            glVertex2f(0.28,0.93);
            glVertex2f(0.25,0.90);
            glVertex2f(0.22,0.93);

            glVertex2f(0.25,0.70);                  //flake on south
            glVertex2f(0.28,0.67);
            glVertex2f(0.25,0.70);
            glVertex2f(0.22,0.67);

            glVertex2f(0.35,0.80);                  //flake on east
            glVertex2f(0.38,0.83);
            glVertex2f(0.35,0.80);
            glVertex2f(0.38,0.77);

            glVertex2f(0.15,0.80);                  //flake on west
            glVertex2f(0.12,0.83);
            glVertex2f(0.15,0.80);
            glVertex2f(0.12,0.77);

            glVertex2f(0.37,0.87);                  //flake on north-east
            glVertex2f(0.32,0.87);
            glVertex2f(0.32,0.92);
            glVertex2f(0.32,0.87);

            glVertex2f(0.18,0.73);                  //flake on south-west
            glVertex2f(0.18,0.68);
            glVertex2f(0.18,0.73);
            glVertex2f(0.13,0.73);

            glVertex2f(0.32,0.73);                  //flake on south-east
            glVertex2f(0.37,0.73);
            glVertex2f(0.32,0.73);
            glVertex2f(0.32,0.68);

            glVertex2f(0.18,0.87);                  //flake on north-west
            glVertex2f(0.18,0.92);
            glVertex2f(0.18,0.87);
            glVertex2f(0.13,0.87);
        glEnd();
        glPopMatrix();

    //instead of 'e' new code
    glPushMatrix();
    glTranslatef(-0.9,-1.13,0.0);
    glScalef(1.0,2.0,1.0-scaling);//sccale the gift box in z direction
    glPushMatrix();
    glMultMatrixf(m);//to apply shear transformation animation
    glBegin(GL_POLYGON);

            glColor3f(   0.90, 0.91 , 0.98 );
            glVertex2f(1.450,0.600);
            glVertex2f(1.650,0.600);

            glVertex2f(01.650,0.600);
            glVertex2f(01.650,0.800);

            glVertex2f(01.650,0.800);
            glVertex2f(01.450,0.800);

            glVertex2f(01.450,0.800);
            glVertex2f(01.450,0.600);

        glEnd();
        glFlush();

        glScalef(1.0,0.4,1.0);
        glTranslatef(0.0,1.40,0.0);
       glBegin(GL_POLYGON);
            glColor3f(0.85 , 0.09, 0.09 );
            glVertex2f(01.540,0.600);
            glVertex2f(01.560,0.600);

            glVertex2f(1.560,0.0600);
            glVertex2f(1.560,0.0800);

            glVertex2f(1.560,0.0800);
            glVertex2f(1.540,0.0800);

            glVertex2f(1.540,0.0800);
            glVertex2f(1.540,0.0600);

        glEnd();
        glFlush();

        //glScalef(0.0,2.0,0.0);
    glTranslatef(0.0,-0.3,0.0);

        glBegin(GL_POLYGON);
            glColor3f(  0.85 , 0.09, 0.09);
            glVertex2f(1.450,0.730);
            glVertex2f(1.650,0.730);

            glVertex2f(1.650,0.730);
            glVertex2f(1.650,0.750);

            glVertex2f(1.650,0.750);
            glVertex2f(1.450,0.750);

            glVertex2f(1.450,0.750);
            glVertex2f(1.450,0.730);

        glEnd();
        glFlush();
        glScalef(1.5,1.55,0.0);
        glTranslatef(-0.52,-0.22,0.0);
        glBegin(GL_POLYGON);
            glColor3f(  0.85 , 0.09, 0.09 );
            glVertex2f(1.550,0.800);
            glVertex2f(1.640,0.870);

            glVertex2f(1.640,0.870);
            glVertex2f(1.600,0.810);

            glVertex2f(1.600,0.810);
            glVertex2f(1.550,0.800);

            glVertex2f(1.550,0.800);
            glVertex2f(1.500,0.840);

            glVertex2f(1.500,0.840);
            glVertex2f(1.520,0.880);

            glVertex2f(1.520,0.880);
            glVertex2f(1.550,0.800);

        glEnd();
    glPopMatrix();
    glPopMatrix();

        //bell code
        glPushMatrix();
        glTranslatef(-1.7,-3,0.0);

        //glutPostRedisplay();
       glScalef(1.2,5.4,1.0);
       glRotatef(theta-9, 1, 1,0);//to apply rotation to a bell
         float rr1 = 0.020; // Radius of circle.
        float xx1 = 1.150; // X-coordinate of center of circle.
        float yy1 = 0.680; // Y-coordinate of center of circle.


        float rr2 = 0.010; // Radius of circle.
        float xx2 = 1.150; // X-coordinate of center of circle.
        float yy2 = 0.580; // Y-coordinate of center of circle.


        float RR = 0.060; // Radius of circle.
        float XX = 1.150; // X-coordinate of center of circle.
        float YY = 0.600; // Y-coordinate of center of circle.
        int nnumVertices = 25; // Number of vertices on circle.
        float tt = -0.01; // Angle parameter.
        int ii;

        glBegin(GL_LINE_LOOP);
         glColor3f(1.0, 1.0, 1.0);
        for(int ii = 0; ii < nnumVertices; ++ii)
        {
            //glColor3ub(rand()%256, rand()%256, rand()%256);
            glVertex3f(XX - RR * cos(tt), YY + RR * sin(tt), 0.0);
            tt +=  PI / nnumVertices;
        }
        glEnd();
        glFlush();

        //glRotatef(theta,1.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);

            //glColor3f(0.90, 0.91, 0.98);
            glVertex2f(1.070,0.600);
            glVertex2f(1.230,0.610);

            glVertex2f(1.230,0.610);
            glVertex2f(1.230,0.590);

            glVertex2f(1.230,0.590);
            glVertex2f(1.070,0.580);

            glVertex2f(1.070,0.580);
            glVertex2f(1.070,0.600);

        glEnd();
        glFlush();

       // glRotatef(theta,0.0,0.0,1.0);
        glBegin(GL_POLYGON);
        glColor3f(0.55, 0.47, 0.14);
        for(int ii = 0; ii < nnumVertices; ++ii)
        {
            glVertex3f(xx1 + rr1 * cos(tt), yy1 + rr1 * sin(tt), 0.0);
            tt += 2 * PI / nnumVertices;
        }
        glEnd();
        glFlush();

        glBegin(GL_POLYGON);
        glColor3f(0.55,0.47,0.14);
        for(int ii = 0; ii < nnumVertices; ++ii)
        {
            glVertex3f(xx2 + rr2 * cos(tt), yy2 + rr2 * sin(tt), 0.0);
            tt += 2 * PI / nnumVertices;
        }
        glEnd();
        glFlush();
        glPopMatrix();

        //joker code
        glPushMatrix();
        glTranslatef(-1.45,-1.05,0.0);
        glScalef(1.0,2.0,1.0*scaling);

        glRotatef(theta,1.0,1.0,0.0);
        float r3 = 0.040; // Radius of circle.
        float x3 = 0.800; // X-coordinate of center of circle.
        float y3 = 0.670;

        float r1 = 0.010; // Radius of circle.
        float x1 = 0.770; // X-coordinate of center of circle.
        float y1 = 0.730;

        float r2 = 0.010; // Radius of circle.
        float x2 = 0.830; // X-coordinate of center of circle.
        float y2 = 0.730;

        float R = 0.030; // Radius of circle.
        float X = 0.800; // X-coordinate of center of circle.
        float Y = 01.030; // Y-coordinate of center of circle.
        int numVertices = 25; // Number of vertices on circle.
        float t = 0; // Angle parameter.
        int i;

        //draw a line
        glBegin(GL_LINES);

            glColor3f(0.92, 0.78, 0.62);
            glVertex2f(0.800,0.600);
            glVertex2f(0.900,0.650);

            glVertex2f(0.900,0.650);
            glVertex2f(0.900,0.750);

            glColor3f(0.137255, 0.556863, 0.137255);//0.0, 0.5, 0.0);
            glVertex2f(0.900,0.750);
            glVertex2f(0.800,0.800);

            glVertex2f(0.800,0.800);
            glVertex2f(0.700,0.750);

            glColor3f(0.92, 0.78, 0.62);
            glVertex2f(0.700,0.750);
            glVertex2f(0.7000,0.650);

            glVertex2f(0.700,0.650);
            glVertex2f(0.800,0.600);

            glColor3f( 0.137255, 0.556863, 0.137255);
            glVertex2f(0.900,0.750);
            glVertex2f(0.800,1.000);

            glVertex2f(0.800,1.000);
            glVertex2f(0.700,0.750);

        glEnd();
        glFlush();


        glBegin(GL_POLYGON);
        glColor3f(0.1, 0.9, 0.0);
        for(int i = 0; i < numVertices; ++i)
        {
            glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
            t += 2 * PI / numVertices;
        }
        glEnd();
        glFlush();


        glBegin(GL_POLYGON);
        glColor3f(0.647059, 0.164706, 0.164706);
        for(int i = 0; i < numVertices; ++i)
        {
            glVertex3f(x1 + r1 * cos(t), y1 + r1 * sin(t), 0.0);
            t += 2 * PI / numVertices;
        }
        glEnd();
        glFlush();


        glBegin(GL_POLYGON);
        glColor3f(0.647059, 0.164706, 0.164706);
        for(int i = 0; i < numVertices; ++i)
        {
            glVertex3f(x2 + r2 * cos(t), y2 + r2 * sin(t), 0.0);
            t += 2 * PI / numVertices;
        }
        glEnd();
        glFlush();


        glBegin(GL_POLYGON);
        glColor3f(1.0, 0.7, 0.0);
        for(int i = 0; i < numVertices; ++i)
        {
            glVertex3f(x3 + r3 * cos(t), y3 + r3 * sin(t), 0.0);
            t += - PI / numVertices;
        }
        glEnd();
        glFlush();
        glPopMatrix();

        //snowman code
        glPushMatrix();
        glScalef(1.3,2.0,0.0);
        glTranslatef(-1.23,-0.42,0.0);
        glRotatef(theta,0.0,1.0,0.0);//to apply rotation to snowman i x-direction
        float r5 = 0.010; // Radius of circle.
        float x5 = 01.320; // X-coordinate of center of circle.
        float y5 = 0.780;


        float r4 = 0.010; // Radius of circle.
        float x4 = 01.280; // X-coordinate of center of circle.
        float y4 = 0.780;

        float nr1 = 0.070; // Radius of circle.
        float nx1 = 01.300; // X-coordinate of center of circle.
        float ny1 = 0.750;

        float nr2 = 0.010; // Radius of circle.
        float nx2 = 01.300; // X-coordinate of center of circle.
        float ny2 = 0.630;

        float nR = 0.100; // Radius of circle.
        float nX = 01.300; // X-coordinate of center of circle.
        float nY = 0.580; // Y-coordinate of center of circle.
        int umVertices = 25; // Number of vertices on circle.
        float nt = 0; // Angle parameter.
        int j;

        //draw a line
        glBegin(GL_LINES);

            glColor3f(0.737255, 0.560784, 0.560784);
            glVertex2f(01.220,0.820);
            glVertex2f(01.380,0.820);
        glEnd();
        glFlush();

        glBegin(GL_POLYGON);
            glColor3f(0.737255, 0.560784, 0.560784);
            glVertex2f(01.260,0.820);
            glVertex2f(01.260,0.880);

            glVertex2f(01.260,0.880);
            glVertex2f(01.340,0.880);

            glVertex2f(01.340,0.880);
            glVertex2f(01.340,0.820);

            glVertex2f(01.340,0.820);
            glVertex2f(01.260,0.820);


        glEnd();
        glFlush();


        glBegin(GL_POLYGON);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(01.300,0.760);
            glVertex2f(01.250,0.730);

            glVertex2f(01.250,0.730);
            glVertex2f(01.300,0.740);

            glVertex2f(01.300,0.740);
            glVertex2f(01.300,0.760);

        glEnd();
        glFlush();



        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 1.0, 1.0);
        for(int i = 0; i < umVertices; ++i)
        {
            glVertex3f(nX + nR * cos(nt), nY + nR * sin(nt), 0.0);
            nt += 2 * PI / umVertices;
        }
        glEnd();
        glFlush();


        glBegin(GL_LINE_LOOP);
        glColor3f(1.0,1.0,1.0);
        for(int i = 0; i < umVertices; ++i)
        {
            glVertex3f(nx1 + nr1 * cos(nt), ny1 + nr1 * sin(nt), 0.0);
            nt += 2 * PI / umVertices;
        }
        glEnd();
        glFlush();


        glBegin(GL_POLYGON);
        glColor3f(0.647059, 0.164706, 0.164706);
        for(int i = 0; i < umVertices; ++i)
        {
            glVertex3f(nx2 + nr2 * cos(nt), ny2 + nr2 * sin(nt), 0.0);
            nt += 2 * PI / umVertices;
        }
        glEnd();
        glFlush();

        glBegin(GL_POLYGON);
        glColor3f(1.0, 0.7, 0.0);
        for(int i = 0; i < umVertices; ++i)
        {
            glVertex3f(x4 + r4 * cos(nt), y4 + r4 * sin(nt), 0.0);
            nt += 2 * PI / umVertices;
        }
        glEnd();
        glFlush();

        glBegin(GL_POLYGON);
        glColor3f(1.0, 0.7, 0.0);
        for(int i = 0; i < numVertices; ++i)
        {
            glVertex3f(x5 + r5 * cos(nt), y5 + r5 * sin(nt), 0.0);
            nt += 2 * PI / numVertices;
        }
        glEnd();
        glFlush();
        glPopMatrix();

        glPopMatrix();
        glFlush();

}

void demo_menu(int id)//to perform menu selection
{
    switch(id)
    {
        case 1:exit(0);
        case 2:flag=2;
                break;
        case 3:flag=3;
                break;
    }
}

void* doSomeThing(void *arg)//to create music for thread
{
    pthread_t id = pthread_self();
    while(1)
     system("canberra-gtk-play -f abc.wav");
    if(pthread_equal(id,tid))
         printf("\n First thread processing\n");
     else
         printf("\n Second thread processing\n");
}

int main(int argc,char **argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(1500, 1500);
        glutCreateWindow("Front page");

        //creating menu
        GLint sub_menu=glutCreateMenu(demo_menu);
        glutAddMenuEntry("Draw objects",2);
        glutAddMenuEntry("Animate Objects",3);
        glutCreateMenu(demo_menu);
        glutAddMenuEntry("Exit",1);
        glutAddSubMenu("Draw and Animate",sub_menu);
        glutAttachMenu(GLUT_LEFT_BUTTON);

        glutDisplayFunc(mydisplay);
        glutKeyboardFunc(myKeyboardFunc);
        init();
        glutMainLoop();

    return 0;
}
