precision highp float;
varying lowp vec4 DestinationColor; // 1
varying lowp vec2 v_coord;
uniform sampler2D myTexture0;

void main(void)
{ // 2
    vec4 color = texture2D(myTexture0, v_coord);

    gl_FragColor = color*DestinationColor;
    
}
