/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 9
 *
 * Языки программирования
 * Лабораторная №8
 * Задание 1
 * В рамках данной лабораторной работы необходимо, анимировать объекты, реализованные в лабораторной работе No7. Нанести текстуры на объект и реализовать возможность вращения камеры вокруг него при помощи мыши.
 */

#pragma comment(lib, "C:/libs/GL/glut32.lib")
#pragma comment(lib, "C:/libs/GL/glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

#include <C:/libs/GL/glut.h>
#include <C:/libs/GL/glaux.h>
#include <cmath>

#define CONSOLE_OUTPUT       _setmode(_fileno(stdout), _O_U16TEXT);
#include <conio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

GLfloat Xcoords[4] = {          -0.5, -0.2, 0.2, 0.5 };
GLfloat Ycoords[4] = { 0.75,   // 1 -- 10    8 -- 7
                       0.1,    // |     | /  4    |

                      -0.1,    // |     9 /  |    |
                      -0.75    // 2 --- 3    5 -- 6
};
GLfloat Zdepth = 0.3;

GLdouble rotate_x = 0;  // поворот по оси х
GLdouble rotate_y = 0;  // поворот по оси у

GLint  // положение мыши
  mouse_x,
  mouse_y;

AUX_RGBImageRec MyBitmap;
GLuint TexID;

GLvoid renderScene(GLvoid); // функция для перерисовки окна
GLvoid reshape(GLint w, GLint h);
GLvoid specialKeys(GLint key, GLint x, GLint y);
GLvoid Redraw(GLvoid);
GLvoid Motion(GLint x, GLint y);
GLvoid Motion_pass(GLint x, GLint y);
GLvoid Animation(int value);
GLint loadTexture(LPCWSTR FileName);

GLint main(GLint argc, GLbyte **argv) {
  #ifdef CONSOLE_OUTPUT
    CONSOLE_OUTPUT
  #endif

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
  glutMotionFunc(Motion);
  glutPassiveMotionFunc(Motion_pass);
  glutIdleFunc(Redraw);

  if (!loadTexture(L"image.bmp"))
    std::wcout << (L"Не удалось загрузить изображение\n") << std::endl;

  glutTimerFunc(0, Animation, 0);
  
  glutMainLoop();  // Основной цикл GLUT

  return 1;
}

GLvoid renderScene(GLvoid) {
  glClearColor(1.0, 1.0, 1.0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY_EXT);
  
  glEnable(GL_TEXTURE_2D);

  glLoadIdentity();

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
    { Xcoords[0], Ycoords[0], 0 + Zdepth },
    { Xcoords[0], Ycoords[3], 0 + Zdepth },
    { Xcoords[1], Ycoords[3], 0 + Zdepth },
    { Xcoords[2], Ycoords[1], 0 + Zdepth },
    { Xcoords[2], Ycoords[3], 0 + Zdepth },
    { Xcoords[3], Ycoords[3], 0 + Zdepth },
    { Xcoords[3], Ycoords[0], 0 + Zdepth },
    { Xcoords[2], Ycoords[0], 0 + Zdepth },
    { Xcoords[1], Ycoords[2], 0 + Zdepth },
    { Xcoords[1], Ycoords[0], 0 + Zdepth }
  };
  GLfloat texture_arr1[20][2] = {
    {0.0, 0.0},  // 1
    {1.0, 0.0},  // 2
    {1.0, 1.0},  // 3
    {1.0, 0.0},  // 4
    {1.0, 0.0},  // 5
    {1.0, 1.0},  // 6
    {0.0, 1.0},  // 7
    {0.0, 0.0},  // 8
    {0.0, 1.0},  // 9
    {0.0, 1.0}, // 10
    {1.0, 0.0},  // 11
    {0.0, 0.0},  // 12
    {0.0, 1.0},  // 13
    {0.0, 0.0},  // 14
    {0.0, 0.0},  // 15
    {0.0, 1.0},  // 16
    {1.0, 1.0},  // 17
    {1.0, 0.0},  // 18
    {1.0, 1.0},  // 19
    {1.0, 1.0}  // 20
  };
  
  // Взятие массива вершин
  glVertexPointer(3, GL_FLOAT, 0, vertex_arr);
  // Взятие массива текстур
  glTexCoordPointer(2, GL_FLOAT, 0, texture_arr1);

  // Грани
  // Лицевые, тыловые, верхние и нижние грани
  GLubyte index_arr4[12][4] = {
    // Лицевые грани
    {0, 1, 2, 9},
    {2, 3, 7, 8},
    {7, 4, 5, 6},
    // тыловые грани
    {10, 19, 12, 11},
    {12, 18, 17, 13},
    {17, 16, 15, 14},
    // Верхние грани
    {0, 9, 19, 10},
    {8, 7, 17, 18},
    {7, 6, 16, 17},
    // Нижние
    {1, 11, 12, 2},
    {4, 14, 15, 5},
    {2, 12, 13, 3}    
  };
  glDrawElements(GL_QUADS, 12 * 4, GL_UNSIGNED_BYTE, index_arr4);

  // Боковые грани
  GLfloat texture_arr2[20][2] = {
    {0.0, 0.0},  // 1  Изменено для корректного отображения боковых текстур
    {0.0, 1.0},  // 2  -//-
    {1.0, 1.0},  // 3
    {1.0, 1.0},  // 4  -//-
    {1.0, 0.0},  // 5  -//-
    {1.0, 1.0},  // 6  -// 
    {0.0, 1.0},  // 7  -//-
    {1.0, 1.0},  // 8  -//-  //
    {1.0, 0.0},  // 9  -//-
    {0.0, 0.0}, // 10  -//-
    {1.0, 0.0},  // 11  -//-
    {1.0, 1.0},  // 12  -//-
    {0.0, 1.0},  // 13
    {0.0, 1.0},  // 14  -//-
    {0.0, 0.0},  // 15  -//-
    {1.0, 0.0},  // 16  -//-
    {0.0, 0.0},  // 17  -//-
    {0.0, 0.0},  // 18  -//-  //
    {1.0, 1.0},  // 19  -//-
    {0.0, 1.0}  // 20  -//-
  };
  GLubyte index_arr5[4][4] = {
    {8, 18, 19, 9},
    {0, 10, 11, 1},
    {6, 5, 15, 16},  // 7, 6, 16, 17
    {4, 3, 13, 14}  // 5, 4, 14, 15
  };
  
  glTexCoordPointer(2, GL_FLOAT, 0, texture_arr2);
  glDrawElements(GL_QUADS, 4 * 4, GL_UNSIGNED_BYTE, index_arr5);
  
  // Рёбра
  glEnableClientState(GL_COLOR_ARRAY);
  GLfloat color_arr1[20][3] = { 0 };
  glColorPointer(3, GL_FLOAT, 0, color_arr1);
  // Лицеве
  GLubyte index_arr1[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  glDrawElements(GL_LINE_LOOP, 10, GL_UNSIGNED_BYTE, index_arr1);
  // Задние
  GLubyte index_arr2[10] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
  glDrawElements(GL_LINE_LOOP, 10, GL_UNSIGNED_BYTE, index_arr2);
  // Перпендикулярные плоскости XY
  GLubyte index_arr3[10][2] = { {0, 10},  {1, 11}, {2, 12}, {3, 13}, {4, 14}, {5, 15}, {6, 16}, {7, 17}, {8, 18}, {9, 19} };
  glDrawElements(GL_LINES, 10*2, GL_UNSIGNED_BYTE, index_arr3);

  glutSwapBuffers();
  glutPostRedisplay();
  glDisableClientState(GL_TEXTURE_COORD_ARRAY_EXT);
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
  // Right arrow - increase rotation by 1 degree
  if (key == GLUT_KEY_RIGHT) rotate_y += 1;
  // Left arrow - decrease rotation by 1 degree
  else if (key == GLUT_KEY_LEFT) rotate_y -= 1;
  else if (key == GLUT_KEY_UP) rotate_x += 1;
  else if (key == GLUT_KEY_DOWN) rotate_x -= 1;
  // Request display update
  glutPostRedisplay();
}

