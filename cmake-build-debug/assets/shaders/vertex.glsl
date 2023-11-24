#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colorRGB;

out vec3 colorVS;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    colorVS = colorRGB;
    gl_Position = projection * view * model * vec4(pos, 1.0);
    //gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);

}
