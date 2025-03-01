#version 330 core

// ES requires setting precision qualifier
// Can be mediump or highp
precision highp float; // affects all floats (vec3, vec4 etc)

#ifdef VULKAN
//input form the vertex shader
layout(location = 0) out vec4 vFragColor;	//fragment shader output

layout(binding=0) uniform sampler2D textureSampler;
#else
out vec4 vFragColor;	//fragment shader output

smooth in vec4 vSmoothColor;		//interpolated colour to fragment shader
smooth in vec2 vSmoothTexcoord;
uniform sampler2D textureSampler;
uniform bool uEnableTexture;
#endif

void main()
{
    vec4 final = vec4(0.0, 1.0, 0.0, 1.0);
#ifndef VULKAN
    if (uEnableTexture)
    {
        final.x = vSmoothTexcoord.x;
        final.y = vSmoothTexcoord.y;
        final = texture(textureSampler, vSmoothTexcoord);
    } else {
        //set the interpolated colour as the shader output
        final = vSmoothColor;
    }
#endif
    vFragColor = final;
}

