//Código fonte do Fragment Shader (em GLSL)
#version 440

//Informações recebidas do vertex shader
in vec3 finalColor;
in vec3 scaledNormal;
in vec3 fragPos;

//Propriedades do material do objeto
uniform float ka;
uniform float kd;
uniform float ks;
uniform float q;

//Propriedades da fonte de luz
uniform vec3 lightPos;
uniform vec3 lightColor;

//Posição da câmera 
uniform vec3 cameraPos;

uniform vec3 selectedColor;
uniform bool isSelected;

//Buffer de saída (color buffer)
out vec4 color;

void main()
{
    // Ambient
    vec3 ambient =  lightColor * ka;
    // Diffuse 
    vec3 N = normalize(scaledNormal);
    vec3 L = normalize(lightPos - fragPos);
    float diff = max(dot(N, L),0.0);
    vec3 diffuse = diff * lightColor * kd;
    
    // Specular
    vec3 R = reflect(-L,N);
    vec3 V = normalize(cameraPos - fragPos);
    float spec = pow(max(dot(R,V),0.0),q);
    vec3 specular = spec * ks * lightColor;
        
    vec3 result;

    if (isSelected)
    {
        result = (ambient + diffuse) * selectedColor + specular;
    }
    else
    {
        result = (ambient + diffuse) * finalColor + specular;
    }

    color = vec4(result, 1.0f);
}
