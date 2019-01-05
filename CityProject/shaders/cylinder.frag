#version 300 es
#undef lowp
#undef mediump
#undef highp

precision mediump float;

out vec4 color;

void main(){
  color = vec4( 0.5 , 0.5 , 0.5 , 1.0 );
}
