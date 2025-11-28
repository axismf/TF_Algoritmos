#pragma once

using namespace System;

namespace JuegoFinal {

    public ref class GameStateManager {
    private:
        static GameStateManager^ instance = nullptr;

        GameStateManager() {
            resetGame();
        }

    public:
        // Información del jugador
        String^ playerName;
        int selectedHero;  // 1 o 2

        // Progreso del juego
        int currentLevel;  // 1, 2, 3
        int totalScore;
        int vidasRestantes;

        // Estadísticas
        int enemiesDefeated;
        int totalTimePlayed;

        // Singleton - obtener instancia única
        static GameStateManager^ getInstance() {
            if (instance == nullptr) {
                instance = gcnew GameStateManager();
            }
            return instance;
        }

        // Reiniciar juego
        void resetGame() {
            playerName = "";
            selectedHero = 0;
            currentLevel = 1;
            totalScore = 0;
            vidasRestantes = 0;
            enemiesDefeated = 0;
            totalTimePlayed = 0;
        }

        // Pasar al siguiente nivel
        void nextLevel() {
            currentLevel++;
        }

        // Agregar puntos
        void addScore(int points) {
            totalScore += points;
        }

        // Guardar vidas
        void setVidas(int vidas) {
            vidasRestantes = vidas;
        }

        // Agregar tiempo
        void addTime(int seconds) {
            totalTimePlayed += seconds;
        }
    };

} // namespace JuegoFinal

