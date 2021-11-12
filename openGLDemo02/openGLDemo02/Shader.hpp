//
//  Shader.hpp
//  openGLDemo02
//
//  Created by key on 2021/10/29.
//

#ifndef Shader_hpp
#define Shader_hpp
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader {
public:
    //程序ID
    GLuint Program;
    // 构造器就是初始化的
    Shader(const GLchar * vertexPath, const GLchar * fragmentPath);
    //使用程序
    void Use();
};



#endif /* Shader_hpp */
