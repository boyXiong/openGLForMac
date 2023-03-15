#version 330 core

// 将 顶点数据 读取的内存数据 locaiotn 为0 的数据 读取到 postion 中 刚好 vec3 ，3个 float 值
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;


out vec3 ourColor;
out vec2 TexCoord;


uniform float texCoordPostion;

uniform mat4 transform;



uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    //着色器位置
    gl_Position =   vec4(position, 1.0f);
//    gl_Position = projection * view * model * vec4(position, 1.0f);
    //旋转
//    gl_Position = transform * vec4(position, 1.0f);

    ourColor = color;
//    //旋转图片 为正 纹理渲染坐标更改  1.0 - texCoord.y 让坐标对调旋转 翻转坐标
    TexCoord = vec2(texCoord.x, 1.0f - texCoord.y );
//    TexCoord = texCoord;
}
