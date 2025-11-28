#pragma once

namespace JuegoFinal {

    public ref class GameConfig {
    public:
        // ============ TIMING ============
        static const int LEVEL_DURATION = 60;  // segundos por nivel
        static const int INVULNERABILITY_TIME = 120;  // frames (2 segundos)

        // ============ SCORING ============
        static const int POINTS_PER_SECOND = 10;
        static const int LEVEL_COMPLETE_BONUS = 500;

        // ============ HERO1 STATS ============
        static const int HERO1_SPEED = 15;
        static const int HERO1_VIDAS = 5;

        // ============ HERO2 STATS ============
        static const int HERO2_SPEED = 8;
        static const int HERO2_VIDAS = 8;

        // ============ ENEMY SPEEDS ============
        static const int ENEMY1_SPEED_MIN = 2;
        static const int ENEMY1_SPEED_MAX = 4;

        static const int ENEMY2_SPEED_MIN = 6;
        static const int ENEMY2_SPEED_MAX = 9;

        static const int ENEMY3_SPEED_MIN = 4;
        static const int ENEMY3_SPEED_MAX = 6;

        // ============ WINDOW SIZE ============
        static const int WINDOW_WIDTH = 1200;
        static const int WINDOW_HEIGHT = 700;

        // ============ FPS ============
        static const int TARGET_FPS = 60;
        static const int TIMER_INTERVAL = 16;  // ~16ms para 60fps
    };

} // namespace JuegoFinal