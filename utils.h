#ifndef utils_h
#define utils_h

namespace GraphUtils
{
    // Попередній опис масивів, які визначають кольори:
    extern float diffWhite[];
    extern float ambiWhite[];
    extern float specWhite[];

    extern float diffBlue[];
    extern float ambiBlue[];
    extern float specBlue[];

    extern float diffGray[];
    extern float ambiGray[];
    extern float specGray[];

    extern float diffRed[];
    extern float ambiRed[];
    extern float specRed[];

    extern float diffYellow[];
    extern float ambiYellow[];
    extern float specYellow[];

    extern float diffGreen[];
    extern float ambiGreen[];
    extern float specGreen[];

    extern float diffOrange[];
    extern float ambiOrange[];
    extern float specOrange[];

    extern float diffLightBlue[];
    extern float ambiLightBlue[];
    extern float specLightBlue[];

    extern float diffViolet[];
    extern float ambiViolet[];
    extern float specViolet[];

    const float shininess = 64; // блиск

    // Випадкове "тасування" одновимірного масиву цілих чисел
    void shuffle(int *a, int size);

    // Малювання паралелепіпеда
    void parallelepiped(float length, float width, float height);

    // Відображення рядка тексту вказаним шрифтом у вказаній позиції
    void drawString(void *font, const char* text, float x, float y);
}

#endif