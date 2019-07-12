#shader vertex
#version 330 core

const int MAX_JOINTS = 50;
const int MAX_WEIGHTS = 3;

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_textureCoords;
layout (location = 2) in vec3 in_normal;
layout (location = 3) in ivec3 in_jointIndices;
layout (location = 4) in vec3 in_weights;

out vec2 pass_textureCoords;
out vec3 pass_normal;

uniform mat4 u_jointTransforms[MAX_JOINTS];
uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
    vec4 totalLocalPos = vec4(0.0);
    vec4 totalNormal = vec4(0.0);

    for(int i = 0; i < MAX_WEIGHTS; i++)
    {
        mat4 jointTransform = u_jointTransforms[in_jointIndices[i]];
        vec4 posePosition = jointTransform * vec4(in_position, 1.0f);
        totalLocalPos += posePosition * in_weights[i];

        vec4 worldNormal = jointTransform * vec4(in_normal, 0.0f);
        totalNormal += worldNormal * in_weights[i];
    }

    gl_Position = u_projection * u_view * totalLocalPos;
    pass_normal = totalNormal.xyz;
    pass_textureCoords = in_textureCoords;
}

#shader fragment
#version 330 core

const vec2 lightBias = vec2(0.7, 0.6);

layout(location = 0) out vec4 out_color;

in vec2 pass_textureCoords;
in vec3 pass_normal;

uniform sampler2D u_diffuseMap;
uniform vec3 u_lightDirection;

void main()
{
    vec4 diffuseColor = texture(u_diffuseMap, pass_textureCoords);
    vec3 unitNormal = normalize(pass_normal);
    float diffuseLight = max(dot(-u_lightDirection, unitNormal), 0.0) * lightBias.x + lightBias.y;
    out_color = diffuseColor * diffuseLight;
}