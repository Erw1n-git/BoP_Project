#include <GL/glut.h>
#include "disk.h"
#include "utils.h"

namespace DiskGame
{

    void Disk::draw()
    {
        // Визначення властивостей матеріалу:
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, getAmbiColor());
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, getDiffColor());
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, getSpecColor());
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
        // Запис поточної матриці в стек
        // (збереження вмісту поточної матриці для подальшого використання):
        glPushMatrix();
        glTranslatef(getXCenter(), getYCenter() + getYSize() / 2, getZCenter());
        // Циліндр повинен бути розташований у вертикальному напрямку:
        glRotatef(90, 1, 0, 0);
        GLUquadricObj* quadricObj = gluNewQuadric();
        gluCylinder(quadricObj, getXSize() / 2, getXSize() / 2, getYSize(), 20, 2);
        // Диск повинен бути намальований зовнішньою гранню догори:
        glRotatef(180, 1, 0, 0);
        // Малюємо диск зверху:
        gluDisk(quadricObj, innerRadius, getXSize() / 2, 20, 20);
        // Малюємо диск знизу:
        glTranslatef(0, 0, -getYSize());
        gluDisk(quadricObj, innerRadius, getXSize() / 2, 20, 20);
        gluDeleteQuadric(quadricObj);
        // Відновлення поточної матриці зі стека:
        glPopMatrix();
    }

}