#version 150

in vec3 pass_Normal;
in vec3 pass_FragPos;	// fragment position _ ass3
in vec3 pass_eyePos;	// eye (camera) position _ ass3
in vec2 pass_TexCoord;  // texture coordinates _ ass4

out vec4 out_Color;

// uniform values _ ass3
uniform vec3 lightSrc;
uniform int modeswitch; // blinn-phong if 1, cel-shading if 2

uniform sampler2D ColorTex; // sampler variable _ ass4

// cel-shading level
const int shadeLevel = 3;
float outline = 1.0;

void main() {

  // use the sampled texture as a diffuse color _ ass4
  vec4 color = texture(ColorTex, pass_TexCoord);
  vec3 diffuseColor = color.rgb;

  // values for shading
  vec3 ambientColor = diffuseColor;
  vec3 specularColor = vec3(1.0, 1.0, 1.0); // white
  float shininess = 24.0;

  // Adjusting and normalizing values before calculating angles
  vec3 normal = normalize(pass_Normal);
  vec3 light = normalize(lightSrc - pass_FragPos);
  vec3 eye = normalize(pass_eyePos - pass_FragPos); 
  vec3 halfway = normalize(eye + light);

  // Cosine values of each angle
  float diffuseAngle = max(0.0, dot(light, normal));
  float specularAngle = pow(max(0.0, dot(normal, halfway)), shininess);
  
  // cel-shading
  if(modeswitch == 2){
    // diffuseAngle is discretized to determine the intensity of color
    diffuseAngle = floor(diffuseAngle * shadeLevel) / shadeLevel;
    
    // also discretize specular light
    if(specularAngle < 0.5)
      specularAngle = 0.0;

    // outline
    if(dot(normal, eye) < 0.25)
      outline = 0.0;
  }

  // final terms
  vec3 ambient = ambientColor;
  vec3 diffuse = diffuseColor * diffuseAngle;
  vec3 specular = specularColor * specularAngle;

  // final result
  vec3 finalColor = outline * (ambient + diffuse + specular);
  out_Color = vec4(finalColor, 1.0);
}
