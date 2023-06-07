#include <GL/glut.h>
#include "Scene.h"
#include "Utils/Utils.h"

using Game::Scene;

Scene *scene;

// Обробка події, пов'язаної з перемалюванням вікна
void on_paint()
{
    scene->on_paint();
}

// Обробка події, пов'язаної зі зміною розмірів вікна
void on_size(int width, int height)
{
    scene->on_size(width, height);
}

// Обробка подій, пов'язаних з натисканням кнопок миші
void on_mouse(int button, int state, int x, int y)
{
    scene->on_mouse(button, state, x, y);
}

// Обробка подій, пов'язаних з пересуванням миші з натисненою кнопкою
void on_motion(int x, int y)
{
    scene->on_motion(x, y);
}

// Обробка подій від спеціальних клавіш клавіатури:
void on_special(int key, int x, int y)
{
    scene->on_special(key, x, y);
}

// Обробка подій від клавіатури:
void on_keyboard(unsigned char key, int x, int y)
{
    scene->on_keyboard(key, x ,y);
}

// Обробка події від таймера
void on_timer(int value)
{
    scene->on_timer(value);
    glutTimerFunc(25, on_timer, 0);
}

int main(int argc, char* argv[])
{
    // Ініціалізуємо GLUT та встановлюємо основні параметри вікна 
    glutInit(&argc, argv);
    scene = new Scene(GraphUtils::xStep, GraphUtils::zStep);
    glutInitWindowSize(900, 900);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glEnable(GLUT_MULTISAMPLE);
    glutCreateWindow("2048"); 

    // Реєстрація функцій 
    glutDisplayFunc(on_paint);
    glutReshapeFunc(on_size);
    glutMotionFunc(on_motion);
    glutMouseFunc(on_mouse);
    glutKeyboardFunc(on_keyboard);
    glutSpecialFunc(on_special);
    glutTimerFunc(10, on_timer, 0);

    // Запуск основного циклу обробки подій
    glutMainLoop();

    delete scene;
    return(0);
}