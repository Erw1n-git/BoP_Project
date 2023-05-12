#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cctype> 

#define RECORD_FILE "record.txt"

namespace Game {

    // Клас рахунку гри, який представляє рахунок поточної гри,
    // рахунок минулої гри та рекордний рахунок
    // Клас використовує паттерн Singleton, тобто цей клас може
    // мати лише єдиний екземпляр
    class Score{
        private:
            static Score* instance; // статичний вказівник на єдиний екземпляр класу

            unsigned int currentScore; // Поточний рахунок гри
            unsigned int previousScore; // Рахунок минулої гри
            unsigned int recordScore; // Рахунок найкращої гри

            Score();

        public:
            static Score& getInstance();

            // TODO: Check whether these 'static' are needed

            static unsigned getCurrentScore();
            static unsigned getPreviousScore();
            static unsigned getRecordScore();

            static void addCurrentScore(unsigned int score);
            static void setCurrentScore(unsigned int currentScore);
            static void setPreviousScore(unsigned int previousScore);
            static void setRecordScore(unsigned int recordScore);

            static int readRecordFromFile();    // Зчитує рекорд з файлу,
                                                // повертає від'ємне значення, якщо виникла помилка
            
            static int writeRecordToFile();     // Записує новий рекорд до файлу,
                                                // повертає від'ємне значення, якщо виникла помилка

    };
    
}

#endif