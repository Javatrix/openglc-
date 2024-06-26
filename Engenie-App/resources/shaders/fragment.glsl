#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 FragNormal;

struct Material {
    float specularity;
    float shininess;
};

uniform mat4 model;

uniform Material material;
uniform sampler2D texture0;
uniform float ambientStrength;
uniform vec3 diffuseDir;
uniform vec4 diffuseColor;
uniform vec3 viewPos;

void main() {
    vec3 normal = normalize((model * vec4(FragNormal, 1)).xyz);
    vec4 ambientLight = vec4(ambientStrength, ambientStrength, ambientStrength, 1);
    vec4 diffuseLight = diffuseColor * max(0, -dot(normalize(diffuseDir), normal));
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectionDir = reflect(normalize(diffuseDir), normal);
    vec4 specularLight = vec4(material.specularity * pow(max(0, dot(viewDir, reflectionDir)), material.shininess));
    FragColor = texture(texture0, TexCoord) * (ambientLight + diffuseLight + specularLight);
}
