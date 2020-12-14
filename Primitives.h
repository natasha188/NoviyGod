#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

void acrt2cyl(
		double x, double y, double z,
		double &cr, double &cphi, double &cz);
// из декартовой в цидиндрическую систему
void cyl2cart(
		double cr, double cphi, double cz,
		double &x, double &y, double &z);	// наоборот

// перевод из декартовой в сферическую
void cart2sph(
		double x, double, double z,
		double &sr, double &sphi, double &stheta);
// из сферической в декартовую
void sph2cart(
		double sr, double sphi, double stheta,
		double &x, double &y, double &z);

void make_cylinder_flat(int sides);	// этоп ризма
void make_cylinder_smooth(int sides);
void make_cone_flat(int sides);	// это пирамида
void make_cone_smooth(int sides);
void make_sphere_flat(int rows, int cols);	// сфера на основе глобуса
void make_sphere_smooth(int rows, int cols);
void make_icosphere_flat(int rows, int cols);	// сфера на основе икосаэдра
void make_icosphere_smooth(int rows, int cols);

#endif /* PRIMITIVES_H_ */