GLvoid Redraw(GLvoid) {
  
}

GLvoid Motion(GLint x, GLint y) {
  if (x > mouse_x) rotate_y -= (x - mouse_x)*0.3;
  if (y > mouse_y) rotate_x -= (y - mouse_y)*0.3;
  if (x < mouse_x) rotate_y += (mouse_x - x)*0.3;
  if (y < mouse_y) rotate_x += (mouse_y - y)*0.3;

  mouse_x = x;
  mouse_y = y;
}

GLvoid Motion_pass(GLint x, GLint y) {
  mouse_x = x;
  mouse_y = y;
}

GLvoid Animation(int value) {
  static GLfloat i = 0;
     
  Ycoords[0] = 0.75 + sin(i)*0.1;
  Ycoords[3] = -0.75 - sin(i)*0.1;

  Xcoords[0] = -0.5 + sin(i)*0.05;
  Xcoords[1] = -0.2 + sin(i)*0.05;

  Xcoords[2] = 0.2 - sin(i)*0.05;
  Xcoords[3] = 0.5 - sin(i)*0.05;

  i += 0.1;

  //glutPostRedisplay();
  glutTimerFunc(20, Animation, 0);
}

GLint loadTexture(LPCWSTR FileName) {
  //--Выравнивание в *.bmp по байту-------------------------------------//
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  //--Создание идентификатора для текстуры- ----------------------------//
  glGenTextures(1, &TexID);
  //--Загрузка изображения в память-------------------------------------//
  AUX_RGBImageRec *pImage = auxDIBImageLoad(FileName);

  int BmpWidth = pImage->sizeX;
  int BmpHeight = pImage->sizeY;
  void *BmpBits = pImage->data;

  //--Начало описания свойств текстуры----------------------------------//
  glBindTexture(GL_TEXTURE_2D, TexID);
  //--Создание уровней детализации и инициализация текстуры ------------//
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, BmpWidth, BmpHeight, GL_RGB,
    GL_UNSIGNED_BYTE, BmpBits);

  //--Разрешение наложения этой текстуры на quadric-объекты-------------//
  //--Задание параметров текстуры---------------------------------------//
  //--Повтор изображения по параметрическим осям s и t------------------//
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //--Не использовать интерполяцию при выборе точки на текстуре---------//
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //--Совмещать текстуру и материал объекта-----------------------------//
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  return 1;
}
