#ifndef RAYLIB_TOWERDEFENSE_ANIMATION_H
#define RAYLIB_TOWERDEFENSE_ANIMATION_H

#include "raylib.h"

struct Animation {
    Texture2D texture;
    int maxFrames; //number of total frames
    int framesPerSecond; //how many frames per second to run the animation

    Rectangle rect; //size of sprite
    float lastFrameChange; //time since last frame change
    int currentFrame; //current frame in the animation process

    Animation(const Texture2D txtr, const int frames, const int fps) :
    texture(txtr), maxFrames(frames), framesPerSecond(fps),
    rect({0.0f, 0.0f, static_cast<float>(texture.width/maxFrames), static_cast<float>(texture.height)}),
    lastFrameChange(0.0f), currentFrame(0)
    {}
};

#endif //RAYLIB_TOWERDEFENSE_ANIMATION_H