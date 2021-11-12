#version 330 core
in vec3 ourColor;  //将上面位置定的 vec3 color 作为输入， 这样 2个着色器 就可以相链， 输入 与 输出
out vec4 color;
void main()
{
    color = vec4(0.7f,0.2f, 0.9f, 1.0f);
//    color = vec4(ourColor, 1.0f);
}
