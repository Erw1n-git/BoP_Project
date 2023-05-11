#ifndef SCORE_H
#define SCORE_H

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
            ~Score();

        public: 
            static Score& getInstance();
            static void addScore(int add);
            static unsigned getScore();

    };
    
}

#endif