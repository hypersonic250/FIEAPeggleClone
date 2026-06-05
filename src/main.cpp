#include <SDL.h>
#include <iostream>

#include "Engine/Window.h"
#include "Engine/Renderer.h"
#include "Engine/Time.h"
#include "Game/Ball.h"
#include "Game/Peg.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Game/Bucket.h"
#include "Game/HUD.h"
#include "Engine/AudioManager.h"

int FindPurplePegIndex(
    const std::vector<Peg>& pegs)
{
    for (int i = 0; i < pegs.size(); i++)
    {
        if (pegs[i].GetType() ==
            PegType::Purple)
        {
            return i;
        }
    }

    return -1;
}

AudioManager audio;

Mix_Chunk* pegHitSound = nullptr;
Mix_Chunk* bucketSound = nullptr;
Mix_Chunk* freeBallSound = nullptr;




void HandlePegHit(
    
    Peg& peg,
    int& score,
    int& turnScore,
    int& pegsHitThisTurn,
    int& orangePegsRemaining,
    int& ballsRemaining,
    int& nextFreeBallScore,
    bool& feverMode,
    bool& multiballActive,
    Ball& ball,
    Ball& multiball)


{
    if (peg.IsLit())
    {
        return;
    }

    peg.SetLit(true);
    pegsHitThisTurn++;

    int multiplier = 1;

    if (orangePegsRemaining <= 15)
    {
        multiplier = 2;
    }

    if (orangePegsRemaining <= 10)
    {
        multiplier = 3;
    }

    if (orangePegsRemaining <= 6)
    {
        multiplier = 5;
    }

    if (orangePegsRemaining <= 3)
    {
        multiplier = 10;
    }

    if (orangePegsRemaining == 0)
    {
        multiplier *= 100;
    }

    if (feverMode)
    {
        multiplier *= 10;
    }

    if (orangePegsRemaining == 0 &&
        !feverMode)
    {
        feverMode = true;

        std::cout << std::endl;
        std::cout << "FEVER MODE!" << std::endl;
        std::cout << std::endl;
    }

    switch (peg.GetType())
    {
    case PegType::Blue:
        turnScore += 10;
        break;

    case PegType::Green:
        turnScore += 10;
        break;

    case PegType::Orange:
        turnScore += 100;
        orangePegsRemaining--;
        break;

    case PegType::Purple:
        turnScore += 500;
        break;
    }

    while ((score + turnScore * pegsHitThisTurn) >= nextFreeBallScore)
    {
        ballsRemaining++;

        audio.PlaySound(freeBallSound);

        std::cout << "FREE BALL!" << std::endl;

        nextFreeBallScore += 25000;

    }

    std::cout
        << "Score: " << score
        << " | Orange Remaining: "
        << orangePegsRemaining
        << std::endl;

    peg.SetLit(true);

	ball.BounceOffPeg(peg.GetPosition());

}


