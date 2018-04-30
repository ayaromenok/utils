layout(location = 0) in vec4 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tc0;

out highp vec3 ioN;
out highp vec2 ioTc0;

uniform mat4 mtxProj;
uniform mat4 mtxWorld;
uniform mat4 mtxCam;
uniform mat4 mtxMy;

void main(void)
{
    ioN = normal;
    ioTc0 = tc0;
    gl_Position = mtxProj * mtxCam * mtxMy * mtxWorld * vertex;
}
