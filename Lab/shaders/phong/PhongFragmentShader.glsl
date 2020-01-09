#version 330 core
out vec4 color;

in vec3 fragNormal;
in vec3 fragPos;
in vec3 fragColor;

uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;

uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
    vec3 norm = normalize(fragNormal);

    vec3 lightDir = normalize(lightPos - fragPos);
    float diffuse = max(dot(norm, lightDir), 0.0) * diffuseStrength;

    vec3 viewDir = normalize(camPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32) * specularStrength;

    vec3 result = fragColor * (ambientStrength + diffuse + spec);
    color = vec4(result, 1.0f);
}