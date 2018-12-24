/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 9
 *
 * Языки программирования
 * Лабораторная №6
 * Задание 1
 * В рамках данной лабораторной работы необходимо, используя C++ и OpenGL, разработать программу построения 2D объектов в соответствии со своим вариантом задания.
 */

#pragma comment(lib, "C:/SDKs/OpenGL/LIBs/Win32/glut32.lib")

#include <C:/SDKs/OpenGL/include/GL/glut.h>
#include <cmath>

#define M_PI 3.14159265358979323846

const GLint width = 1024;
const GLint height = 768;

GLvoid renderScene(GLvoid); // функция для перерисовки окна
GLvoid reshape(GLint w, GLint h);

GLvoid StrokeEllipse(GLfloat xCenter, GLfloat yCenter, GLfloat rx, GLfloat ry, GLint pointCount = 360);
GLvoid FillEllipse(GLfloat xCenter, GLfloat yCenter, GLfloat rx, GLfloat ry, GLint pointCount = 360);
GLvoid Rectangle(GLint x, GLint y, GLint w, GLint h);

GLint main(GLint argc, GLbyte **argv) {
  glutInit(&argc, (char **) argv);  // инициализация
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(200, 50);
  glutInitWindowSize(width, height);
  glutCreateWindow("Лабараторная работа №6");  
  glutDisplayFunc(renderScene); // регистрация обратных вызовов
  glutReshapeFunc(reshape);
  glutMainLoop();  // Основной цикл GLUT

  return 1;
}

GLvoid renderScene(GLvoid) {
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub(128, 128, 0);
  Rectangle(width/2-210/2, height-50, 210, 70);
    
  glColor3ub(128, 255, 255);
  FillEllipse(    width / 2,    height - 50 - 70 - 65,                    125, 65);
  glColor3ub(0, 0, 0);
  StrokeEllipse(  width / 2,    height - 50 - 70 - 65,                    125, 65);

  glColor3ub(128, 255, 255);
  FillEllipse(width / 2,        height - 50 - 70 - 65*2 - 80,             175, 80);
  glColor3ub(0, 0, 0);
  StrokeEllipse(width / 2,      height - 50 - 70 - 65*2 - 80,             175, 80);

  glColor3ub(128, 255, 255);
  FillEllipse(width / 2,        height - 50 - 70 - 65*2 - 80*2 - 130,     275, 130);
  glColor3ub(0, 0, 0);
  StrokeEllipse(width / 2,      height - 50 - 70 - 65*2 - 80*2 - 130,     275, 130);

  glutSwapBuffers();
  glFlush(); //Очистить все очереди команд и буферы OpenGL
}
GLvoid reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

GLvoid Rectangle(GLint x, GLint y, GLint w, GLint h) {
  glBegin(GL_QUADS);
  glVertex2i(x, y);
  glVertex2i(x, y - h);
  glVertex2i(x + w, y - h);
  glVertex2i(x + w, y);
  glEnd();
}
GLvoid StrokeEllipse(GLfloat xCenter, GLfloat yCenter, GLfloat rx, GLfloat ry, GLint pointCount) {
  const float step = float(2 * M_PI / pointCount);

  // Эллипс представлен в виде незамкнутой ломаной линии, соединяющей
  // pointCount точек на его границе с шагом 2*PI/pointCount
  glBegin(GL_LINE_STRIP);
  for (float angle = 0; angle < float(2 * M_PI); angle += step) {
    const float dx = rx * cosf(angle);
    const float dy = ry * sinf(angle);
    glVertex2f(dx + xCenter, dy + yCenter);
  }

  glEnd();
}
GLvoid FillEllipse(GLfloat xCenter, GLfloat yCenter, GLfloat rx, GLfloat ry, GLint pointCount) {
  const float step = float(2 * M_PI) / pointCount;

  // Эллипс представлет в виде "веера" из треугольников
  glBegin(GL_TRIANGLE_FAN);
  // Начальная точка веера располагается в центре эллипса
  glVertex2f(xCenter, yCenter);
  // Остальные точки - равномерно по его границе
  for (float angle = 0; angle <= float(2 * M_PI); angle += step) {
    float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
    const float dx = rx * cosf(a);
    const float dy = ry * sinf(a);
    glVertex2f(dx + xCenter, dy + yCenter);
  }

  glEnd();
}