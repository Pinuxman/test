#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Room {
    int SIZE_X, SIZE_Y;
public:
    GLFWwindow* window;
    Room(GLFWwindow* InitWindow, int InitSizeX, int InitSizeY);
    ~Room() {};
    void Show();
};

class Player {
    float X, Y;
    float energy;
    GLFWwindow* window;
public:
    Player(GLFWwindow* InitWindow, float InitX, float InitY);
    ~Player() {};
    float GetX();
    float GetY();
    float GetEnergy();
    void Show();
    void Move();
};

class Enemy {
    float X, Y;
public:
    Enemy(float InitX, float InitY);
    ~Enemy() {};
    float GetX();
    float GetY();
    void Show();
    void Chase(float InitX, float InitY);
};

class EnergyScale {
    float X, Y;
    float level;
public:
    EnergyScale(float InitX, float InitY, float InitEnergy);
    ~EnergyScale() {};
    void Show(float InitLevel);
//    void Update();
};
