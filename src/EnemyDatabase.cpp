#include "EnemyDatabase.h"

static constexpr Vector2 ZERO_VECTOR = Vector2(0.0f, 0.0f);

EnemyDatabase::EnemyDatabase() :
basic({ZERO_VECTOR, Vector2(7, 7), RED, 30, 3}),
fast({ZERO_VECTOR, Vector2(3, 3), BLACK, 60, 1}),
slow({ZERO_VECTOR, Vector2(10, 10), GREEN, 15, 10})
{}