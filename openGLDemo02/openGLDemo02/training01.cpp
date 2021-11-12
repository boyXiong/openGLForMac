//
//  training01.cpp
//  openGLDemo02
//
//  Created by key on 2021/10/28.
//

#include "training01.hpp"

#include <stdio.h>
#include <iostream>

/*
 。GLSL定义了in和out关键字专门来实现这个目的。每个着色器使用这两个关键字设定输入和输出，只要一个输出变量与下一个着色器阶段的输入匹配，它就会传递下去。但在顶点和片段着色器中会有点不同。
 */
const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"    //位置变量的属性位置为 0
    "layout (location = 2) in vec3 color;\n"       //颜色变量的属性位置为 2 主要是用来绑定数据的
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position, 1.0);\n"
    "ourColor = color;\n"
    "}\0";

//偏单着色器源码
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "in vec3 ourColor;\n"  //将上面位置定的 vec3 color 作为输入， 这样 2个着色器 就可以相链， 输入 与 输出
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(ourColor, 1.0f);\n"
    "}\n\0";

//    "color = vec4(7.0f, 0.1f, 0.9f, 1.0f);\n"
//      "uniform vec4 ourColor;\n"


int  windowInit() {
   
    
    return 0;
}


//通用着色器与绑定
void shaderInit(GLuint * shaderProgram) {
    
    //顶点着色器
    GLuint vertexShader;
    //创建顶点数据类型 着色器
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //解析这色器类型
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //进行编译
    glCompileShader(vertexShader);
    
    //查看编译情况
    GLint success;
    GLchar infLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        glGetShaderInfoLog(vertexShader, GL_COMPILE_STATUS, NULL, infLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n: %s", infLog);
    }
    
    
    //片段着色器
    GLint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    
    //3 将2个 着色器 进行链接在一起
//    GLuint shaderProgram;
//    *shaderProgram = glCreateProgram();
    //给 program 增加属性 2个着色器
    glAttachShader( *shaderProgram, vertexShader);
    glAttachShader( *shaderProgram, fragmentShader);
    glLinkProgram( *shaderProgram);
    
    //获取链接程序错误，检测链接是否失败
    glGetProgramiv( *shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog( *shaderProgram, 512, NULL, infLog);
        printf("ERROR::SHADER::VERTEX::PROGRAM_LINK_FAILED\n: %s", infLog);
    }
    
    //使用激活这个程序
    glUseProgram( *shaderProgram);
    
    //删除2个着色器分配的空间
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    
    
    
}


int train1() {
    
    //Window 初始化
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
    
    
    
    //创建顶点数据
    GLfloat vertices[] = {
        //顶点位置 0        //颜色
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        0.5f,  -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f,   0.5f, 0.0f,   0.0f, 0.0f, 1.0f
    };
    
    //创建顶点对象
    GLuint VBO;
    glGenBuffers(1, &VBO);
    //绑定到顶点空间
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //给顶点空间拷贝数据 拷贝的数据位置
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    
    
    //获取着色器 相关的
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    shaderInit(&shaderProgram);
    
    
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
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    
    //3. 设置顶点属性指针  位置 0 的
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 *sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    
    
    //解绑
    glBindVertexArray(0);
    
    
    //游戏循环(Game Loop) 窗口可以一直接受事件 进行处理
    while(!glfwWindowShouldClose(window))
    {
       
        
        //检查事件 有事件 就进行处理
        glfwPollEvents();

        //渲染 清空颜色缓存
        //清空色值 状态设置函数
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 状态应用函数
        glClear(GL_COLOR_BUFFER_BIT);
        //函数会交换颜色缓冲  存储 GLFW窗口每一个像素颜色的大缓冲
        
        //激活着色器
        glUseProgram(shaderProgram);
        
        //更新uniform 颜色
        //获取时间
        GLfloat timeValue = glfwGetTime();
        // 时间
        // 通过sin 将数据在 0.0 到 1.0 直接
        GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
        //因为 ourColor  在着色器中定义的是 全局变量定义的 uniform，所以可以在这里 通过这个方法拿到
        GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        //通过这个 设置 向量参数 f 是 float 4f 就是 4个 float 参数，第一个是 位置坐标， 后面是颜色值
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        
        
        //
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
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

void train2() {
    
    
}

void train3() {
    
    
}
