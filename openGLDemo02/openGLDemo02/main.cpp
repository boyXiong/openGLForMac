//
//  main.cpp
//  openGLDemo02
//
//  Created by key on 2021/10/26.
//
//

#include "main.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include "training01.hpp"
#include "Shader.hpp"
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//顶点着色器源码  一般使用常量
//const GLchar* vertexShaderSource = "#version 330 core\n"
//    "layout (location = 0) in vec3 position;\n"
//    "void main()\n"
//    "{\n"
//    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
//    "}\0";
//
////偏单着色器源码
//const GLchar* fragmentShaderSource = "#version 330 core\n"
//    "out vec4 color;\n"
//    "void main()\n"
//    "{\n"
//    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//    "}\n\0";

//用类
int useShaderClass();

int triangles();
//三角形
void triangles(GLuint * shaderProgramPtr, GLuint *VAOPtr);

//使用纹理
int useTexture();

//按键回调函数接受一个GLFWwindow指针作为它的第一个参数；第二个整形参数用来表示按下的按键；action参数表示这个按键是被按下还是释放；最后一个整形参数表示是否有Ctrl、Shift、Alt、Super等按钮的操作。GLFW会在合适的时候调用它，并为各个参数传入适当的值。
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    
    printf("key:%d, scancode:%d, action:%d, mode:%d", key, scancode, action, mode);
    // 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
    // 关闭应用程序
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


int main() {
    
  

//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//    glGenerateMipmap(GL_TEXTURE_2D);
    
    //
    useTexture();

    
//    train1();
//    triangles();
    
    return 0;

    
}


int useTexture() {
    
    //初始化 glfw 窗口
    glfwInit();
    
    // 进行窗口配置
    // MAJOR 主版本 设置为 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // MINOR 此版本 设置为 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // profile 使用的平台核心 是 core_profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 是否可以 resizeable 设置大小 调整大小
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    // forward_compat  置顶 mac_ox 需要这句
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    printf("start");
    
    //创建窗口 宽 高  标题
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    
    //窗口如果等于 空指针
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        //关掉窗口
        glfwTerminate();
        return -1;
    }
    
    //创建完窗口我们就可以通知GLFW将我们窗口的上下文设置为当前 线程 的主上下文了。
    glfwMakeContextCurrent(window);
    
    //glew 实验性的
    glewExperimental = GL_TRUE;
    //初始化  glew
    if (glewInit() != GLEW_OK)
    {
        printf( "Failed to initialize GLEW");
        return -1;
    }
    
    int width, height;
    // 获取 window 对应的 宽 高
    //直接从GLFW中获取的。我们从GLFW中获取视口的维度而不设置为800*600是为了让它在高DPI的屏幕上（比如说Apple的视网膜显示屏
    glfwGetFramebufferSize(window, &width, &height);
  
    std::cout << "width: " << width << " height :" << height << std::endl;
    //前2个是用来控制窗口左下角 渲染宽高,
    glViewport(0, 0, width, height);
    
    //连接2个这色器
    Shader ourShader("/Users/key/Documents/Code/OpenGL/openGLDemo02/openGLDemo02/vertexData/shaderTextrue.vs", "/Users/key/Documents/Code/OpenGL/openGLDemo02/openGLDemo02/vertexData/shaderTextrue.frag");
    
    
    //顶点数据
    GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
    };
    
    //绘制矩形 需要2个三角形， 0 1 3 是一个   1 2 3 是一个
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };
    
    
    
    //创建顶点数据 缓存
    GLuint VBO, VAO, EBO;
    //顶点数据缓存 数组
    glGenVertexArrays(1, &VAO);
 
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    
    //绑定数组缓存
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //绑定标签数据 用来告诉 GPU怎么 读取VAO 顶点数组的顺序
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute  顶点位置读取，如果读取数组内存
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    
    // 启动顶点数据数据属性 2，就是 0,1,2
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO

    //载入 创建纹理
    // Load and create a texture
    GLuint texture1;
    GLuint texture2;
    // ====================
    // Texture 1
    // ====================
    
    //创建纹理空间
    glGenTextures(1, &texture1);
    //绑定渲染器空间指针
    glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering 过滤器
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load, create texture and generate mipmaps
    int imageWidth, imageHeight;
    unsigned char* image = SOIL_load_image("/Users/key/Downloads/test2.png", &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB);
    
    
    //创建纹理 纹理类型，  第4个参数是历史原因是 0
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // 生成纹理
    glGenerateMipmap(GL_TEXTURE_2D);
    
    //清空数据图片
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
    // ===================
    // Texture 2
    // ===================
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load, create texture and generate mipmaps
    image = SOIL_load_image("/Users/key/Downloads/test.png", &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    
    //将纹理渲染到
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind Textures using texture units
        glActiveTexture(GL_TEXTURE0); //在绑定纹理之前先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, texture1);
        //更改这色器 值
        glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
        
        glActiveTexture(GL_TEXTURE1); //在绑定纹理之前先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, texture2);
        //更改这色器 值
        glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);
        
        
        
        // Activate shader
        ourShader.Use();
        
        
        
        //渐变
        GLfloat timeValue = glfwGetTime();
        GLfloat per = (sin(timeValue) / 2) + 0.5;
        //更改 着色器的 变化值
        glUniform1f(glGetUniformLocation(ourShader.Program, "ourTexture1AndOurTexture2Per"), per);
        //更改坐标
        glUniform1f(glGetUniformLocation(ourShader.Program, "texCoordPostion"), per);
        
        // Create transformations
        glm::mat4 transform;
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 0.0f, 1.0f));


        glm::vec4 vec(0.5f, 0.5f, 0.0f, 1.0f);
        vec = transform * vec;
        std::cout << "x:" << vec.x << " y:" << vec.y << " z:" << vec.z << " w:" << vec.w << std::endl;

         // Get matrix's uniform location and set matrix
         GLint transformLoc = glGetUniformLocation(ourShader.Program, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        
        
        // Draw container
        glBindVertexArray(VAO);
        //画 的类型 6个点
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        //解绑 VAO  数据
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
 
    return 0;
}


