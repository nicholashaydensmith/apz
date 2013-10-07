#version 400

uniform float opacity;
uniform mat3  normalMatrix;
uniform mat4  modelviewMatrix;
uniform mat4  projectionMatrix;
uniform vec3  eyePosition;
uniform float time;

in vec3  vertexPositionToGeo[];
in float vertexMassToGeo[];
in vec3  vertexNormalToGeo[];
in vec4  vertexColorToGeo[];
in int   vertexTypeToGeo[];


layout (points) in;
layout (points, max_vertices = 1) out;

out vec4 oColor;


void main() {
  mat4 MVP = projectionMatrix * modelviewMatrix;


  for(int i = 0; i < gl_in.length(); i++){
    gl_Position = MVP * vec4(vertexPositionToGeo[i], 1.0);
    oColor      = vertexColorToGeo[i];
    EmitVertex();
    EndPrimitive();
  }
}