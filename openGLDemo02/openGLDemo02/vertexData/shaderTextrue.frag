#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float ourTexture1AndOurTexture2Per;

void main()
{
    //混合颜色
    //可以把得到的纹理颜色与顶点颜色混合，来获得更有趣的效果。我们只需把纹理颜色与顶点颜色在片段着色器中相乘来混合二者的颜色
//    color = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0f);
    
    //得到线性色彩值  第一个 纹理 与第二个纹理， 第三个值 就等于  第一个纹理 与 第二个纹理， 占据的比例，如果是1.0就是全部第二个， 0.0就是全部第一个， 0.2 就是， 80% 第一个， 20% 第二个
    color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), ourTexture1AndOurTexture2Per);

    
//    color = texture(ourTexture, TexCoord);
}
