#include "Score.h"

namespace Game {

    Score* Score::instance = nullptr;

    Score::Score()
    {
        currentScore = 1;
        previousScore = 0;
        recordScore = 0;
    }

    Score::~Score()
    {
        delete instance;
    }

    Score& Score::getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Score();
        }
        return *instance;
    }

    void Score::addScore(int add)
    {
        instance->currentScore += add;
    }

    unsigned Score::getScore()
    {
        return getInstance().currentScore;
    }

}