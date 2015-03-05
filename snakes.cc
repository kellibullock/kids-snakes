#include <GL/glut.h>
#include <cmath>
#include <cstdio>
#include <memory>
#include <vector>
#include <string>

constexpr float kColorBlack[] = {0, 0, 0};
constexpr float kColorWhite[] = {1, 1, 1};
constexpr float kColorRed[] = {1, 0, 0};
constexpr float kColorGreen[] = {0, 1, 0};
constexpr float kColorBlue[] = {0, 0, 1};
constexpr float kColorTeal[] = {0, 1, 1};
constexpr float kColorPurple[] = {1, 0, 1};
constexpr float kColorYellow[] = {1, 1, 0};

constexpr int speed = 200;  // Move snake every 300 ms

bool in_game = false;

struct Block {
  int x;
  int y;
};

std::vector<int> direction{0, 0};
std::vector<std::vector<Block>> snake{{{0, 0}}, {{0, 0}}};

void draw_rectangle(int x, int y, const float* color) {
  const GLdouble x_begin = -1.0 + x * 0.05;
  const GLdouble y_begin = -1.0 + y * 0.05;

  glBegin(GL_QUADS);
  glColor3fv(color);
  glVertex2f(x_begin, y_begin);
  glVertex2f(x_begin, y_begin + 0.05);
  glVertex2f(x_begin + 0.05, y_begin + 0.05);
  glVertex2f(x_begin + 0.05, y_begin);
  glEnd();
}

void Timer(int value) {
  for (int i = 0; i < 2; i++) {
    Block new_block = snake[i].back();

    switch (direction[i]) {
      case GLUT_KEY_RIGHT:
        new_block.x++;
        break;
      case GLUT_KEY_LEFT:
        new_block.x--;
        break;
      case GLUT_KEY_UP:
        new_block.y++;
        break;
      case GLUT_KEY_DOWN:
        new_block.y--;
        break;
    }

    if (new_block.y == -1 || new_block.y == 40 || new_block.x == -1 ||
        new_block.x == 40) {
      in_game = false;
    }

    snake[i].erase(snake[i].begin());
    snake[i].push_back(new_block);
  }

  if (in_game) {
    glutTimerFunc(speed, Timer, 0);
  }
  glutPostRedisplay();
}

void SpecialPressed(int key, int x, int y) {
  if (GLUT_KEY_UP == key || GLUT_KEY_DOWN == key || GLUT_KEY_LEFT == key ||
      GLUT_KEY_RIGHT == key) {
    direction[0] = key;
  }
}

void KeyPressed(unsigned char key, int x, int y) {
  if ('n' == key) {
    in_game = true;
    snake[0] = {{3, 5}, {4, 5}, {5, 5}};
    direction[0] = GLUT_KEY_RIGHT;
    snake[1] = {{33, 35}, {34, 35}, {35, 35}};
    direction[1] = GLUT_KEY_LEFT;
    glutTimerFunc(speed, Timer, 0);
  }
  if ('a' == key) {
    direction[1] = GLUT_KEY_LEFT;
  }
  if ('d' == key) {
    direction[1] = GLUT_KEY_RIGHT;
  }
  if ('w' == key) {
    direction[1] = GLUT_KEY_UP;
  }
  if ('s' == key) {
    direction[1] = GLUT_KEY_DOWN;
  }
}

void Display() {
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_QUADS);
  glColor3fv(kColorGreen);
  glVertex2f(1.25, 0.95);
  glVertex2f(1.25, -0.95);
  glVertex2f(-1.25, -0.95);
  glVertex2f(-1.25, 0.95);
  glEnd();

  glBegin(GL_QUADS);
  glColor3fv(kColorBlue);
  glVertex2f(0.95, 0.95);
  glVertex2f(0.95, -0.95);
  glVertex2f(-0.95, -0.95);
  glVertex2f(-0.95, 0.95);
  glEnd();

  if (in_game) {
    for (int i = 0; i < 2; i++) {
      for (auto b : snake[i]) {
        draw_rectangle(b.x, b.y, kColorWhite);
      }
    }
  } else {
    // There is something not quite right about this...
    const char* str = "Press n";
    glColor3fv(kColorWhite);
    glRasterPos2i(0, 0);
    for (size_t i = 0; i < sizeof(str); i++) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
  }

  glFlush();
}

void ScreenResized(int w, int h) {
  GLdouble aspect = ((GLdouble)w) / (GLdouble)h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (aspect > 1.3) {
    gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
  } else {
    gluOrtho2D(-1.3, 1.3, -1.3 / aspect, 1.3 / aspect);
  }
  glMatrixMode(GL_MODELVIEW);

  glViewport(0, 0, w, h);
}

int main(int argc, char** argv) {
  srand(time(nullptr));

  glutInit(&argc, argv);
  glutInitWindowSize(1000, 800);
  glutCreateWindow("Bouncing Ball");
  glutDisplayFunc(Display);
  glutIdleFunc(Display);
  glutSpecialFunc(SpecialPressed);
  glutKeyboardFunc(KeyPressed);
  glutReshapeFunc(ScreenResized);
  glutPostRedisplay();
  glutMainLoop();

  return 0;
}
