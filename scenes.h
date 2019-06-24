#ifndef SCENESH
#define SCENESH 

class hit_table;

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "hit_table.h"
#include "float.h"
#include "camera.h"
#include "material.h"
#include "tools.h"
#include "renderer.h"
#include "shapes.h"

using namespace std;

void cornell_box_constant_render_scene(int width, int height, int samples, string fileName)
{
	cout << "Rendering Starts" << endl;

	/* Scene Hit Information */
	hit_table **list = new hit_table*[8];
	int i = 0;

	/* Colors for probs */
	material *torqoise = new constant(vec3(0.14, 0.74, 0.74)); // roof
	material *majanta = new constant(vec3(0.74, 0.14, 0.74));  // left wall
	material *yellow = new constant(vec3(0.74, 0.74, 0.14));   // right wall
	material *green = new constant(vec3(0.14, 0.74, 0.14));    // floor
	material *red = new constant(vec3(0.74, 0.14, 0.14));      // short block
	material *blue = new constant(vec3(0.14, 0.14, 0.74));     // long block
	material *gray = new constant(vec3(0.74, 0.74, 0.74));     // front wall
	material *white = new constant(vec3(1.0, 1.0, 1.0));       // light Color

	/* Surface Informations */
	list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, majanta));
	list[i++] = new yz_rect(0, 555, 0, 555, 0, yellow);
	list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, torqoise));
	list[i++] = new xz_rect(0, 555, 0, 555, 0, green);
	list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, gray));
	list[i++] = new translate(new rotate_y(new box(vec3(0, 0, 0), vec3(165, 165, 165), red), 70), vec3(80, 0, 225));
	list[i++] = new translate(new rotate_y(new box(vec3(0, 0, 0), vec3(165, 330, 165), blue), 15), vec3(265, 0, 295));

	// World Information
	hit_table *world = new hit_table_list(list, i);

	// Camera Information
	vec3 lookfrom(278, 278, -800);
	vec3 lookat(278, 278, 0);
	float dist_to_focus = 10.0;
	float aperture = 0.0;
	float vfov = 40.0;

	camera cam(lookfrom, lookat, vec3(0, 1, 0), vfov, float(width) / float(height), aperture, dist_to_focus, 0.0, 1.0);

	// Image Information Start
	ofstream outputImage;
	outputImage.open(fileName+".ppm");
	std::cout << "P3\n" << width << " " << height << "\n255\n";
	outputImage << "P3\n" << width << " " << height << "\n255\n";

	for (int j = height - 1; j >= 0; j--) {
		for (int i = 0; i < width; i++) {
			vec3 col(0, 0, 0);
			for (int s = 0; s < samples; s++) {
				float u = float(i + float(rand()) / RAND_MAX) / float(width);
				float v = float(j + float(rand()) / RAND_MAX) / float(height);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += render_constant(r, world, 0);
			}
			col /= float(samples);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			cout << "Rendering ... " << ir << " " << ig << " " << ib << "\n";
			outputImage << ir << " " << ig << " " << ib << "\n";
		}
	}
	outputImage.close();
	system("cls");
	cout << "Rendering Completed.\n\n" << endl;
	return;
}

#endif