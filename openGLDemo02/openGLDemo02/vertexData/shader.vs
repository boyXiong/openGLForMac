#version 330 core
layout (location = 0) in vec3 position;   //位置变量的属性位置为 0
layout (location = 2) in vec3 color;       //颜色变量的属性位置为 2 主要是用来绑定数据的
out vec3 ourColor;
void main()
{
    gl_Position = vec4(position, 1.0);
//    ourColor = color;
}
