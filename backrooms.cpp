#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "backrooms.h"

const int ROOM_SIZE_X = 800;
const int ROOM_SIZE_Y = 600;
const int BORDER_SIZE = 5;
const float ENRG_LIM = 0.01;

float kfx = (float)ROOM_SIZE_X/ROOM_SIZE_Y;
float kfy = 1;

Room::Room(GLFWwindow* InitWindow, int InitSizeX, int InitSizeY) {
    window = InitWindow;
    SIZE_X = InitSizeX;
    SIZE_Y = InitSizeY;
}

void Room::Show() {
    glBegin(GL_QUADS);
    glColor3f(0.10, 0.10, 0.10); // WALLS
    glVertex2f(-kfx, -kfy);
    glVertex2f(-kfx, kfy);
    glVertex2f(kfx, kfy);
    glVertex2f(kfx, -kfy);
    
    glColor3f(0.80, 0.80, 0.80); // BG
    glVertex2f(-kfx+0.05, -kfy+0.05);
    glVertex2f(-kfx+0.05, kfy-0.05);
    glVertex2f(kfx-0.05, kfy-0.05);
    glVertex2f(kfx-0.05, -kfy+0.05);
    glEnd();
}

Player::Player(GLFWwindow* InitWindow, float InitX, float InitY) {
    window = InitWindow;
    X = InitX;
    Y = InitY;
    energy = 0.01;
}

float Player::GetX() {
    return X;
}

float Player::GetY() {
    return Y;
}
float Player::GetEnergy() {
    return energy;
}

void Player::Show() {
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(0.05, 0.05, 0.90);
    glVertex2f(X, Y);
    glEnd();
//    int seg = 20;
//    float circ_x = X, circ_y = Y;
//    float rad = 0.05;
//    float a = M_PI*2/seg;
//    glBegin(GL_TRIANGLE_FAN);
//    glColor3f(0.90, 0.05, 0.05);
//    for(int i = -1; i < seg; i++) {
//        circ_x = sin(a*i)*rad;
//        circ_y = cos(a*i)*rad;
//        glVertex2f(circ_x, circ_y);
//    }
//    glEnd();
}

void Player::Move() {
    float dx = 0.00, dy = 0.00, de = 0.00;
    float step = 0.01, rest = 0.0001, tired = 0.00002;
    int KeyStateW = -1, KeyStateA = -1, KeyStateS = -1, KeyStateD = -1;
    
    step = 0.002+energy;
    
    KeyStateW = glfwGetKey(window, GLFW_KEY_W); // WASD LOGIC
    KeyStateA = glfwGetKey(window, GLFW_KEY_A);
    KeyStateS = glfwGetKey(window, GLFW_KEY_S);
    KeyStateD = glfwGetKey(window, GLFW_KEY_D);
    
    if(KeyStateW == GLFW_PRESS && Y+step < kfy-0.05) {
        dy += step;
    }
    if(KeyStateA == GLFW_PRESS && X-step > -kfx+0.05) {
        dx -= step;
    }
    if(KeyStateS == GLFW_PRESS && Y-step > -kfy+0.05) {
        dy -= step;
    }
    if(KeyStateD == GLFW_PRESS && X+step < kfx-0.05) {
        dx += step;
    }
    
    // ENERGY LOGIC
    if((dx && dy) && energy > 0) {
        de -= tired;
    }
    if((dx && !dy) && energy > 0) {
        de -= tired;
    }
    if((!dx && dy) && energy > 0) {
        de -= tired;
    }
    if((!dx && !dy) && energy < ENRG_LIM) { // EARN ENERGY
        de += rest;
    }
    
//    if(KeyStateW == GLFW_PRESS) {
//        dy += step;
//    }
//    if(KeyStateA == GLFW_PRESS) {
//        dx -= step;
//    }
//    if(KeyStateS == GLFW_PRESS) {
//        dy -= step;
//    }
//    if(KeyStateD == GLFW_PRESS) {
//        dx += step;
//    }
    
//    if((!dx || !dy) && energy < ENRG_LIM) { // EARN ENERGY
//        de += rest;
//    }
//    if((dx || dy) && energy > 0) {
//        de -= tired;
//    }
    X += dx; Y += dy; energy += de;
    dx = 0.00; dy = 0.00; de = 0.00;
}

Enemy::Enemy(float InitX, float InitY) {
    X = InitX;
    Y = InitY;
}

float Enemy::GetX() {
    return X;
}

float Enemy::GetY() {
    return Y;
}

void Enemy::Show() {
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(0.90, 0.05, 0.05);
    glVertex2f(X, Y);
    glEnd();
}

void Enemy::Chase(float TargX, float TargY) {
    float dx = 0.00, dy = 0.00;
    float step = 0.004;
    if(X > TargX-step) {
        dx -= step;
    }
    if(X < TargX+step) {
        dx += step;
    }
    if(Y > TargY-step) {
        dy -= step;
    }
    if(Y < TargY+step) {
        dy += step;
    }
    X += dx; Y += dy;
    dx = 0.00; dy = 0.00;
}

EnergyScale::EnergyScale(float InitX, float InitY, float InitEnergy) {
    X = InitX;
    Y = InitY;
    level = InitEnergy;
}

void EnergyScale::Show(float InitLevel) {
    level = (InitLevel/ENRG_LIM)*0.2;
    
    
    glLineWidth(4);  // SCALE BORDER
    glBegin(GL_LINE_LOOP);
    glColor3f(0.00, 0.00, 0.00);
    glVertex2f(X, Y); glVertex2f(X+0.04, Y);
    glVertex2f(X+0.04, Y+0.2); glVertex2f(X, Y+0.2);
    glEnd();
    
    glBegin(GL_QUADS); // SCALE BG
    glColor3f(0.90, 0.00, 0.00);
    glVertex2f(X, Y); glVertex2f(X+0.04, Y);
    glColor3f(0.00, 0.90, 0.00);
    glVertex2f(X+0.04, Y+0.2); glVertex2f(X, Y+0.2);
    glEnd();
    
    glLineWidth(4);  // SCALE PLANK
    glBegin(GL_LINES);
    glColor3f(0.00, 0.00, 0.00);
    glVertex2f(X-0.02, Y+level); glVertex2f(X+0.06, Y+level);
//    glVertex2f(X-0.02, Y); glVertex2f(X+0.06, Y);
    glEnd();
}

//void EnergyScale::Update() {
//    level = Player::GetEnergy();
//}
