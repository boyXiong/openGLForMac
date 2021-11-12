//
//  training01.hpp
//  openGLDemo02
//
//  Created by key on 2021/10/28.
//

#ifndef training01_hpp
#define training01_hpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>




//顶点着色器源码  一般使用常量
extern const GLchar* vertexShaderSource;

//偏单着色器源码
extern const GLchar* fragmentShaderSource;



#endif /* training01_hpp */



// 训练

/*
 1.添加更多顶点到数据中，使用glDrawArrays，尝试绘制两个彼此相连的三角形：参考解答
 2.创建相同的两个三角形，但对它们的数据使用不同的VAO和VBO：参考解答
 3..创建两个着色器程序，第二个程序使用与第一个不同的片段着色器，输出黄色；再次绘制这两个三角形，其中一个输出为黄色：参考解答
 */

int train1();
void train2();
void train3();

