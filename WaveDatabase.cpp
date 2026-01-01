#include "WaveDatabase.h"
#include "EnemyDatabase.h"

std::queue<std::queue<EnemySpawn>> WaveDatabase::waves;

void WaveDatabase::LoadWaves() {
    const EnemyDatabase edb;

    std::queue<EnemySpawn> wave1;
    for (int i = 0; i < 5; i++) {
        wave1.push(EnemySpawn{edb.basic, 1.0f});
    }
    waves.push(wave1);

    std::queue<EnemySpawn> wave2;
    for (int i = 0; i < 10; i++) {
        wave2.push(EnemySpawn{edb.basic, 0.8f});
    }
    waves.push(wave2);

    std::queue<EnemySpawn> wave3;
    for (int i = 0; i < 6; i++) {
        wave3.push(EnemySpawn{edb.basic, 0.8f});
    }
    for (int i = 0; i < 2; i++) {
        wave3.push(EnemySpawn{edb.slow, 1.5f});
    }
    waves.push(wave3);

    std::queue<EnemySpawn> wave4;
    for (int i = 0; i < 10; i++) {
        wave4.push(EnemySpawn{edb.fast, 0.5f});
    }
    waves.push(wave4);

    std::queue<EnemySpawn> wave5;
    for (int i = 0; i < 5; i++) {
        wave5.push(EnemySpawn{edb.slow, 0.75f});
    }
    for (int i = 0; i < 10; i++) {
        wave5.push(EnemySpawn{edb.fast, 0.2f});
    }
    waves.push(wave5);
}
