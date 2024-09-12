const char* V_SHADER_SOURCE = R"V0G0N(#version 310 es
precision mediump float;

uniform mat4 cameraTranslate;
uniform mat4 cameraRot;
uniform mat4 scaleTransform;

attribute vec4 a_Position;
attribute vec4 a_Color;

varying vec4 color;


void main()
{
  mat4 finTransform = cameraTranslate * cameraRot * scaleTransform;
  
  gl_Position = a_Position;
  color = a_Color;
}

})V0G0N";

const char* F_SHADER_SOURCE = R"V0G0N(#version 310 es
precision mediump float;

varying vec4 color;

void main() {

  gl_FragColor = color;
}

})V0G0N";


