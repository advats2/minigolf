#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "game.h"
#include <GL/glut.h>
using namespace std;

#define sizeX 500
#define sizeY 700
#define delta 20
#define friction 50

extern vector<Box> boxes;
extern Ball ball;
extern Ball hole;
int mX = -1;
int mY = -1;
double vX = 0;
double vY = 0;
float dirX = 1;
float dirY = 1;
int strokes = 0;
bool gameover = false;
int level = 1;

void init() {
    glClearColor(0.0, 1.0, 0.0, 1.0);
    switch (level) {
        case 1: level1(); break;
        case 2: level2(); break;
        case 3: level3(); break;
        default: level = 1; level1();
    }
    strokes = 0;
    vX = vY = 0;
    mX = mY = -1;
    dirX = dirY = 1;
    gameover = false;
}

void display();
void reshape(int,int);
void mouse(int,int,int,int);
void timer(int);
void keyboard(unsigned char, int,int);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(sizeX,sizeY);
    glutInitWindowPosition(500,0);
    glutCreateWindow("Mini Golf");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    init();
    glutTimerFunc(0,timer,0);
    glutMainLoop();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    for(auto box : boxes) {
        glRectd(box.x, box.y, box.w+box.x, box.h+box.y);
    }
    glColor3f(0.0, 0.0, 0.0);
    draw_circle(hole);
    glColor3f(1.0, 1.0, 1.0);
    draw_circle(ball);
    glRasterPos2i(10,10);
    string str = "Level : " + to_string(level);
    str = str + ("  Tries : " + to_string(strokes));
    for(auto ch : str) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ch);
    }
    if(gameover) {
        glColor3f(0.0, 0.0, 1.0);
        glRectd(150,130,450,550);
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2i(160,500);
        string st = "Level Finished!!";
        for(auto ch : st) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch);
        }
        glRasterPos2i(160,420);
        st = "Your Tries : " + to_string(strokes);
        for(auto ch : st) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch);
        }
        glRasterPos2i(160,350);
        st = "Press R to restart";
        for(auto ch : st) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch);
        }
        glRasterPos2i(160,280);
        st = "Press E to exit";
        for(auto ch : st) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch);
        }
        glRasterPos2i(160,210);
        st = "Press N for next level";
        for(auto ch : st) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch);
        }
        glRasterPos2i(160,140);
        st = "Press P for previous level";
        for(auto ch : st) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch);
        }
    }
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, sizeX, 0.0, sizeY);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mX = x;
        mY = y;
    }
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        if(x > mX) dirX = -1;
        else dirX = 1;
        if(mY > y) dirY = -1;
        else dirY = 1;
        vX = abs(x-mX);
        vY = abs(y-mY);
        mX = -1;
        mY = -1;
        strokes++;
    }
}

void timer(int _) {
    double newX = ball.x + dirX*vX*delta / 1000;
    double newY = ball.y + dirY*vY*delta / 1000;
    if((newX-hole.x)*(newX-hole.x) + (newY-hole.y)*(newY-hole.y) <= hole.r*hole.r) {
        gameover = true;
        cout << "Game Finished\n";
        cout << "Your Tries : " << strokes << "\n";
        ball.r = 0;
        glutPostRedisplay();
        system("mpv --no-terminal stone-dropping-6843.mp3 &");
        return;
    }
    if(newX-ball.r <= 0 || newX+ball.r >= sizeX) {
        dirX *= -1;
    }
    if(newY-ball.r <= 0 || newY+ball.r >= sizeY) {
        dirY *= -1;
    }
    for(auto box : boxes) {
        newX = ball.x + dirX*vX*delta / 1000;
        newY = ball.y;
        if(newX >= box.x && newX <= box.x+box.w && newY >= box.y && newY <= box.y+box.h) {
            dirX *= -1;
        }
        newX = ball.x;
        newY = ball.y + dirY*vY*delta / 1000;
        if(newX >= box.x && newX <= box.x+box.w && newY >= box.y && newY <= box.y+box.h) {
            dirY *= -1;
        }
    }

    ball.x += (dirX*vX*delta / 1000);
    ball.y += (dirY*vY*delta / 1000);
    double v = sqrt(vX*vX + vY*vY);
    if(v > 0) {
       double vx = vX, vy = vY, v1 = v;
        v -= abs(friction*delta / 1000);
        v = max(0.0,v);
        vX = v*(vx/v1);
        vY = v*(vy/v1);
    }

    glutPostRedisplay();
    glutTimerFunc(delta,timer,0);
}

void keyboard(unsigned char ch, int x, int y) {
    if(ch == 'R' || ch == 'r') {
        init();
        glutPostRedisplay();
        glutTimerFunc(0,timer,0);
    }
    if(ch == 'N' || ch == 'n') {
        if(!gameover) return;
        level++;
        init();
        glutPostRedisplay();
        glutTimerFunc(0,timer,0);
    }
    if(ch == 'P' || ch == 'p') {
        level--;
        init();
        glutPostRedisplay();
        glutTimerFunc(0,timer,0);
    }
    if(ch == 'E' || ch == 'e') {
        exit(0);
    }
}