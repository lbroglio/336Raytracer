const char* V_SHADER_SOURCE = R"V0G0N(#version 300 es
precision mediump float;

uniform mat4 cameraTranslate;
uniform mat4 cameraRot;
uniform mat4 scaleTransform;

in vec4 a_Position;
in vec4 a_Color;

out vec4 color;


void main()
{
  mat4 finTransform = cameraTranslate * cameraRot * scaleTransform;
  
  gl_Position = a_Position;
  color = a_Color;
}

)V0G0N";

const char* F_SHADER_SOURCE = R"V0G0N(#version 300 es
precision mediump float;

in vec4 color;
out vec4 fragColor;

void main() {

  fragColor = color;
}

)V0G0N";


