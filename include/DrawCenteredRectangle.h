#ifndef RAYLIB_TOWERDEFENSE_DRAWCENTEREDRECTANGLE_H
#define RAYLIB_TOWERDEFENSE_DRAWCENTEREDRECTANGLE_H

#include <concepts>
#include "raylib.h"

//ensures that the type T calling the function has these variables
template <typename T>
concept HasPositionSizeColor = requires (T entity) {
    { entity.position } -> std::convertible_to<Vector2>;
    { entity.size } -> std::convertible_to<int>;
    { entity.color } -> std::convertible_to<Color>;
};

//Draw a rectangle centered around the position of the entity
//Rectangles draw from top left by default
template <HasPositionSizeColor T>
void DrawCenteredRectangle(const T& entity) {
    const auto size = static_cast<float>(entity.size);
    const float center = size/2;
    const Vector2 drawPosition = {entity.position.x - center, entity.position.y - center};

    DrawRectangleV(drawPosition, (Vector2){size, size}, entity.color);
}

#endif //RAYLIB_TOWERDEFENSE_DRAWCENTEREDRECTANGLE_H