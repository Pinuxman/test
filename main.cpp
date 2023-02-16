#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "backrooms.cpp"

bool game_over(Room &pRoom, Player &pPlayer, Enemy &pEnemy) {
    if(abs(pPlayer.GetX()-pEnemy.GetX())<=0.005 && abs(pPlayer.GetY()-pEnemy.GetY())<=0.005) {
        return true;
    }
    else return false;
}

int main(void) {
    
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(ROOM_SIZE_X, ROOM_SIZE_Y, "backrooms2d", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glScalef(1/kfx, 1/kfy, 1);
    Room room(window, ROOM_SIZE_X, ROOM_SIZE_Y);
//    TheEnd theend(0, 0);
    Player player(window, 0, 0);
    Enemy enemy(0.5, 0.5);
    EnergyScale escale(-kfx+0.1, -kfy+0.1, 1);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        if(!game_over(room, player, enemy)) {
            room.Show();
            player.Move();
            player.Show();
            enemy.Chase(player.GetX(), player.GetY());
            enemy.Show();
            escale.Show(player.GetEnergy());
//            theend.Show();
        }
        else {
            glfwSwapBuffers(window);
            glfwPollEvents();
            break;
        }
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
