in vec3 vp;

uniform vec3 transform;

void main() {
	gl_Position = vec4(vp.x,vp.y,vp.z, 1.0);
};