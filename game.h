#ifndef GAME_H
#define GAME_H

class Box {
    public:
        int x;
        int y;
        int w;
        int h;
        Box(){}
        Box(int x, int y, int w, int h) {
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
        }
};

class Ball {
    public:
        double x;
        double y;
        int r;
        Ball(){}
        Ball(double x, double y, int r) {
            this->x = x;
            this->y = y;
            this->r = r;
        }
};

void level1();
void level2();
void level3();
void draw_circle(Ball ball);

#endif