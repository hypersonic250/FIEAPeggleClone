#pragma once

class Input
{
public:

    static void Update();

    static bool IsKeyPressed(
        SDL_Keycode key);

    static bool IsMouseButtonPressed(
        int button);

    static Vector2 GetMousePosition();
};
