#include "raylib.h"

int main()
{
    int w = 350;
    InitWindow(w, 200, "Hello");
    
    while (true)
    {
        BeginDrawing();
        ClearBackground(RED);
        EndDrawing();
    }
    

    return 0;
}