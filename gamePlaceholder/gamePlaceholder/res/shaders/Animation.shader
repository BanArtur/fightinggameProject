#shader vertex
#version 440 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP*position;
    v_TexCoord = texCoord;
};

#shader fragment
#version 440 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform float u_FrameOffset;

void main()
{
    vec2 realTexCoord = v_TexCoord;
    realTexCoord.x = realTexCoord.x+u_FrameOffset;
    vec4 texColor = texture(u_Texture, realTexCoord);
    color = texColor;
};