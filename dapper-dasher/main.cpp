#include "raylib.h"

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
    Rectangle nebRec = {0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos = {windowWidth, windowHeight - nebRec.height};

    // second nebula variables
    Rectangle neb2Rec = {0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 neb2Pos = {windowWidth+300, windowHeight - nebRec.height};

    // nebula velocity (pixels/second)
    int nebVel = -200;

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // animation Scarfy frame
    int frame = 0;

    // animation Nebula frame
    int nebFrame = 0;

    // animation second Nebula frame
    int neb2Frame = 0;

    // amount of time before we update the animation frame
    const float updateTime = 1.0 / 12.0; // 1 frame of Scarfy need = 1/12 seconds (or we want Scarfy animation has FPS = 12)
    float runningTime = 0.0;             // total time elapsed through each frame

    // amount of time before we update the animation nebula frame
    const float nebUpdateTime = 1.0 / 12.0;
    float nebRunningTime = 0.0;

    // amount of time before we update the animation second nebula frame
    const float neb2UpdateTime = 1.0 / 12.0;
    float neb2RunningTime = 0.0;

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
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
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
        nebPos.x += nebVel * dT;

        // update the second nebula position
        neb2Pos.x += nebVel * dT;

        // update scarfy position
        scarfyPos.y += velocity * dT;

        // running time of 1 frame default device for Scarfy 
        runningTime += dT;

        // running time of 1 frame default device for Nebula 
        nebRunningTime += dT;

        // running time of 1 frame default device for second Nebula 
        neb2RunningTime += dT;

        // animation breeze when Scarfy jump (Scarfy's animation frame)
        if (!isInAir)
        {
            if (runningTime >= updateTime)
            // FPS "up" => time request "down"
            // FPS "down" => time request "up"
            {
                runningTime = 0;
                // update animation frame
                if (frame > 5)
                {
                    frame = 0;
                }
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
            }
        }

        // update Nebula's animation frame
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0;
            // update animation frame
            if (nebFrame > 7)
            {
                nebFrame = 0;
            }
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
        }

        // update second Nebula's animation frame
        if (neb2RunningTime >= neb2UpdateTime)
        {
            neb2RunningTime = 0;
            // update animation frame
            if (neb2Frame > 7)
            {
                neb2Frame = 0;
            }
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
        }

        // Draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);
        // Draw second nebula
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // End drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
