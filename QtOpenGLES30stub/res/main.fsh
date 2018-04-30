in highp vec3 ioN;
in highp vec2 ioTc0;
out highp vec4 fragColor;
uniform sampler2D sampler;

void main(void)
{
    //fragColor = vec4(ioTc0.s, ioTc0.t, ioN.z, 1.0);
    fragColor = texture(sampler,ioTc0);
}
