in vec3 vp;

uniform vec3 transform;

void main() {
	gl_Position = vec4(vp, 1.0);
};