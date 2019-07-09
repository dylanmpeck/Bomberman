#shader vertex
#version 330 core

layout (location = 0) in vec4 vertex;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(vertex.xy, 0.0f, 1.0f);
    v_TexCoord = vertex.zw;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform sampler2D u_Texture2;

void main()
{
    vec4 texColor = mix(texture(u_Texture, v_TexCoord), texture(u_Texture2, v_TexCoord), 0.2);
	FragColor = texColor;
}