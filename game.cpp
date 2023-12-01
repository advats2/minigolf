#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "game.h"
using namespace std;

vector<Box> boxes;
Ball ball;
Ball hole;

void level1() {
    boxes.clear();
    Box box1 = Box(100,200,200,200);
    boxes.push_back(box1);
    ball = Ball(250,50,10);
    hole = Ball(70,650,30);
}

void level2() {
    boxes.clear();
    Box box1 = Box(115,30,100,150);
    boxes.push_back(box1);
    Box box2 = Box(200,300,150,150);
    boxes.push_back(box2);
    Box box3 = Box(20,430,60,250);
    boxes.push_back(box3);
    Box box4 = Box(220,520,180,80);
    boxes.push_back(box4);
    ball = Ball(20,40,10);
    hole = Ball(430,650,30);
}

void level3() {
    boxes.clear();
    Box box1 = Box(100,80,300,50);
    boxes.push_back(box1);
    Box box2 = Box(150,200,200,200);
    boxes.push_back(box2);
    Box box3 = Box(150,480,340,50);
    boxes.push_back(box3);
    Box box4 = Box(50,530,60,150);
    boxes.push_back(box4);
    ball = Ball(250,30,10);
    hole = Ball(430,650,30);
}

void draw_circle(Ball ball) {
    double x, y;
    double h = ball.x, k = ball.y, r = ball.r;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(h,k);
    for(int i = 0; i <= 360; i++) {
        x = h + r*cos(i * M_PI / 180.0);
        y = k + r*sin(i * M_PI / 180.0);
        glVertex2d(x,y);
    }
    glEnd();
}