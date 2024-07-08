#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return (data.pos.y >= windowHeight - data.rec.height);
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // running time of 1 frame default device for Scarfy
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    // FPS "up" => time request "down"
    // FPS "down" => time request "up"
    {
        data.runningTime = 0.0;
        // update animation frame
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
    }
    return data;
}

int main()
{
    // window dimension
    int windowDimensions[2] = {512, 380}; // width, height
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    // acceleration due to gravity (acceleration = (pixel/second)/second = v/t )
    const int gravity = 1000;

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeOfNebulae = 6;
    AnimData nebulae[sizeOfNebulae];

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.x = windowDimensions[0] + (300 * i);
        nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0; 
    }

    // nebula velocity (pixels/second)
    int nebVel = -200;

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    // is the rectangle in the air
    bool isInAir = false;
    // jump velocity (pixel/second)
    const int jumpVel = -600;

    int velocity = 0; // pixel/second

    // background variables
    Texture2D background = LoadTexture("textures/far-buildings.png");

    float bgX = 0.0; // position vector x of background 

    // Game running
    SetTargetFPS(60); // 60frames = 1 s => 1 frame = 1/60 s || 30FPS => 1f = 1/30 s
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        float dT = GetFrameTime();

        // move background from right to left
        bgX -= 20 * dT;

        // draw the background
        Vector2 bgPos = {bgX, 0.0};
        DrawTextureEx(background, bgPos, 0.0, 2.0, WHITE);


        // perform ground check
        if (isOnGround(scarfyData, windowDimensions[1]))
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

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // update the position of each nebula
            nebulae[i].pos.x += nebVel * dT;
        }

        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        // running time of 1 frame default device for Nebula
        nebulae[0].runningTime += dT;

        // running time of 1 frame default device for second Nebula
        nebulae[1].runningTime += dT;

        // animation breeze when Scarfy jump (Scarfy's animation frame)
        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
            // // update Nebula's animation frame
            // if (nebulae[i].runningTime >= nebulae[i].updateTime)
            // {
            //     nebulae[i].runningTime = 0;
            //     // update animation frame
            //     if (nebulae[i].frame > 7)
            //     {
            //         nebulae[i].frame = 0;
            //     }
            //     nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
            //     nebulae[i].frame++;
            // }
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // Draw nebula
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // End drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    CloseWindow();
}
