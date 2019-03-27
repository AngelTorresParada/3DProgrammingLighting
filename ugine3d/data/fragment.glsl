uniform sampler2D texSampler;
uniform int usetexture;

varying vec2 ftex;
varying vec4 fcolor;
varying vec3 fnormal;
varying vec3 fpos;

uniform int numlights;
uniform vec4 lightpos[8];
uniform vec4 lightcolor[8];
uniform float specularatt;
uniform float constatt;
uniform float linearatt[8];
uniform float quadratt;
uniform vec3 ambient;
uniform float shininess;
uniform vec4 diffusecolor;

void main() {
	vec3 diffuse = vec3(0.0);
	vec3 specular = vec3(0.0);

	if ((ambient.x != 0.0) || (ambient.y != 0.0) || (ambient.z != 0.0)) {
		diffuse = ambient;
	}
	else {
		diffuse = vec3(1.0, 1.0, 1.0);
	}

	if ((diffusecolor.x == 0.0) && (diffusecolor.y == 0.0) || (diffusecolor.z == 0.0)) {
		diffusecolor = vec4(1.0, 1.0, 1.0, 1.0);
	}

	vec3 N = normalize(fnormal);
	for (int i = 0; i < numlights; i++) {
		vec3 L = vec3(lightpos[i].x, lightpos[i].y, lightpos[i].z);
		float att = 1.0;
		if (lightpos[i].w == 1.0) {
			L = L - fpos;
			att = 1.0 / (constatt + linearatt[i] * length(L) + quadratt * length(L) * length(L));
		}

		L = normalize(L);
		float NdotL = dot(N,L);
		if (NdotL < 0.0) {
			NdotL = 0.0;
		}

		diffuse += NdotL * lightcolor[i].xyz * att;

		if (NdotL > 0.0 && shininess > 0.0) {
			vec3 H = normalize(L - fpos);
			float NdotH = dot(N,H);
			if (NdotH < 0.0) {
				NdotH = 0.0;
			}
			specular += pow(NdotH, float(shininess)) * att;
		}
	}
		
	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	if (usetexture == 1) {
		gl_FragColor *= texture2D(texSampler, ftex);
	}

	gl_FragColor *= vec4(fcolor) * diffusecolor * vec4(diffuse, 1.0) + vec4(specular, 0.0);
}
