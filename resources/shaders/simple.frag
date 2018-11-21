#version 150

in  vec3 pass_Normal;

//ass 3
in vec3 pass_VertexViewPosition;
in vec3 pass_LightSourceViewPosition;
in vec3 pass_DiffuseColor;
in float pass_ShaderMode;

out vec4 out_Color;

// Constans for Ambient, Diffuse, Specular, specularIntensity and gloss
float ambientK = 0.5;
float diffuseK = 0.8;
float specularK = 1.0;															  //Ks
float glossiness = 2.0;
float specularIntensity = 0.0;

vec3 specColor = vec3(1.0, 1.0, 1.0);                                             //Is

// For ToonShading
vec3 coloredOutline = vec3(0.608, 0.259, 0.745);

void main() 
{
  // First normalize the normal vector
  vec3 normal = normalize(pass_Normal);
  // Then normalize the direction of light (origin - position of vertex)
  vec3 viewDir = normalize(pass_LightSourceViewPosition - pass_VertexViewPosition);
  
  // Calculate ambient light by multiplying the constant with DiffuseColor
  vec3 ambient = ambientK * pass_DiffuseColor;
  
  // Use Lambert's law to get the Diffuse reflection
  float lambertian = max(dot(viewDir, normal), 0.0);
  vec3 diffuse = lambertian * pass_DiffuseColor * diffuseK;
  
  // Normalize the negative position of vertex
  viewDir = normalize(-pass_VertexViewPosition);
  
  if (lambertian > 0.0)
  {
	  vec3 halfwayVector = normalize(viewDir + viewDir);
	  float specAngle = max(dot(halfwayVector, normal), 0.0);
	  specularIntensity = pow(specAngle, glossiness);
  }
  
  vec3 specular = specularK * specColor * specularIntensity;
  
  // Convert the ambient, diffuse and specular in to a vec4
  out_Color = vec4(ambient + diffuse + specular, 1.0);
  
  if (pass_ShaderMode == 2.0)
  {
		//calculate the view angle cosine
        float viewAngleCosine = dot(normal, viewDir);

		// Only color the outline of planets if viewAngleCosine is less than 0.3
        if (viewAngleCosine < 0.3) 
		{
            out_Color = vec4(coloredOutline, 1.0);
        }
		else
		{
            out_Color = ceil(out_Color * 4) / 4;
        } 
  }
}
