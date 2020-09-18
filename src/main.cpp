// Standard headers
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

const double PI = std::acos(-1.0);

using namespace std;

template <typename T>
void println(T i)
{
    cout << i << endl;
}

void argsEcho(int argc, char** argv)
{
    println("____ARGS____");
    if (argc == 0) {
        println("NO ARGS");
    } else {
        for (int i = 0; i < argc; i++) {
            println(argv[i]);
        }
    }
    println("____________\n");
}

int main(int argc, char** argv)
    {
        argsEcho(argc, argv);
        println("Loban A., PA-18-2");

        if( !glfwInit() )
        {
            fprintf( stderr, "Ошибка при инициализации GLFW\n" );
            return -1;
        }
        glfwWindowHint(GLFW_SAMPLES, 4); // 4x Сглаживание
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Мы хотим использовать OpenGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

        GLFWwindow* window; // (В сопроводительном исходном коде эта переменная является глобальной)
        window = glfwCreateWindow( 800, 600, "Loban A.", nullptr, nullptr);

        if( window == nullptr ){
            fprintf( stderr, "Невозможно открыть окно GLFW. Если у вас Intel GPU, то он не поддерживает версию 3.3. Попробуйте версию уроков для OpenGL 2.1.\n" );
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);

        // Инициализируем GLEW
        glewExperimental=true; // Флаг необходим в Core-режиме OpenGL
        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "Невозможно инициализировать GLEW\n");
            return -1;
        }

        // Включим режим отслеживания нажатия клавиш, для проверки ниже
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

        double start_value = glfwGetTime(), colorRGB;
        int delta = 0;
        constexpr double change = 1;
        const double PI_half_deg = PI / 180;

        do {
            colorRGB = start_value - glfwGetTime();

            // Пока что ничего не выводим. Это будет в уроке 2.
            glClearColor(
                static_cast<float>(sin((colorRGB * delta) * PI_half_deg)),
                static_cast<float>(abs(cos((colorRGB * delta) * PI_half_deg))),
                static_cast<float>(abs(sin((colorRGB * delta) * PI_half_deg)) + cos((colorRGB * delta) * PI_half_deg)),
                1.0f);

            glClear(GL_COLOR_BUFFER_BIT);

            // Сбрасываем буферы
            glfwSwapBuffers(window);
            glfwPollEvents();

            if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            {
                std::cout << "Delta increased, delta = " << delta << std::endl;
                delta += change;
            }
            else if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                std::cout << "Delta decreased, delta = " << delta << std::endl;
                delta -= change;
            }

        }
        // Проверяем нажатие клавиши Escape или закрытие окна
        while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 );

        glfwTerminate();
        return 0;
}
