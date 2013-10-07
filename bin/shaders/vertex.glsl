#version 400

uniform float opacity;
uniform mat3  normalMatrix;
uniform mat4  modelviewMatrix;
uniform mat4  projectionMatrix;
uniform float time;
uniform vec3  vertexNormal;
uniform vec3  vertexPosition;
in vec4  vertexColor;
in float vertexMass;
in int   vertexType;

/*out vec3  vertexNormalToGeo;
out vec4  vertexColorToGeo;
out int   vertexTypeToGeo;
out float vertexMassToGeo;
out vec3  vertexPositionToGeo;*/
out vec4 oColor;

void main(void) {
  
  //vertexMassToGeo     = vertexMass;
  //vertexPositionToGeo = vertexPosition;
  //vertexTypeToGeo     = vertexType;
  //vertexColorToGeo    = vec4(1.0, 1.0, 1.0, 1.0);
  //vertexNormalToGeo   = vertexNormal;
  gl_Position           = projectionMatrix * modelviewMatrix * vec4(vertexPosition,1.0);
  oColor                = vec4(1.0, 1.0, 1.0, 0.03);
}