int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }

    AudioManager audio;

    audio.Initialize();

    Mix_Chunk* pegHitSound = audio.LoadSound("../../../assets/Audio/PegglePegHit.wav");

    Mix_Chunk* bucketSound = audio.LoadSound("../../../assets/Audio/PeggleBucketHit.wav");

    Mix_Chunk* freeBallSound = audio.LoadSound("../../../assets/Audio/PeggleFreeBall.wav");

    Mix_Chunk* multiballSound = audio.LoadSound("../../../assets/Audio/PeggleMultiball.wav");





    bool running = true;

    Window window("FIEA Peggle Clone", 1280, 720);

    Renderer renderer(window);

    Ball ball;
    Ball multiball;

    bool multiballActive = false;
    Bucket bucket;

    HUD hud;

    if (!hud.Initialize())
    {
        std::cout<< "HUD initialization failed!"<< std::endl;
    }

    Vector2 launcherPosition(640.0f, 80.0f);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int ballsRemaining = 10;
    int score = 0;
    int turnScore = 0;
    int pegsHitThisTurn = 0;
    int nextFreeBallScore = 25000;

    bool ballReady = true;
    bool feverMode = false;

    bool gameWon = false;
    bool gameLost = false;

    std::vector<Peg> pegs;

    for (int row = 0; row < 10; row++)
    {
        int pegCount = (row % 2 == 0) ? 12 : 13;

        float startX = (row % 2 == 0) ? 240.0f : 200.0f;
        float y = 140.0f + row * 50.0f;

        for (int col = 0; col < pegCount; col++)
        {
            float x = startX + col * 80.0f;

            PegType type = PegType::Blue;

            pegs.emplace_back(x, y, type);
        }
    }

    const int orangeCount = 25;

    int orangesPlaced = 0;

    while (orangesPlaced < orangeCount)
    {
        int index = std::rand() % pegs.size();

        if (pegs[index].GetType() == PegType::Blue)
        {
            pegs[index].SetType(
                PegType::Orange);

            orangesPlaced++;
        }
    }

    int orangePegsRemaining = 0;

    for (const Peg& peg : pegs)
    {
        if (peg.GetType() == PegType::Orange)
        {
            orangePegsRemaining++;
        }
    }

    int purpleIndex = std::rand() % pegs.size();
    pegs[purpleIndex].SetType(PegType::Purple);

    int greenIndex = std::rand() % pegs.size();

    while (greenIndex == purpleIndex)
    {
        greenIndex = std::rand() % pegs.size();
    }

    pegs[greenIndex].SetType(PegType::Green);

    Time::Initialize();

    SDL_Event event;

    while (running)
    {
        Time::Update();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN &&
                event.button.button == SDL_BUTTON_LEFT)
            {
                if (ballReady)
                {
                    int mouseX;
                    int mouseY;

                    SDL_GetMouseState(
                        &mouseX,
                        &mouseY
                    );

                    Vector2 direction =
                        Vector2(
                            static_cast<float>(mouseX),
                            static_cast<float>(mouseY)
                        )
                        - ball.GetPosition();

                    direction =
                        direction.Normalized();

                    ball.Launch(direction * 600.0f);

                    ballReady = false;
                }
            }


            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_r)
                {
                    std::cout << "RESTARTING..." << std::endl;

                    score = 0;

                    ballsRemaining = 10;

                    nextFreeBallScore = 25000;

                    feverMode = false;

                    gameWon = false;

                    gameLost = false;

                    ballReady = true;

                    multiballActive = false;

                    ball.Reset();

                    multiball.Reset();

                    pegs.clear();

                    for (int row = 0; row < 10; row++)
                    {
                        int pegCount = (row % 2 == 0) ? 12 : 13;

                        float startX = (row % 2 == 0) ? 240.0f : 200.0f;
                        float y = 140.0f + row * 50.0f;

                        for (int col = 0; col < pegCount; col++)
                        {
                            float x = startX + col * 80.0f;

                            PegType type = PegType::Blue;

                            pegs.emplace_back(x, y, type);
                        }

                    }

                    const int orangeCount = 25;

                    int orangesPlaced = 0;

                    while (orangesPlaced < orangeCount)
                    {
                        int index = std::rand() % pegs.size();

                        if (pegs[index].GetType() == PegType::Blue)
                        {
                            pegs[index].SetType(
                                PegType::Orange);

                            orangesPlaced++;
                        }
                    }

                    orangePegsRemaining = 0;

                    for (const Peg& peg : pegs)
                    {
                        if (peg.GetType() == PegType::Orange)
                        {
                            orangePegsRemaining++;
                        }
                    }

                    int purpleIndex = std::rand() % pegs.size();

                    while (pegs[purpleIndex].GetType() != PegType::Blue)
                    {
                        purpleIndex = std::rand() % pegs.size();
                    }

                    pegs[purpleIndex].SetType(PegType::Purple);

                    int greenIndex = std::rand() % pegs.size();

                    while (greenIndex == purpleIndex || pegs[greenIndex].GetType() != PegType::Blue)
                    {
                        greenIndex = std::rand() % pegs.size();
                    }

                    pegs[greenIndex].SetType(PegType::Green);

                    std::cout << "GAME RESTARTED" << std::endl;

                    std::cout << "Orange Count = " << orangePegsRemaining << std::endl;
                }

            }

        }



        renderer.Clear();

        if (feverMode)
        {
            renderer.SetColor(80, 0, 0);

            SDL_Rect rect =
            {
                0,
                0,
                1280,
                720
            };

            SDL_RenderFillRect(
                renderer.GetNativeRenderer(),
                &rect
            );
        }

        renderer.SetColor(200, 200, 200);

        renderer.DrawCircle(
            static_cast<int>(launcherPosition.x),
            static_cast<int>(launcherPosition.y),
            20
        );

        int mouseX;
        int mouseY;

        SDL_GetMouseState(
            &mouseX,
            &mouseY
        );

        Vector2 direction =
            Vector2(
                static_cast<float>(mouseX),
                static_cast<float>(mouseY)
            )
            - launcherPosition;

        direction = direction.Normalized();

        Vector2 barrelEnd =
            launcherPosition +
            direction * 50.0f;

        renderer.SetColor(255, 255, 255);

        renderer.DrawLine(
            static_cast<int>(launcherPosition.x),
            static_cast<int>(launcherPosition.y),
            static_cast<int>(barrelEnd.x),
            static_cast<int>(barrelEnd.y)
        );

        if (!gameWon && !gameLost)
        {
            ball.Update();

            if (multiballActive)
            {
                 multiball.Update();
            }

         if (multiballActive && multiball.IsOutOfBounds())
            {
                multiballActive = false;
            }
    
        bucket.Update();

        Vector2 bucketPosition = bucket.GetPosition();

        float left =
            bucketPosition.x - bucket.GetWidth() / 2.0f;

        float right =
            bucketPosition.x + bucket.GetWidth() / 2.0f;

        float top =
            bucketPosition.y - bucket.GetHeight() / 2.0f;

        float ballX = ball.GetPosition().x;
        float ballY = ball.GetPosition().y;

        float ballRadius = ball.GetRadius();

        if (ballX >= left &&
            ballX <= right &&
            ballY >= top &&
            ballY <= bucketPosition.y)
        {
            ballsRemaining++;

            audio.PlaySound(
                bucketSound);

            std::cout
                << "FREE BALL CATCH!"
                << std::endl;

            if (feverMode)
            {
                std::cout << "YOU WIN!" << std::endl;
            }
            else
            {
                ball.Reset();
                ballReady = true;
            }
        }

        if (multiballActive)
        {
            float multiballX =
                multiball.GetPosition().x;

            float multiballY =
                multiball.GetPosition().y;

            if (multiballX >= left &&
                multiballX <= right &&
                multiballY >= top &&
                multiballY <= bucketPosition.y)
            {
                ballsRemaining++;

                audio.PlaySound(
                    bucketSound);

                std::cout
                    << "MULTIBALL FREE BALL!"
                    << std::endl;

                multiballActive = false;

                multiball.Reset();
            }
        }

        if (ball.IsOutOfBounds())
        {
            ballsRemaining--;

            std::cout
                << "Balls Remaining: "
                << ballsRemaining
                << std::endl;

            if (ballsRemaining <= 0)
            {
                std::cout << "GAME OVER" << std::endl;

                gameLost = true;
                ballReady = false;
            }

            else
            {
                for (Peg& peg : pegs)
                {
                    if (peg.IsLit())
                    {
                        peg.SetHit(true);
                    }
                }

                score += turnScore * pegsHitThisTurn;

                std::cout << "Turn Score: " << turnScore * pegsHitThisTurn << std::endl;

                turnScore = 0;
                pegsHitThisTurn = 0;

                if (orangePegsRemaining <= 0)
                {
                    std::cout << std::endl;
                    std::cout << "YOU WIN!" << std::endl;
                    std::cout << "FINAL SCORE: "
                        << score
                        << std::endl;
                    std::cout << std::endl;

                    gameWon = true;
                    ballReady = false;
                }

                score += turnScore * pegsHitThisTurn;

                for (Peg& peg : pegs)
                {
                    if (peg.IsLit())
                    {
                        peg.SetHit(true);
                    }
                }

                turnScore = 0;
                pegsHitThisTurn = 0;

                for (Peg& peg : pegs)
                {
                    if (peg.IsLit())
                    {
                        peg.SetHit(true);
                    }
                }

                score += turnScore * pegsHitThisTurn;

                std::cout
                    << "Turn Score: "
                    << turnScore * pegsHitThisTurn
                    << std::endl;

                turnScore = 0;
                pegsHitThisTurn = 0;

                ball.Reset();
                ballReady = true;

                int oldPurple = FindPurplePegIndex(pegs);

                if (oldPurple >= 0)
                {
                    pegs[oldPurple].SetType(PegType::Blue);
                }

                int newPurple = std::rand() % pegs.size();

                while (
                    pegs[newPurple].IsHit() ||
                    pegs[newPurple].IsLit()
                    )
                {
                    newPurple = std::rand() % pegs.size();
                }
                pegs[newPurple].SetType(PegType::Purple);
            }
        }


        for (Peg& peg : pegs)
        {
            if (peg.IsHit())
            {
                continue;
            }

            Vector2 difference =
                ball.GetPosition() - peg.GetPosition();

            float distanceSquared =
                difference.x * difference.x +
                difference.y * difference.y;

            float radiusSum =
                ball.GetRadius() + peg.GetRadius();

            if (distanceSquared <= radiusSum * radiusSum)
            {
                ball.BounceOffPeg(
                    peg.GetPosition()
                );

                Vector2 normal =
                    (ball.GetPosition() -
                        peg.GetPosition()).Normalized();

                float separation =
                    ball.GetRadius() +
                    peg.GetRadius();

                ball.SetPosition(
                    peg.GetPosition() +
                    normal * separation
                );

                audio.PlaySound(pegHitSound);

                PegType hitType = peg.GetType();

                HandlePegHit(
                    peg,
                    score,
                    turnScore,
                    pegsHitThisTurn,
                    orangePegsRemaining,
                    ballsRemaining,
                    nextFreeBallScore,
                    feverMode,
                    multiballActive,
                    ball,
                    multiball
                );





                if (hitType == PegType::Green &&
                    !multiballActive)
                {
                    audio.PlaySound(
                        multiballSound);

                    multiballActive = true;

                    multiball.SetPosition(
                        ball.GetPosition());

                    Vector2 velocity =
                        ball.GetVelocity();

                    velocity.x *= -1.0f;

                    multiball.SetVelocity(
                        velocity);
                }
            }
        }

        

        //duplicate, for multiball
        if (multiballActive)
        {
            for (Peg& peg : pegs)
            {
                if (peg.IsHit())
                {
                    continue;
                }

                Vector2 difference =
                    multiball.GetPosition() -
                    peg.GetPosition();

                float distanceSquared =
                    difference.x * difference.x +
                    difference.y * difference.y;

                float radiusSum =
                    multiball.GetRadius() +
                    peg.GetRadius();

                if (distanceSquared <= radiusSum * radiusSum)
                {

                    audio.PlaySound(pegHitSound);

                    HandlePegHit(
                        peg,
                        score,
                        turnScore,
                        pegsHitThisTurn,
                        orangePegsRemaining,
                        ballsRemaining,
                        nextFreeBallScore,
                        feverMode,
                        multiballActive,
                        multiball,
                        multiball
                    );
                }
            }
        }

    }

    for (Peg& peg : pegs)
    {
        peg.Render(renderer);
    }

    if (ballReady)
    {
        int mouseX;
        int mouseY;

        SDL_GetMouseState(
            &mouseX,
            &mouseY
        );

        renderer.SetColor(
            0,
            255,
            255
        );

        renderer.DrawLine(
            static_cast<int>(ball.GetPosition().x),
            static_cast<int>(ball.GetPosition().y),
            mouseX,
            mouseY
        );
    }

    ball.Render(renderer);

    if (multiballActive)
    {
        multiball.Render(renderer);
    }

    bucket.Render(renderer);

    hud.Render(
        renderer,
        score,
        turnScore,
        ballsRemaining,
        orangePegsRemaining
    );

    renderer.Present();

        SDL_Quit();

        return 0;

}