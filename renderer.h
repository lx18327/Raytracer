#ifndef RENDERERH
#define RENDERERH 

#include "vec3.h"
#include "ray.h";
#include "hit_table.h"
#include "material.h"


///////////////////////////////
// Render Constant Renderer
///////////////////////////////
vec3 render_constant_raytracer(const ray& r, hit_table *world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * render_constant_raytracer(scattered, world, depth + 1);
	}
	return vec3(0, 0, 0);
}

vec3 render_constant(const ray& r, hit_table *world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation + render_constant_raytracer(scattered, world, depth + 1);
	}
	return vec3(0, 0, 0);
}


#endif