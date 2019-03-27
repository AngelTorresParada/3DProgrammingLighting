uniform mat4 MVP;

attribute vec3 vpos;
attribute vec2 vtex;
attribute vec4 vcolor;
attribute vec3 vnormal;

varying vec2 ftex;
varying vec4 fcolor;
varying vec3 fnormal;
varying vec3 fpos;

void main() {
	gl_Position = MVP * vec4(vpos, 1);
	ftex = vtex;
	fcolor = vcolor;
	fnormal = vnormal;
	fpos = vpos;

}