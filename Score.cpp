#include "Score.h"

namespace Game {

    Score* Score::instance = nullptr;

    Score::Score()
    {
        currentScore = 0;
        previousScore = 0;
        recordScore = 0;
    }

    Score& Score::getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Score();
            //instance->readRecordFromFile();
        }
        return *instance;
    }

    int Score::readRecordFromFile()
    {
        std::ifstream file(RECORD_FILE);

        if (!file.is_open())
        {
            std::cout << "*[ERROR]* Could not open the file: " << RECORD_FILE << std::endl;
            return -1;
        }

        std::string lineRecord;
        if (std::getline(file, lineRecord))
        {
            for (char c : lineRecord)
            {
                if (!std::isdigit(c))
                {
                    std::cout << "*[ERROR]* The file contains non-digit characters." << std::endl;
                    file.close();
                    return -3;
                }
            }

            instance->recordScore = std::stoi(lineRecord); 
            file.close();
            return 0;
        }

        std::cout << "*[ERROR]* The file is empty" << std::endl;
        file.close();
        return -2;
    }

    int Score::writeRecordToFile()
    {
        std::ofstream file(RECORD_FILE);

        if (!file.is_open())
        {
            std::cout << "*[ERROR]* Could not open the file: " << RECORD_FILE << std::endl;
            return -1; 
        }

        file << instance->recordScore;

        if (file.fail())
        {
            std::cout << "*[ERROR]* Could not write record to the file: " << RECORD_FILE << std::endl;
            return -2;
        }

        return 0;
    }

    unsigned Score::getCurrentScore()
    {
        return instance->currentScore;
    }

    unsigned Score::getPreviousScore()
    {
        return instance->previousScore;
    }

    unsigned Score::getRecordScore()
    {
        return instance->recordScore;
    }

    void Score::addCurrentScore(unsigned int score)
    {
        instance->currentScore += score;
    }

    void Score::setCurrentScore(unsigned int currentScore)
    {
        instance->currentScore = currentScore;
    }

    void Score::setPreviousScore(unsigned int previousScore)
    {
        instance->previousScore = previousScore;
    }

    void Score::setRecordScore(unsigned int recordScore)
    {
        instance->recordScore = recordScore;
        std::cout << "This is a test!" << std::endl;
        instance->writeRecordToFile();
    }

}