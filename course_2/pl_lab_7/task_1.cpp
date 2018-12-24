/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 9
 *
 * Языки программирования
 * Лабораторная №7
 * Задание 1
 * В рамках данной лабораторной работы необходимо, используя C++ и OpenGL, разработать программу построения трехмерного объектов (буква в виде многогранника) в соответствии со своим вариантом задания. Грани объекта должны быть окрашены в определенный цвет. Ребра – черного цвета. Отобразить фигуру под углом, чтобы были видны грани и можно понять, что это 3D объект.
 */

#pragma comment(lib, "C:/SDKs/OpenGL/LIBs/Win32/glut32.lib")

#include <C:/SDKs/OpenGL/include/GL/glut.h>
#include <cmath>
//#include <iostream>

GLfloat Xcoords[4]          = { -0.5, -0.2, 0.2, 0.5 };
GLfloat Ycoords[4] = { 0.75,   // 1 -- 10    8 -- 7
                       0.1,    // |     | /  4    |

                      -0.1,    // |     9 /  |    |
                      -0.75    // 2 --- 3    5 -- 6
};
GLfloat Zdepth = 0.3;

GLdouble rotate_x = -25;  // поворот по оси х
GLdouble rotate_y = -25;  // поворот по оси у

GLvoid renderScene(GLvoid); // функция для перерисовки окна
GLvoid reshape(GLint w, GLint h);
GLvoid specialKeys(GLint key, GLint x, GLint y);

GLint main(GLint argc, GLbyte **argv) {
  glutInit(&argc, (char **)argv);  // инициализация
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1280, 720);
  glutCreateWindow("Лабараторная работа №7");
  //glutFullScreen();
  glEnable(GL_DEPTH_TEST);

  glutDisplayFunc(renderScene); // регистрация обратных вызовов
  glutReshapeFunc(reshape);
  glutSpecialFunc(specialKeys);
  glutMainLoop();  // Основной цикл GLUT

  return 1;
}

GLvoid renderScene(GLvoid) {
  glClearColor(1.0, 1.0, 1.0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glRotatef(rotate_x, 1.0, 0.0, 0.0);
  glRotatef(rotate_y, 0.0, 1.0, 0.0);

  GLfloat vertex_arr[20][3] = {
    { Xcoords[0], Ycoords[0], 0 },
    { Xcoords[0], Ycoords[3], 0 },
    { Xcoords[1], Ycoords[3], 0 },
    { Xcoords[2], Ycoords[1], 0 },
    { Xcoords[2], Ycoords[3], 0 },
    { Xcoords[3], Ycoords[3], 0 },
    { Xcoords[3], Ycoords[0], 0 },
    { Xcoords[2], Ycoords[0], 0 },
    { Xcoords[1], Ycoords[2], 0 },
    { Xcoords[1], Ycoords[0], 0 },
    { Xcoords[0], Ycoords[0], 0 - Zdepth },
    { Xcoords[0], Ycoords[3], 0 - Zdepth },
    { Xcoords[1], Ycoords[3], 0 - Zdepth },
    { Xcoords[2], Ycoords[1], 0 - Zdepth },
    { Xcoords[2], Ycoords[3], 0 - Zdepth },
    { Xcoords[3], Ycoords[3], 0 - Zdepth },
    { Xcoords[3], Ycoords[0], 0 - Zdepth },
    { Xcoords[2], Ycoords[0], 0 - Zdepth },
    { Xcoords[1], Ycoords[2], 0 - Zdepth },
    { Xcoords[1], Ycoords[0], 0 - Zdepth }
  };
  GLfloat color_arr[20][3] = { {0.0, 0.0, 0.0} };
  
  glVertexPointer(3, GL_FLOAT, 0, vertex_arr);
  glColorPointer(3, GL_FLOAT, 0, color_arr);
  // Лицеве рёбра
  GLubyte index_arr1[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  glDrawElements(GL_LINE_LOOP, 10, GL_UNSIGNED_BYTE, index_arr1);
  // Задние рёбра
  GLubyte index_arr2[10] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
  glDrawElements(GL_LINE_LOOP, 10, GL_UNSIGNED_BYTE, index_arr2);
  // Боковые рёбра
  GLubyte index_arr3[10][2] = { {0, 10},  {1, 11}, {2, 12}, {3, 13}, {4, 14}, {5, 15}, {6, 16}, {7, 17}, {8, 18}, {9, 19} };
  glDrawElements(GL_LINES, 20, GL_UNSIGNED_BYTE, index_arr3);

  GLubyte index_arr4[16][4] = {
    // Лицевая грань
    {0, 1, 2, 9},
    {2, 3, 7, 8},
    {7, 4, 5, 6},
    // Задняя грань
    {10, 19, 12, 11},
    {12, 18, 17, 13},
    {17, 16, 15, 14},
    // Боковые грани
    {0, 9, 19, 10},
    {1, 11, 12, 2},
    {7, 6, 16, 17},
    {4, 14, 15, 5},
    {8, 7, 17, 18},
    {2, 12, 13, 3},
    {0, 10, 11, 1},
    {6, 5, 15, 16},
    {8, 18, 19, 9},
    {4, 3, 13, 14}
  };
  glDrawElements(GL_QUADS, 16*4, GL_UNSIGNED_BYTE, index_arr4);

  glutSwapBuffers();
  //glutPostRedisplay();
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glFlush();  //Очистить все очереди команд и буферы OpenGL
}
GLvoid reshape(GLint w, GLint h) {
  GLint
    width,
    height,
    initX,
    initY;
  // шире, чем обычно
  if (w / 16 * 9 > h) {
    width = h / 9 * 16;
    height = h;
    initX = (w - width) / 2;
    initY = 0;
  }
  // уже, чем обычно
  else if (w / 16 * 9 < h) {
    width = w;
    height = w / 16 * 9;
    initX = 0;
    initY = (h - height) / 2;
  }
  // обычно
  else {
    width = w;
    height = h;
    initX = 0;
    initY = 0;
  }
  glViewport(initX, initY, width, height);

  glMatrixMode(GL_PROJECTION/*GL_MODELVIEW*/);
  glLoadIdentity();
  //gluOrtho2D(0, w, 0, h);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

GLvoid specialKeys(GLint key, GLint x, GLint y) {
  // Right arrow - increase rotation by 0.5 degree
  if (key == GLUT_KEY_RIGHT) rotate_y += 0.5;
  // Left arrow - decrease rotation by 0.5 degree
  else if (key == GLUT_KEY_LEFT) rotate_y -= 0.5;
  else if (key == GLUT_KEY_UP) rotate_x += 0.5;
  else if (key == GLUT_KEY_DOWN) rotate_x -= 0.5;
  // Request display update
  glutPostRedisplay();
}