#include "GLFW/glfw3.h"
#include <iostream>
#include <Windows.h>
using namespace std;

GLFWwindow* Window;
const int Width = 1400;
const int Height = 700;
char Answer = 'Y';
int i = 5,      //порядок
    l = 5,      //длина
    x = 5,      //x
    y = 5;      //y

void DrawLine(int X, int Y) {
    GLfloat Line[] = {
        x, y, 0,
        x+X, y+Y, 0
    };
    x += X;
    y += Y;

    glVertexPointer(3, GL_FLOAT, 0, Line);
    glDrawArrays(GL_LINES, 0, 2);
    if(Answer!='n') {
        glfwSwapBuffers(Window);
        glDrawArrays(GL_LINES, 0, 2);
        glfwSwapBuffers(Window);
        }
}

void A(int i);
void B(int i);
void C(int i);
void D(int i);

void A(int i) {
    if(i>0) {
        A(i - 1);
        DrawLine(l, l);
        B(i - 1);
        DrawLine(2 * l, 0);
        D(i - 1);
        DrawLine(l, -l);
        A(i - 1);
    }
}
void B(int i) {
    if (i > 0) {
        B(i-1);
        DrawLine(-l, l);
        C(i-1);
        DrawLine(0, 2 * l);
        A(i-1);
        DrawLine(l, l);
        B(i-1);

    }
}
void C(int i) {
    if (i > 0) {
        C(i-1);
        DrawLine(-l, -l);
        D(i-1);
        DrawLine(-2 * l, 0);
        B(i-1);
        DrawLine(-l, l);
        C(i-1);
    }

}
void D(int i) {
    if (i > 0) {
        D(i-1);
        DrawLine(l, -l);
        A(i-1);
        DrawLine(0, -2 * l);
        C(i-1);
        DrawLine(-l, -l);
        D(i-1);
    }
}


int main() {
    setlocale(LC_ALL,"");
    
    HWND windowHandle = GetConsoleWindow();     //Перехватываем консоль
    ShowWindow(windowHandle, SW_SHOW);          //Показываем консоль для ввода

    
    cout << "Использовать параметры по умолчанию? (Y/n)\n>";
    cin >> Answer;

    if(Answer=='n') {
        cout<<"Введите порядок кривой Серпинского: ";
        cin>>i;
        cout<<"Введите длину основания кривой: ";
        cin>>l;
        cout<<"Введите координаты начала:\nx=";
        cin>>x;
        cout<<"y=";
        cin>>y;
        cout<<"Отрисовывать в реальном времени?(Y/n)\n>";
        cin>>Answer;
    }
    ShowWindow(windowHandle, SW_HIDE);

    if (!glfwInit())
        return -1;
    
    Window = glfwCreateWindow(Width, Height, "Sierpinski's Curve", NULL, NULL); //Создаем окно
    glfwMakeContextCurrent(Window);
    glViewport(0.0f, 0.0f, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); 
    glOrtho(0.0f, Width, Height, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);               //Очищаем буфер
    glEnableClientState(GL_VERTEX_ARRAY);
    glLineWidth(1);                             //Задаем ширину линии
    
    A(i);
    DrawLine(l,l);
    B(i);
    DrawLine(-l,l);
    C(i);
    DrawLine(-l,-l);
    D(i);
    DrawLine(l,-l);

    glfwSwapBuffers(Window);                //Отрисовываем кадр (свапаем передний буфер с задним)
    


    while (!glfwWindowShouldClose(Window)) { //Пока не получен получен сигнал закрыться
        glfwPollEvents();                   //Отслеживать события
    }    
    glfwTerminate();                        //Завершиться
	
    
    return 0;
}