#include "raylib.h"

int main()
{
    // Windows dimensions
    int width = 800;
    int height = 450;
    InitWindow(width, height, "Axe Game"); // width, height, title

    // Circle coordinates
    int circle_x = 200;
    int circle_y = 200;
    int circle_radius = 25;

    // circle edges
    int l_circle_x = circle_x - circle_radius;
    int r_circle_x = circle_x + circle_radius;
    int u_circle_y = circle_y - circle_radius;
    int b_circle_y = circle_y + circle_radius;

    // Axe coordinates
    int axe_x = 400;
    int axe_y = 0;
    int axe_length = 50;

    // Axe edges
    int l_axe_x = axe_x;
    int r_axe_x = axe_x + axe_length;
    int u_axe_y = axe_y;
    int b_axe_y = axe_y + axe_length;

    int direction = 10;

    bool collision_with_axe = (b_axe_y >= u_circle_y) && (u_axe_y <= b_circle_y) && (l_axe_x <= r_circle_x) && (r_axe_x >= l_circle_x);

    SetTargetFPS(15);
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (collision_with_axe)
        {
            DrawText("Game Over!", 400, 200, 20, RED);
        }
        else
        {
            // Game logic begin

            // update the edges
            int l_circle_x = circle_x - circle_radius;
            int r_circle_x = circle_x + circle_radius;
            int u_circle_y = circle_y - circle_radius;
            int b_circle_y = circle_y + circle_radius;
            int l_axe_x = axe_x;
            int r_axe_x = axe_x + axe_length;
            int u_axe_y = axe_y;
            int b_axe_y = axe_y + axe_length;

            // update collision_with_axe
            collision_with_axe = (b_axe_y >= u_circle_y) && (u_axe_y <= b_circle_y) && (l_axe_x <= r_circle_x) && (r_axe_x >= l_circle_x);

            DrawCircle(circle_x, circle_y, circle_radius, BLUE);      // posX, posY, radius, color
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED); // posX, posY, width, height, color

            // move axe
            axe_y += direction;
            if (axe_y > height || axe_y < -100)
            { // down -> up -> down ...
                direction = -direction;
            }

            if (IsKeyDown(KEY_D) && circle_x < width)
            {
                circle_x += 10;
            }
            if (IsKeyDown(KEY_A) && circle_x > 0)
            {
                circle_x -= 10;
            }

            // Game login end
        }
        EndDrawing();
    }
}