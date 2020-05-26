#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glut.h>

class Point {
public:
    float x, y;

    Point(float x, float y) : x (x), y (y) {};
};

const int WINDOW_W = 500;
const int WINDOW_H = 500;
std::vector<Point> points;
std::vector<Point> bezierCurve;
int dotIndex = -1;
const float _POINT_SIZE = 5.0f;

bool insideDot(float clickedX, float clickedY, float dotX, float dotY) {
    return dotX >= clickedX - _POINT_SIZE && dotX <= clickedX + _POINT_SIZE && dotY >= clickedY - _POINT_SIZE &&
           dotY <= clickedY + _POINT_SIZE;
}

int getDot(float x, float y) {
    float dotX;
    float dotY;
    int aux = 0;
    int maxSize = points.size ();

    while (aux < maxSize) {
        dotX = points[aux].x;
        dotY = points[aux].y;

        if (insideDot (x, y, dotX, dotY)) return aux;

        aux += 1;
    }

    return -1;
}

unsigned long long fact(int number) {
    unsigned long long result = 1;

    for (int i = number; i > 1; i -= 1) { result *= i; }

    return result;
}

unsigned long long optimizedFact(int number, int limit) {
    unsigned long long result = 1;

    for (int i = number; i > limit; i -= 1) { result *= i; }

    return result;
}

int getMax(int numberOne, int numberTwo) {
    return numberOne > numberTwo ? numberOne : numberTwo;
}

int getMin(int numberOne, int numberTwo) { return numberOne < numberTwo ? numberOne : numberTwo; }

unsigned long long comb(int n, int i) {
    int limit = getMax (i, n - i);
    int minimum = getMin (i, n - i);

    unsigned long long combResult = optimizedFact (n, limit) / (fact (minimum));

    return combResult;
}

void bezier() {
    bezierCurve.clear ();

    for (float t = 0; t <= 1; t += 0.01) {
        float x = 0;
        float y = 0;
        int maxSize = points.size () - 1;

        for (unsigned int i = 0; i < points.size (); i += 1) {
            x += comb (maxSize, i) * pow ((1 - t), (maxSize - i)) * pow (t, i) * points[i].x;
            y += comb (maxSize, i) * pow ((1 - t), (maxSize - i)) * pow (t, i) * points[i].y;
        }

        bezierCurve.push_back (Point (x, y));
    }
}

void reshape(int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho (0.0f, WINDOW_W, WINDOW_H, 0.0f, -5.0, 5.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

void handleKeypress(unsigned char key, int x, int y) {
    static int x1 = 0;
    switch (key) {
        case 27: // ESC
            exit (0);
            break;
        case 119:
            glLineWidth (5.0f);
            points.push_back (Point (x, y));
            glutPostRedisplay ();
            x1++;
            break;
        case 99:
            points.clear ();
            bezierCurve.clear ();
            glutPostRedisplay ();
    }
}

void handlePressedAndMovingMouse(int x, int y) {
    if (dotIndex != -1) {
        points.at (dotIndex).x = x;
        points.at (dotIndex).y = y;
        glutPostRedisplay ();

        bezier ();
    }
}

void handleMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN) {
            dotIndex = getDot (x, y);
        } else {
            dotIndex = -1;
            bezier ();
        }
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN) {    // se 'getDot' for diferente de -1, ja existe um ponto naquele local
            if (getDot (x, y) == -1) points.push_back (Point (x, y));

            bezier ();
        }
    if (button == GLUT_MIDDLE_BUTTON)
        if (state == GLUT_DOWN) {
            int index = getDot (x, y);

            if (index != -1) points.erase (points.begin () + index);

            bezier ();
        }

    glutPostRedisplay ();  // avisa que a janela atual deve ser reimpressa
}


void display() {
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity ();

    if (points.size () > 0) {
        glPointSize (_POINT_SIZE);
        glBegin (GL_POINTS);
        float colorCoef = 1.0f;

        for (unsigned int i = 0; i < points.size (); i++) {
            if (i < 20) glColor3f (0.0f, 1.0f, 0.0f);
            else if (i < 29) glColor3f (1.0f, 1.0f, 0.0f);
            else
                glColor3f (1.0f, 0.0f, 0.0f);

            glVertex2d (points.at (i).x, points.at (i).y);

            colorCoef -= 0.1f;
        }

        glEnd ();

        glBegin (GL_LINE_STRIP);
        glColor3f (1.0f, 1.0f, 1.0f);
        for (unsigned int i = 0; i < points.size (); i++) glVertex2d (points.at (i).x, points.at (i).y);
        glEnd ();
    }

    if (bezierCurve.size () > 2) {
        glBegin (GL_LINE_STRIP);
        glColor3f (0.5f, 0.0f, 1.0f);
        for (unsigned int i = 0; i < bezierCurve.size (); i++) glVertex2d (bezierCurve.at (i).x, bezierCurve.at (i).y);
        glEnd ();
    }

    glFlush ();
}


int main(int argc, char *argv[]) {
    std::cout << "Bezier Curve" << std::endl;
    glutInit (&argc, argv);      //初始化 GLUT 库.
    glutInitWindowPosition (50, 50); //首先确定窗口位置（它默认的是屏幕左上角）
    glutInitWindowSize (WINDOW_W, WINDOW_H);      //设置窗口大小
    glutInitDisplayMode (GLUT_RGB | GLUT_SINGLE); //定义显示方式

    glutCreateWindow ("Example OpenGL");          //创建窗口
    glMatrixMode (GL_MODELVIEW);     // 当前矩阵设定为模型视矩阵
    glLoadIdentity ();       // 模型视矩阵设置为单位矩阵

    glutDisplayFunc (display);     //注册一个绘图函数
    glutKeyboardFunc (handleKeypress);
    glutMouseFunc (handleMouseClick);
    glutMotionFunc (handlePressedAndMovingMouse);
    glutReshapeFunc (reshape);
    glutMainLoop ();
    return 0;
}
