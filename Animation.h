#ifndef RAYLIB_FUN_ANIMATION_H
#define RAYLIB_FUN_ANIMATION_H

#include "raylib.h"

struct Animation {
    Texture2D texture;
    int maxFrames;
    int framesPerSecond;

    Rectangle rect;
    float lastFrameChange;
    int currentFrame;

    Animation(const Texture2D txtr, const int frames, const int fps) :
    texture(txtr), maxFrames(frames), framesPerSecond(fps),
    rect({0.0f, 0.0f, static_cast<float>(texture.width/maxFrames), static_cast<float>(texture.height)}),
    lastFrameChange(0.0f), currentFrame(0)
    {}
};

#endif //RAYLIB_FUN_ANIMATION_H