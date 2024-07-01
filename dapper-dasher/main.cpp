#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    // window dimension
    const int windowWidth = 512;
    const int windowHeight = 380;
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // acceleration due to gravity (acceleration = (pixel/second)/second = v/t )
    const int gravity = 1000;

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for 2 nebulas
    AnimData nebData = {
        {0.0, 0.0, nebula.width / 8, nebula.height / 8}, // Rectangle rec
        {windowWidth, windowHeight - nebula.height / 8}, // Vector2 pos
        0,                                               // int frame
        1.0 / 12.0,                                      // float updateTime
        0.0                                              // float runningTime
    };

    AnimData neb2Data = {
        {0.0, 0.0, nebula.width / 8, nebula.height / 8},
        {windowWidth + 300, windowHeight - nebula.height / 8},
        0,
        1.0 / 16.0,
        0.0};

    // nebula velocity (pixels/second)
    int nebVel = -200;

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowWidth / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    // is the rectangle in the air
    bool isInAir = false;
    // jump velocity (pixel/second)
    const int jumpVel = -600;

    int velocity = 0; // pixel/second

    // Game running
    SetTargetFPS(60); // 60frames = 1 s => 1 frame = 1/60 s || 30FPS => 1f = 1/30 s
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        float dT = GetFrameTime();

        // perform ground check
        if (scarfyData.pos.y >= windowHeight - scarfyData.rec.height)
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air
            // apply gravity
            velocity += gravity * dT;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update nebula position
        nebData.pos.x += nebVel * dT;

        // update the second nebula position
        neb2Data.pos.x += nebVel * dT;

        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        // running time of 1 frame default device for Nebula
        nebData.runningTime += dT;

        // running time of 1 frame default device for second Nebula
        neb2Data.runningTime += dT;

        // animation breeze when Scarfy jump (Scarfy's animation frame)
        if (!isInAir)
        {
            // running time of 1 frame default device for Scarfy
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            // FPS "up" => time request "down"
            // FPS "down" => time request "up"
            {
                scarfyData.runningTime = 0.0;
                // update animation frame
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
            }
        }

        // update Nebula's animation frame
        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0;
            // update animation frame
            if (nebData.frame > 7)
            {
                nebData.frame = 0;
            }
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
        }

        // update second Nebula's animation frame
        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0.0;
            // update animation frame
            if (neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
        }

        // Draw nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        // Draw second nebula
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // End drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
