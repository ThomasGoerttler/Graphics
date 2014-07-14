#version 120

// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2014 - Aufgabenblatt 6
//                     - Aufgabe 20 (Phong)
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: xxxxx
// Matr.-Nr: xxxxx
//
// ======================================

uniform vec4 light_pos;
uniform vec4 light_iAmbient;
uniform vec4 light_iDiffuse;
uniform vec4 light_iSpecular;

uniform vec4 material_ambient;
uniform vec4 material_diffuse;
uniform vec4 material_specular;
uniform vec4 material_emission;
uniform float material_shininess;

varying vec3 N;
varying vec3 v;

void main (void)
{
    vec4 resultColor = vec4(0.0,0.0,0.0,1.0);
	vec3 normN = normalize(N);
	vec3 normL = normalize(vec3(light_pos.x - N.x, light_pos.y - N.y, light_pos.z - N.z));
	float scalarProduct = normL.x * normN.x + normL.y * normN.y + normL.z * normN.z;
	vec3 R = vec3(2 * normN[0] * scalarProduct - normL[0], 2 * normN[1] * scalarProduct - normL[1], 2 * normN[2] * scalarProduct - normL[2]);
	for(int i = 0; i <= 3; i++)
		resultColor[i] = light_iAmbient[i] * material_ambient[i] + light_iDiffuse[i] * material_diffuse[i] * scalarProduct + light_iSpecular[i] * material_specular[i] * pow(normalize(R.x * v.x + R.y * v.y + R.z * v.z), material_shininess);
	gl_FragColor = clamp(resultColor,0.0,1.0);
}
