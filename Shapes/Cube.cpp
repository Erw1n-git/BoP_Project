#include "Cube.h"

namespace Game
{
    Cube::Cube(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            int gridX, int gridZ, unsigned int value)
            : Shape(xCenter, yCenter, zCenter,
                xSize, ySize, zSize,
                nullptr, nullptr, nullptr)
    { 
        this->value = value;
        this->gridX = gridX;
        this->gridZ = gridZ;

        // Оновлення кольору в залежності від значення тексту(Value):
        updateColor();
    }

    void Cube::setGridCoords(int gridX, int gridZ)
    {
        this->gridX = gridX;
        this->gridZ = gridZ;
    }

    int Cube::getGridX() const
    {
        return gridX;      
    }

    int Cube::getGridZ() const
    {
        return gridZ;
    }

    void Cube::setPosition(float x, float y, float z)
    {
        setXCenter(x);
        setYCenter(y);
        setZCenter(z);
    }

    void Cube::setMerged(bool merged)
    {
        this->merged = merged;
    }

    bool Cube::isMerged() const
    {
        return merged;
    }

    void Cube::draw()
    {

        // Визначення властивостей матеріалу:
        // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, getDiffColor());
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, getAmbiColor());
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, getDiffColor());
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, getSpecColor());
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
        // Запис поточної матриці в стек
        // (збереження вмісту поточної матриці для подальшого використання):
        glPushMatrix();
        glTranslatef(getXCenter(), getYCenter(), getZCenter());

        float halfWidth = getXSize() / 2.0;
        float halfHeight = getYSize() / 2.0;
        float halfDepth = getZSize() / 2.0;

        // Малюємо грані куба з шести чотирикутників:
        glBegin(GL_QUADS);
        // Грань зі стороною від'ємного X:
        glNormal3f(-1, 0, 0);
        glVertex3f(-halfWidth, -halfHeight, -halfDepth);
        glVertex3f(-halfWidth, halfHeight, -halfDepth);
        glVertex3f(-halfWidth, halfHeight, halfDepth);
        glVertex3f(-halfWidth, -halfHeight, halfDepth);
        // Грань зі стороною позитивного X:
        glNormal3f(1, 0, 0);
        glVertex3f(halfWidth, -halfHeight, -halfDepth);
        glVertex3f(halfWidth, -halfHeight, halfDepth);
        glVertex3f(halfWidth, halfHeight, halfDepth);
        glVertex3f(halfWidth, halfHeight, -halfDepth);
        // Грань зі стороною від'ємного Y:
        glNormal3f(0, -1, 0);
        glVertex3f(-halfWidth, -halfHeight, -halfDepth);
        glVertex3f(-halfWidth, -halfHeight, halfDepth);
        glVertex3f(halfWidth, -halfHeight, halfDepth);
        glVertex3f(halfWidth, -halfHeight, -halfDepth);
        // Грань зі стороною позитивного Y:
        glNormal3f(0, 1, 0);
        glVertex3f(-halfWidth, halfHeight, -halfDepth);
        glVertex3f(halfWidth, halfHeight, -halfDepth);
        glVertex3f(halfWidth, halfHeight, halfDepth);
        glVertex3f(-halfWidth, halfHeight, halfDepth);
        // Грань зі стороною від'ємного Z:
        glNormal3f(0, 0, -1);
        glVertex3f(-halfWidth, -halfHeight, -halfDepth);
        glVertex3f(halfWidth, -halfHeight, -halfDepth);
        glVertex3f(halfWidth, halfHeight, -halfDepth);
        glVertex3f(-halfWidth, halfHeight, -halfDepth);
        // Грань зі стороною позитивного Z:
        glNormal3f(0, 0, 1);
        glVertex3f(-halfWidth, -halfHeight, halfDepth);
        glVertex3f(-halfWidth, halfHeight, halfDepth);
        glVertex3f(halfWidth, halfHeight, halfDepth);
        glVertex3f(halfWidth, -halfHeight, halfDepth);
        glEnd();

        // !
        glPushMatrix();
        // Додавання тексту на верхню грань куба:
        // Переміщення до верхньої грані куба:
        glTranslatef(0, halfHeight + 0.002, 0);
        // Масштабування тексту:

        // !float textScale = 0.0016 * getYSize();
        // Визначення та встановлення розміру тексту
        float textScale = 0.00042;
        float textWidth = 0.0f;
        float lineWidth = 6000.0 * textScale;
        glLineWidth(lineWidth);
        glScalef(textScale, textScale, textScale);

        std::string text = std::to_string(value);
        for (char c : text) {
            textWidth += glutStrokeWidth(GLUT_STROKE_MONO_ROMAN, c) / 1000.0;
        }

        // Визначення початкової позиції тексту:
        float textX = -textWidth / 0.002f;
        float textY = -45.0;
        float textZ = 0.0;

        // Ротація тексту, щоб він лежав плоско на верхній грані куба:
        glRotatef(-90, 1, 0, 0);

        // Виведення кожного символу тексту:
        //if (textValue <= 4) 
        //glColor3f(0.47f, 0.44f, 0.4f); // Сірий колір тексту
        glColor3f(1.0, 1.0, 1.0);  // Білий колір тексту
        // ! glPushMatrix();
        for (char c : text)
        {
            // Переміщення до початкової позиції кожного символу тексту
            glTranslatef(textX, textY, textZ);
            // Виведення символу на екран за допомогою GLUT
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, c);
            // Повернення до початкової позиції, щоб відобразити наступний символ
            glTranslatef(-textX, -textY, -textZ);
            // Збільшення значення зміщення по осі x на ширину символу
            textX += glutStrokeWidth(GLUT_STROKE_MONO_ROMAN, c) / 1000.0;
        }
        // TODO: Check whether this glPopMatrix() is needed.
        glPopMatrix();

        // Відновлення поточної матриці зі стека:
        glPopMatrix();

        // Оновлення кольору в залежності від значення тексту(textValue):
        updateColor();
    }

    void Cube::setValue(unsigned int value)
    {
        this->value = value;
        Cube::updateColor();
    }

    unsigned int Cube::getValue() const
    {
        return value;
    }

    void Cube::updateColor()
    {
        switch(value)
        {
            case 2:
                setColors(diffCubeColor2, ambiCubeColor2, specCubeColor2);
                break;
            case 4:
                setColors(diffCubeColor4, ambiCubeColor4, specCubeColor4);
                break;
            case 8:
                setColors(diffCubeColor8, ambiCubeColor8, specCubeColor8);
                break;
            case 16:
                setColors(diffCubeColor16, ambiCubeColor16, specCubeColor16);
                break;
            case 32:
                setColors(diffCubeColor32, ambiCubeColor32, specCubeColor32);
                break;
            case 64:
                setColors(diffCubeColor64, ambiCubeColor64, specCubeColor64);
                break;
            case 128:
                setColors(diffCubeColor128, ambiCubeColor128, specCubeColor128);
                break;
            case 256:
                setColors(diffCubeColor256, ambiCubeColor256, specCubeColor256);
                break;
            case 512:
                setColors(diffCubeColor512, ambiCubeColor512, specCubeColor512);
                break;
            case 1024:
                setColors(diffCubeColor1024, ambiCubeColor1024, specCubeColor1024);
                break;
            case 2048:
                setColors(diffCubeColor2048, ambiCubeColor2048, specCubeColor2048);
                break;
            default:
                break;
        }
    }

}