int useShaderClass() {
    
    //初始化 glfw 窗口
    glfwInit();
    
    // 进行窗口配置
    // MAJOR 主版本 设置为 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // MINOR 此版本 设置为 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // profile 使用的平台核心 是 core_profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 是否可以 resizeable 设置大小 调整大小
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    // forward_compat  置顶 mac_ox 需要这句
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    printf("start");
    
    //创建窗口 宽 高  标题
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    
    //窗口如果等于 空指针
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        //关掉窗口
        glfwTerminate();
        return -1;
    }
    
    //创建完窗口我们就可以通知GLFW将我们窗口的上下文设置为当前 线程 的主上下文了。
    glfwMakeContextCurrent(window);
    
    //glew 实验性的
    glewExperimental = GL_TRUE;
    //初始化  glew
    if (glewInit() != GLEW_OK)
    {
        printf( "Failed to initialize GLEW");
        return -1;
    }
    
    int width, height;
    // 获取 window 对应的 宽 高
    //直接从GLFW中获取的。我们从GLFW中获取视口的维度而不设置为800*600是为了让它在高DPI的屏幕上（比如说Apple的视网膜显示屏
    glfwGetFramebufferSize(window, &width, &height);
  
    std::cout << "width: " << width << " height :" << height << std::endl;
    //前2个是用来控制窗口左下角 渲染宽高,
    glViewport(0, 0, width, height);
    Shader ourShader("/Users/key/Documents/Code/OpenGL/openGLDemo02/openGLDemo02/vertexData/shader.vs", "/Users/key/Documents/Code/OpenGL/openGLDemo02/openGLDemo02/vertexData/shader.frag");
    
    
    //菱形 坐标，openGL 主要用来绘制 3角形，如果使用菱形，可以画2个三角形，但是这样如果很多的情况下，就非常麻烦了，于是有了索引，指定画线的顺序，这样
    GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f,   // 右上角
        0.0f, -0.5f, 0.0f,  // 右下角
        -0.5f, 0.0f, 0.0f, // 左下角
    };
    GLuint VBO;
    //创建缓存 表示与地址开始
    glGenBuffers(1, &VBO);
    //绑定 缓存空间 与指针
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 放入数据到 顶点缓存空间
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    
    //使用 VAO 顶点数组对象(Vertex Array Object, VAO)
    GLuint VAO;
    //直接创建顶点数据缓存
    glGenVertexArrays(1, &VAO);
    //绑定缓存空间地址
    glBindVertexArray(VAO);
    //
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //3. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    
    //解绑
    glBindVertexArray(0);
    
    
    //绑定 点数组对象(Vertex Array Object, VAO) 用来告诉 写入内容
    // OpenGL的核心模式要求我们使用VAO，所以它知道该如何处理我们的顶点输入。如果我们绑定VAO失败，OpenGL会拒绝绘制任何东西。
    glBindVertexArray(VAO);

    //游戏循环(Game Loop) 窗口可以一直接受事件 进行处理
    while(!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ourShader.Use();
//        glUniform1f(glGetUniformLocation(ourShader.Program, "someUniform"), 1.0f);
        //
        glDrawArrays(GL_TRIANGLES, 0, 3);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
    }
    
    // 清空数据
    // Properly de-allocate all resources once they've outlived their purpose
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
    //关闭 终结 glf 并释放 GLFW分配的内存
    glfwTerminate();
    return 0;
    
    
}





