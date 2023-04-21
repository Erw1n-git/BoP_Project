#include "Cube.h"

namespace Game
{
    Cube::Cube(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float *diffColor, float *ambiColor, float *specColor,
            unsigned int textValue)
            : Shape(xCenter, yCenter, zCenter,
                xSize, ySize, zSize,
                specColor, diffColor, ambiColor)
    { 
        this->textValue = textValue;
    }

    void Cube::draw()
    {
        // Визначення властивостей матеріалу:
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
        float textScale = 0.00032;
        float textWidth = 0.0f;
        float lineWidth = 6000.0 * textScale;
        glLineWidth(lineWidth);
        glScalef(textScale, textScale, textScale);

        std::string text = std::to_string(textValue);
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
        glPopMatrix();

        // Відновлення поточної матриці зі стека:
        glPopMatrix();
    }

}
