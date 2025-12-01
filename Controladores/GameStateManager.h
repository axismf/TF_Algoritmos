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
        
        int selectedHero;       
        int currentLevel;      
        int score;              
        int totalEnemiesKilled; 
        bool gameStarted;      
        
        static GameStateManager^ getInstance() {
            if (instance == nullptr) {
                instance = gcnew GameStateManager();
            }
            return instance;
        }

        
        void resetGame() {
            currentLevel = 1;
            score = 0;
            totalEnemiesKilled = 0;
            gameStarted = true;
        }

        
        void nextLevel() {
            currentLevel++;
        }

       
        void addScore(int points) {
            score += points;
        }

      
        void addEnemyKilled() {
            totalEnemiesKilled++;
        }

        
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