//绘制三角形
int triangles() {
    //初始化 glfw 窗口
    glfwInit();
    
    // 进行窗口配置
    // MAJOR 主版本 设置为 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // MINOR 此版本 设置为 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // profile 使用的平台核心 是 core_profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 是否可以 resizeable 设置大小 调整大小
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    // forward_compat  置顶 mac_ox 需要这句
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    printf("start");
    
    //创建窗口 宽 高  标题
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    
    //窗口如果等于 空指针
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        //关掉窗口
        glfwTerminate();
        return -1;
    }
    
    //创建完窗口我们就可以通知GLFW将我们窗口的上下文设置为当前 线程 的主上下文了。
    glfwMakeContextCurrent(window);
    
    //glew 实验性的
    glewExperimental = GL_TRUE;
    //初始化  glew
    if (glewInit() != GLEW_OK)
    {
        printf( "Failed to initialize GLEW");
        return -1;
    }
    
    int width, height;
    // 获取 window 对应的 宽 高
    //直接从GLFW中获取的。我们从GLFW中获取视口的维度而不设置为800*600是为了让它在高DPI的屏幕上（比如说Apple的视网膜显示屏
    glfwGetFramebufferSize(window, &width, &height);
  
    std::cout << "width: " << width << " height :" << height << std::endl;
    //前2个是用来控制窗口左下角 渲染宽高,
    glViewport(0, 0, width, height);
    
    glfwSetKeyCallback(window, key_callback);
    
    
    //初始化对应的着色器数据
    //创建一个 3D 顶点坐标位置
    
    
    // 三角形 坐标 坐标永远都是在 -1 ~ 1 区间内
