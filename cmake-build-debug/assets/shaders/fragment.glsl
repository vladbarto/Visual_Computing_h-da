#version 330 core

in vec3 colorVS;

//fragment shader output
out vec4 color;
uniform float animation;

void main(){
    //color = vec4(colorVS.x, colorVS.y, colorVS.z, 1.0);
    color = vec4(colorVS.x*animation, colorVS.y-animation, colorVS.z-animation, 1.0);
}

