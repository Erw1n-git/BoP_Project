#include "Cube.h"

namespace Game
{
    Cube::Cube(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            int gridX, int gridZ, std::string value)
            : Shape(xCenter, yCenter, zCenter,
                xSize, ySize, zSize,
                nullptr, nullptr, nullptr)
    { 
        this->value = value;
        this->gridX = gridX;
        this->gridZ = gridZ;

        updateColor();
    }

    void Cube::draw()
    {

        // Визначення властивостей матеріалу:
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, getAmbiColor());
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, getDiffColor());
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, getSpecColor());
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);

        // Запис поточної матриці в стек
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

        glPushMatrix();

        glTranslatef(0, halfHeight + 0.002, 0);

        // Визначення та встановлення розміру тексту
        float textScale = 0.00042;
        float textWidth = 0.0f;
        float lineWidth = 6000.0 * textScale;
        glLineWidth(lineWidth);
        glScalef(textScale, textScale, textScale);

        for (char c : value) {
            textWidth += glutStrokeWidth(GLUT_STROKE_MONO_ROMAN, c) / 1000.0;
        }

        // Визначення початкової позиції тексту
        float textX = -textWidth / 0.002f;
        float textY = -45.0;
        float textZ = 0.0;

        // Ротація тексту, щоб він лежав плоско на верхній грані куба
        glRotatef(-90, 1, 0, 0);

        glColor3f(1.0, 1.0, 1.0); 

        // Виведення кожного символу тексту
        for (char c : value)
        {
            glTranslatef(textX, textY, textZ);
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, c);
            glTranslatef(-textX, -textY, -textZ);
            textX += glutStrokeWidth(GLUT_STROKE_MONO_ROMAN, c) / 1000.0;
        }

        // Відновлення трансформації тексту, застосовані до куба.
        glPopMatrix();

        // Відновлення матриці до стану перед малюванням куба.
        glPopMatrix();

        // Оновлення кольору в залежності від значення тексту(textValue):
        updateColor();
    }

    // Встановлення значень положення у сітці 'grid'
    void Cube::setGridCoords(int gridX, int gridZ)
    {
        this->gridX = gridX;
        this->gridZ = gridZ;
    }

    // Встановлення значення кубу
    void Cube::setValue(std::string value)
    {
        this->value = value;
        Cube::updateColor();
    }

    // Оновлення кольору в залежності від значення 'value'
    void Cube::updateColor()
    {
        if (value == "2") {
            setColors(diffCubeColor2, ambiCubeColor2, specCubeColor2);
        } else if (value == "4") {
            setColors(diffCubeColor4, ambiCubeColor4, specCubeColor4);
        } else if (value == "8") {
            setColors(diffCubeColor8, ambiCubeColor8, specCubeColor8);
        } else if (value == "16") {
            setColors(diffCubeColor16, ambiCubeColor16, specCubeColor16);
        } else if (value == "32") {
            setColors(diffCubeColor32, ambiCubeColor32, specCubeColor32);
        } else if (value == "64") {
            setColors(diffCubeColor64, ambiCubeColor64, specCubeColor64);
        } else if (value == "128") {
            setColors(diffCubeColor128, ambiCubeColor128, specCubeColor128);
        } else if (value == "256") {
            setColors(diffCubeColor256, ambiCubeColor256, specCubeColor256);
        } else if (value == "512") {
            setColors(diffCubeColor512, ambiCubeColor512, specCubeColor512);
        } else if (value == "1024") {
            setColors(diffCubeColor1024, ambiCubeColor1024, specCubeColor1024);
        } else if (value == "2048") {
            setColors(diffCubeColor2048, ambiCubeColor2048, specCubeColor2048);
        } else {
            setColors(diffCubeColor2, ambiCubeColor2, specCubeColor2);
        }
    }

}
