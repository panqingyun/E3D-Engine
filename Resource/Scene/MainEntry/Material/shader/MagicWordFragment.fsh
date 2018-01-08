precision highp float;
varying lowp vec4 DestinationColor; // 1
varying lowp vec2 v_coord;
uniform sampler2D myTexture0;
uniform float blur;
uniform vec2 TextureSize;
const float GlowRange = 3.0;//发光范围
const float GlowExpand = 200.0; //发光强度

void main(void) { // 2
	
	if (blur < 0.5)
	{
		float samplerPre = 2.0;
		float radiusX = 1.0 / TextureSize.x;
		float radiusY = 1.0 / TextureSize.y;
		float glowAlpha = 0.0;
		float count = 0.0;
		for( float i = -GlowRange ; i <= GlowRange ; i += samplerPre )
		{
			for( float j = -GlowRange ; j <= GlowRange ; j += samplerPre )
			{
				vec2 samplerTexCoord = vec2( v_coord.x + j * radiusX , v_coord.y + i * radiusY );
				if( samplerTexCoord.x < 0.0 || samplerTexCoord.x > 1.0 || samplerTexCoord.y <0.0 || samplerTexCoord.y > 1.0 )
				{
					glowAlpha += 0.0;
				}
				else
				{
					vec4 color = texture2D(myTexture0, samplerTexCoord);
					glowAlpha += color.r * DestinationColor.a;
				}
				count += 1.0;
			}
		}
		glowAlpha /= (count + 500.0);
		float R = DestinationColor.r;
		float G = DestinationColor.g;
		float B = DestinationColor.b;
		float A = glowAlpha *GlowExpand;
		gl_FragColor = vec4( R ,G ,B ,A);
	}
	else
	{
		vec4 color = texture2D(myTexture0, v_coord);
		float alpha = color.r  * DestinationColor.a;
		gl_FragColor = vec4(color.rgb, alpha);
	}
}
