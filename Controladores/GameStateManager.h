#pragma once

namespace JuegoFinal {

    using namespace System;

    public ref class GameStateManager
    {
    private:
        static GameStateManager^ instance = nullptr;

        GameStateManager() {
            selectedHero = 1;
            currentLevel = 1;
            score = 0;
            totalEnemiesKilled = 0;
            gameStarted = false;
        }

    public:
        // Estado del juego
        int selectedHero;       // 1 = Hero1, 2 = Hero2, 3 = IA
        int currentLevel;       // Nivel actual (0 = habitación, 1-3 = niveles)
        int score;              // Puntuación total
        int totalEnemiesKilled; // Enemigos eliminados
        bool gameStarted;       // Si el juego ha iniciado

        // Singleton pattern
        static GameStateManager^ getInstance() {
            if (instance == nullptr) {
                instance = gcnew GameStateManager();
            }
            return instance;
        }

        // Reiniciar estado del juego
        void resetGame() {
            currentLevel = 1;
            score = 0;
            totalEnemiesKilled = 0;
            gameStarted = true;
        }

        // Avanzar al siguiente nivel
        void nextLevel() {
            currentLevel++;
        }

        // Agregar puntos
        void addScore(int points) {
            score += points;
        }

        // Agregar enemigo eliminado
        void addEnemyKilled() {
            totalEnemiesKilled++;
        }

        // Obtener información del héroe seleccionado
        System::String^ getHeroName() {
            switch (selectedHero) {
            case 1: return "VELOCISTA";
            case 2: return "TANQUE";
            case 3: return "IA";
            default: return "DESCONOCIDO";
            }
        }

        int getHeroSpeed() {
            switch (selectedHero) {
            case 1: return 15;
            case 2: return 8;
            default: return 10;
            }
        }

        int getHeroLives() {
            switch (selectedHero) {
            case 1: return 5;
            case 2: return 8;
            default: return 3;
            }
        }
    };
}