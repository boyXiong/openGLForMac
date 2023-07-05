#version 330 core
in vec2 TexCoord;
in float IsOpenMirror;
out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform sampler2D openMirrorTexture3;

void main()
{
    
    if (IsOpenMirror > 0) {
        //显示开镜纹理
        color = texture(openMirrorTexture3, TexCoord, 0.5);
    }else {
        color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.5);

    }
    
}


