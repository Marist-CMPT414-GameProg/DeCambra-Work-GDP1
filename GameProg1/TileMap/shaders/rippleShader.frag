#version 110

// attributes from vertShader.vert
varying vec4 vColor;
varying vec2 vTexCoord;

// uniforms
uniform sampler2D uTexture;
uniform float uTime;
uniform vec3 uTint;

void main() {
	float coef = sin(gl_FragCoord.y * 0.1 + 10.0 * uTime);
	
	vec2 fTexCoord = vTexCoord;
	fTexCoord.x +=  coef * 0.01;

	vec4 fColor = vColor;
	fColor.rgb *= coef * uTint;

	gl_FragColor = fColor * texture2D(uTexture, fTexCoord);
}