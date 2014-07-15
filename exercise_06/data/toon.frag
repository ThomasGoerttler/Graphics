#version 120
#define M_PI 3.1415926535897932384626433832795

// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2014 - Aufgabenblatt 6
//                     - Aufgabe 20 (Toon)
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: 768201
// Matr.-Nr: 766414
//
// ======================================

uniform vec4 light_pos;

varying vec3 N;

void main()
{
	float intensity;
    vec4 baseColor = vec4(0.8,0.0,0.0,1.0);
	vec4 color = baseColor;
	
	vec3 normN = normalize(N);
	
    vec3 ligthVector = vec3(light_pos[0] - N.x, light_pos[1] - N.y, light_pos[2] - N.z);
	intensity = 1 - acos(
        ((ligthVector[0] * normN.x) + (ligthVector[1] * normN.y) + (ligthVector[2] * normN.z))/
        (
            sqrt(pow(ligthVector[0],2) + pow(ligthVector[1],2) + pow(ligthVector[2],2)) *
            sqrt(pow(normN.x,2) + pow(normN.y,2) + pow(normN.z,2))
        )
    ) / M_PI;
	
	if (intensity < 0)
        intensity *= -1;
    
	if (intensity < 0.01)
		color = vec4(0.0, 0.0, 0.0, 1.0);
    
	else if (intensity <= 0.33)
		color = baseColor / 3.0;
    
	else if (intensity <= 0.66)
	  	color = baseColor * 2.0 / 3.0;
    
    else if (intensity <= 0.99)
    	color = baseColor;
    
    else 
		color = vec4(1.0, 1.0, 1.0, 1.0);

    
	gl_FragColor = color;
}