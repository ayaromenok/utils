#define IMGFORMAT rgba8
layout(binding = 0, IMGFORMAT) uniform readonly highp image2D inputImage;
layout(binding = 1, IMGFORMAT) uniform readonly highp image2D outputImage;

void main(){
    ivec2 imgSize = imageSize(outputImage);
    int x = int(gl_GlobalInvocationID.x);
    int y = int(gl_GlobalInvocationID.y);
    if (( x >= imgSize.x) || (y >= imgSize.y))
        return;

    vec4 imgValue = imageLoad(inputImage,ivec2(x,y))*0.5;
    imageStore(resultImage, ivec2(x,y), imgValue);
}
