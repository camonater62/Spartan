#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;

out vec4 v_Normal;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * position;
    v_Normal = normal;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Normal;

void main() {
    color.r = abs(v_Normal.r);
    color.g = abs(v_Normal.g);
    color.b = abs(v_Normal.b);
    color.a = 1.0;
}