//    GLfloat vertices[] = {
//        -0.5f, -0.5f, 0.0f,
//         0.5f, -0.5f, 0.0f,
//         0.0f,  0.5f, 0.0f
//    };
    
    //菱形 坐标，openGL 主要用来绘制 3角形，如果使用菱形，可以画2个三角形，但是这样如果很多的情况下，就非常麻烦了，于是有了索引，指定画线的顺序，这样
    GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };

    //索引点线
    GLuint indices[] = { // 注意索引从0开始!
        0, 1, 3, // 第一个三角形
        1, 2, 3,  // 第二个三角形
    };
    
    //创建索引的缓存
    GLuint EBO;
    glGenBuffers(1, &EBO);
    // 将 EBO  绑定 容器 GL_ELEMENT_ARRAY_BUFFER 中
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // 将 EBO  绑定 容器 GL_ELEMENT_ARRAY_BUFFER 中
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //第一个是绘制的模式，第二个是绘制多少个顶点，第三个 索引类型 这里就是这个， 第四个就是EBO的偏移量
    
    
    
    
    
    
    GLuint VBO;
    //创建缓存
    glGenBuffers(1, &VBO);
    //绑定到 顶点缓存上面 ，顶点类型就有了缓存空间
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // 将 顶点坐标 渲染到缓存上面
    // 缓存类型，  大小， 数据， 静态渲染绘制 不需要怎么改变 渲染的，每次都一个鸟样
    /*
     GL_STATIC_DRAW ：数据不会或几乎不会改变。
     GL_DYNAMIC_DRAW：数据会被改变很多。
     GL_STREAM_DRAW ：数据每次绘制时都会改变。
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //到这里 已经把数据 存储在显卡的内存上了
    
    //创建 顶点 和片段
    // vertex shader 顶点着色器
    
//    layout (location = 0) in vec3 position;
    //1. 着色器 创建
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 第一个参数  着色器 是啥， 传递源码字符串数量 为 1，
//    char tmpVertexShaderSource[] = "#version 330 core\n"
//    "layout (location = 0) in vec3 position;\n"
//    "void main()\n"
//    "{\n"
//    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
//    "}\0";
//    char *vertexShaderSource = tmpVertexShaderSource;
    
    // 解析着色器类型,
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    
    //获取编辑成功或者失败
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        glGetShaderInfoLog(vertexShader, GL_COMPILE_STATUS, NULL,  infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n: %s", infoLog);
    }
    
    
    
    //2. 片段着色器
    //
//    char tmpfragmentShaderSource[] = "#version 330 core\
//    out vec4 color;\
//    void main()\
//    {\
//        color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\
//    }";
//    char *fragmentShaderSource = tmpfragmentShaderSource;
    
    GLint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    
    //3 将2个 着色器 进行链接在一起
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    //给 program 增加属性 2个着色器
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    //获取链接程序错误，检测链接是否失败
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::PROGRAM_LINK_FAILED\n: %s", infoLog);
    }
    
    //使用激活这个程序
    glUseProgram(shaderProgram);
    
    //删除2个着色器分配的空间
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //到目前为止 已经把顶点数据发送给GPU了
    
    //告诉 openGL 如果解析数据  3个 vertex  队列解析
    //1, 从哪里开始， 2 总长度， 3，每次解析的数据类型 , 4 数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。
    
    //5. 步长步长(Stride),   6 偏移量 void 0 ， 偏移量(Offset)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    
    
    
    //0 copy 顶点数据 到缓冲中 提供 OpenGle 使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 1 设置顶点属性指针 调用进行的顶点缓冲对象与顶点属性链接。
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    // 启动顶点数据
    glEnableVertexAttribArray(0);
    
    // 2.渲染数据的时候 需要使用着色器
    glUseProgram(shaderProgram);
    // 3.绘制物体
//    someOpenGLFuncationThatDrawsOurTriangle();
    
    
    //使用 VAO 顶点数组对象(Vertex Array Object, VAO)
    GLuint VAO;
    //直接创建顶点数据缓存
    glGenVertexArrays(1, &VAO);
    
    //初始化代码只运行一次，除非物体改变的很平凡
    //绑定VAO
    glBindVertexArray(VAO);
    
    //2. 把顶点数据复制到 缓冲中供openGL 使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    
    //2.2 将索引数组复制到一个索引缓冲中，供OpenGL 使用
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    
    //3. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    
    //解绑
    glBindVertexArray(0);
    
    
    // 5 绘制物体
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    // 3.绘制物体
//    someOpenGLFuncationThatDrawsOurTriangle();
    //释放缓存
    glBindVertexArray(0);
    
    
    //使用线性绘制模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //游戏循环(Game Loop) 窗口可以一直接受事件 进行处理
    while(!glfwWindowShouldClose(window))
    {
        //检查事件 有事件 就进行处理
        glfwPollEvents();
        
        //清空色值 状态设置函数
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        // 状态应用函数
        glClear(GL_COLOR_BUFFER_BIT);
        //函数会交换颜色缓冲  存储 GLFW窗口每一个像素颜色的大缓冲
        
        //绘制
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

     
        
        glfwSwapBuffers(window);
    }
    
    // 清空数据
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //关闭 终结 glf 并释放 GLFW分配的内存
    glfwTerminate();
    return 0;
}
   





//三角形 形状 坐标定位, 传输参数，初始化， 链接程序，与 顶点对象指针
void trianglesInt(GLuint * shaderProgramPtr, GLuint *VAOPtr) {
    
    //创建一个 3D 顶点坐标位置
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    
    GLuint VBO;
    //创建缓存
    glGenBuffers(1, &VBO);
    //绑定到 顶点缓存上面 ，顶点类型就有了缓存空间
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // 将 顶点坐标 渲染到缓存上面
    // 缓存类型，  大小， 数据， 静态渲染绘制 不需要怎么改变 渲染的，每次都一个鸟样
    /*
     GL_STATIC_DRAW ：数据不会或几乎不会改变。
     GL_DYNAMIC_DRAW：数据会被改变很多。
     GL_STREAM_DRAW ：数据每次绘制时都会改变。
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //到这里 已经把数据 存储在显卡的内存上了
    
    //创建 顶点 和片段
    // vertex shader 顶点着色器
    
//    layout (location = 0) in vec3 position;
    //1. 着色器 创建
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 第一个参数  着色器 是啥， 传递源码字符串数量 为 1，
//    char tmpVertexShaderSource[] = "layout (location = 0) in vec3 position;\
//    void main()\
//    {\
//        gl_Position = vec4(position.x, position.y, position.z, 1.0);\
//    }";
// 上面 写的有错误
    char tmpVertexShaderSource[] = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";



    char *vertexShaderSource = tmpVertexShaderSource;
    
    // 解析着色器类型,
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    
    //获取编辑成功或者失败
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        glGetShaderInfoLog(vertexShader, GL_COMPILE_STATUS, NULL,  infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n: %s", infoLog);
    }
    
    
    
    //2. 片段着色器
    //
    char tmpfragmentShaderSource[] = "#version 330 core\
    out vec4 color;\
    void main()\
    {\
        color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\
    }";
    char *fragmentShaderSource = tmpfragmentShaderSource;
    
    GLint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    
    
    //3 将2个 着色器 进行链接在一起
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    //给 program 增加属性 2个着色器
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    //获取链接程序错误，检测链接是否失败
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::PROGRAM_LINK_FAILED\n: %s", infoLog);
    }
    
    //使用激活这个程序
    glUseProgram(shaderProgram);
    
    //删除2个着色器分配的空间
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //到目前为止 已经把顶点数据发送给GPU了
    
    //告诉 openGL 如果解析数据  3个 vertex  队列解析
    //1, 从哪里开始， 2 总长度， 3，每次解析的数据类型 , 4 数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。
    
    //5. 步长步长(Stride),   6 偏移量 void 0 ， 偏移量(Offset)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    
    
    
    //0 copy 顶点数据 到缓冲中 提供 OpenGle 使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 1 设置顶点属性指针 调用进行的顶点缓冲对象与顶点属性链接。
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    // 启动顶点数据
    glEnableVertexAttribArray(0);
    
    // 2.渲染数据的时候 需要使用着色器
    glUseProgram(shaderProgram);
    // 3.绘制物体
//    someOpenGLFuncationThatDrawsOurTriangle();
    
    
    //使用 VAO 顶点数组对象(Vertex Array Object, VAO)
    GLuint VAO;
    //直接创建顶点数据缓存
    glGenVertexArrays(1, &VAO);
    
    //初始化代码只运行一次，除非物体改变的很平凡
    //绑定VAO
    glBindVertexArray(VAO);
    
    //2. 把顶点数据复制到 缓冲中供openGL 使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //3. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 *sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    
    //解绑
    glBindVertexArray(0);
    
    
    // 5 绘制物体
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    // 3.绘制物体
//    someOpenGLFuncationThatDrawsOurTriangle();
    //释放缓存
    glBindVertexArray(0);

}
