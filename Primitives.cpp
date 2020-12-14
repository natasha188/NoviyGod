#include "Primitives.h"

static constexpr double Pi = acos(-1);

void acrt2cyl(
		double x, double y, double z,
		double &cr, double &cphi, double &cz)
{
	cr = hypot(x, y);
	cphi = atan2(y, x);	// вычисляет арктангенс по катетам
	cz = z;
}

void cyl2cart(
		double cr, double cphi, double cz,
		double &x, double &y, double &z)
{
	x = cr * cos(cphi);
	y = cr * sin(cphi);
	z = cz;
}

void cart2sph(
		double x, double y, double z,
		double &sr, double &sphi, double &stheta)
{
	sr = sqrt(x*x + y*y + z*z);
	sphi = atan2(y, x);
	stheta = atan2(hypot(x, y), z);
}

void sph2cart(
		double sr, double sphi, double stheta,
		double &x, double &y, double &z)
{
	x = sr * sin(stheta) * cos(sphi);
	y = sr * sin(stheta) * sin(sphi);
	z = sr * cos(stheta);
}

void make_cylinder_flat(int sides)
{
	for (int i = 0; i < sides; i++){
		double phi1 = double(i + 0.) / double(sides) * 2. * Pi;
		double phi2 = double(i + 1.) / double(sides) * 2. * Pi;

		double points[6][3];
		double normals[3][3];

		cyl2cart(0., 0., 0., points[0][0], points[0][1], points[0][2]);	//0 point
		cyl2cart(0., 0., 1., points[1][0], points[1][1], points[1][2]);	//1 point
		cyl2cart(1., phi2, 1., points[2][0], points[2][1], points[2][2]);	//2 point
		cyl2cart(1., phi1, 1., points[3][0], points[3][1], points[3][2]);	//3 point
		cyl2cart(1., phi1, 0., points[4][0], points[4][1], points[4][2]);	//4 point
		cyl2cart(1., phi2, 0., points[5][0], points[5][1], points[5][2]);	//5 point
		cyl2cart(0., 0., 1., normals[0][0], normals[0][1], normals[0][2]);	// 0 normal
		cyl2cart(0., 0., -1., normals[1][0], normals[1][1], normals[1][2]);	// 1 normal
		cyl2cart(1., (phi2+phi1)/2, 0., normals[2][0], normals[2][1], normals[2][2]);	// 2 normal

		glBegin(GL_TRIANGLES);

		glNormal3dv(normals[0]);
		glVertex3dv(points[1]);
		glVertex3dv(points[2]);
		glVertex3dv(points[3]);

		glNormal3dv(normals[1]);
		glVertex3dv(points[0]);
		glVertex3dv(points[4]);
		glVertex3dv(points[5]);

		glEnd();

		glBegin(GL_QUADS);

		glNormal3dv(normals[2]);
		glVertex3dv(points[3]);
		glVertex3dv(points[2]);
		glVertex3dv(points[5]);
		glVertex3dv(points[4]);

		glEnd();
	}
}

void make_cylinder_smooth(int sides)
{
	for (int i = 0; i < sides; i++){
		double phi1 = double(i + 0.) / double(sides) * 2. * Pi;
		double phi2 = double(i + 1.) / double(sides) * 2. * Pi;

		double points[6][3];
		double normals[4][3];

		cyl2cart(0., 0., 0., points[0][0], points[0][1], points[0][2]);	//0 point
		cyl2cart(0., 0., 1., points[1][0], points[1][1], points[1][2]);	//1 point
		cyl2cart(1., phi2, 1., points[2][0], points[2][1], points[2][2]);	//2 point
		cyl2cart(1., phi1, 1., points[3][0], points[3][1], points[3][2]);	//3 point
		cyl2cart(1., phi1, 0., points[4][0], points[4][1], points[4][2]);	//4 point
		cyl2cart(1., phi2, 0., points[5][0], points[5][1], points[5][2]);	//5 point

		cyl2cart(0., 0., 1., normals[0][0], normals[0][1], normals[0][2]);	// 0 normal
		cyl2cart(0., 0., -1., normals[1][0], normals[1][1], normals[1][2]);	// 1 normal
		cyl2cart(1., phi1, 0., normals[2][0], normals[2][1], normals[2][2]);	// 2 normal
		cyl2cart(1., phi2, 0., normals[3][0], normals[3][1], normals[3][2]);	// 3 normal

		glBegin(GL_TRIANGLES);

		glNormal3dv(normals[0]);
		glVertex3dv(points[1]);
		glVertex3dv(points[2]);
		glVertex3dv(points[3]);

		glNormal3dv(normals[1]);
		glVertex3dv(points[0]);
		glVertex3dv(points[4]);
		glVertex3dv(points[5]);

		glEnd();

		glBegin(GL_QUADS);

		glNormal3dv(normals[3]);
		glVertex3dv(points[2]);
		glVertex3dv(points[5]);
		glNormal3dv(normals[2]);
		glVertex3dv(points[4]);
		glVertex3dv(points[3]);

		glEnd();
	}
}

void make_cone_flat(int sides)
{
	for (int i = 0; i < sides; i++){
			double phi1 = double(i + 0.) / double(sides) * 2. * Pi;
			double phi2 = double(i + 1.) / double(sides) * 2. * Pi;

			double points[4][3];
			double normals[2][3];

			cyl2cart(0., 0., 0., points[0][0], points[0][1], points[0][2]);	//0 point
			cyl2cart(0., 0., 1., points[1][0], points[1][1], points[1][2]);	//1 point
			cyl2cart(1., phi1, 0., points[2][0], points[2][1], points[2][2]);	//2 point
			cyl2cart(1., phi2, 0., points[3][0], points[3][1], points[3][2]);	//3 point

			cyl2cart(0., 0., 1., normals[0][0], normals[0][1], normals[0][2]);	// 0 normal
			cyl2cart(1., (phi2+phi1)/2, 0., normals[1][0], normals[1][1], normals[1][2]);	// 1 normal

			glBegin(GL_TRIANGLES);

			glNormal3dv(normals[0]);
			glVertex3dv(points[0]);
			glVertex3dv(points[2]);
			glVertex3dv(points[3]);

			glNormal3dv(normals[1]);
			glVertex3dv(points[2]);
			glVertex3dv(points[1]);
			glVertex3dv(points[3]);

			glEnd();
	}
}

void make_cone_smooth(int sides)
{
	for (int i = 0; i < sides; i++){
			double phi1 = double(i + 0.) / double(sides) * 2. * Pi;
			double phi2 = double(i + 1.) / double(sides) * 2. * Pi;

			double points[4][3];
			double normals[2][3];

			cyl2cart(0., 0., 0., points[0][0], points[0][1], points[0][2]);	//0 point
			cyl2cart(0., 0., 1., points[1][0], points[1][1], points[1][2]);	//1 point
			cyl2cart(1., phi1, 0., points[2][0], points[2][1], points[2][2]);	//2 point
			cyl2cart(1., phi2, 0., points[3][0], points[3][1], points[3][2]);	//3 point

			cyl2cart(0., 0., 1., normals[0][0], normals[0][1], normals[0][2]);	// 0 normal
			cyl2cart(1., phi1, 0., normals[1][0], normals[1][1], normals[1][2]);	// 1 normal
			cyl2cart(1., phi2, 0., normals[2][0], normals[2][1], normals[2][2]);	// 2 normal

			glBegin(GL_TRIANGLES);

			glNormal3dv(normals[0]);
			glVertex3dv(points[0]);
			glVertex3dv(points[2]);
			glVertex3dv(points[3]);

			glNormal3dv(normals[1]);
			glVertex3dv(points[2]);
			glVertex3dv(points[1]);
			glNormal3dv(normals[2]);
			glVertex3dv(points[3]);

			glEnd();
	}
}

void make_sphere_flat(int rows, int cols)
{
	for (int i = 0; i < cols; i++){
		double phi1 = double(i + 0.) / double(cols) * 2. * Pi;
		double phi2 = double(i + 1.) / double(cols) * 2. * Pi;
		for (int j = 0; j < rows; j++){
			double theta1 = double(j + 0.) / double(rows) * Pi;
			double theta2 = double(j + 1.) / double(rows) * Pi;

			double points[4][3];
			double normals[1][3];

			sph2cart(1., phi2, theta2, points[0][0], points[0][1], points[0][2]);	//0 point
			sph2cart(1., phi1, theta2, points[1][0], points[1][1], points[1][2]);	//1 point
			sph2cart(1., phi1, theta1, points[2][0], points[2][1], points[2][2]);	//2 point
			sph2cart(1., phi2, theta1, points[3][0], points[3][1], points[3][2]);	//3 point

			sph2cart(1., (phi1+phi2)/2, (theta1+theta2)/2, normals[0][0], normals[0][1], normals[0][2]);	// 0 normal

			glBegin(GL_QUADS);

			glNormal3dv(normals[0]);
			glVertex3dv(&points[0][0]);
			glVertex3dv(&points[1][0]);
			glVertex3dv(&points[2][0]);
			glVertex3dv(&points[3][0]);

			glEnd();
		}
	}
}

void make_sphere_smooth(int rows, int cols)
{
	for (int i = 0; i < cols; i++){
			double phi1 = double(i + 0.) / double(cols) * 2. * Pi;
			double phi2 = double(i + 1.) / double(cols) * 2. * Pi;
			for (int j = 0; j < rows; j++){
				double theta1 = double(j + 0.) / double(rows) * Pi;
				double theta2 = double(j + 1.) / double(rows) * Pi;

				double points[4][3];
				double normals[4][3];

				sph2cart(1., phi2, theta2, points[0][0], points[0][1], points[0][2]);	//0 point
				sph2cart(1., phi1, theta2, points[1][0], points[1][1], points[1][2]);	//1 point
				sph2cart(1., phi1, theta1, points[2][0], points[2][1], points[2][2]);	//2 point
				sph2cart(1., phi2, theta1, points[3][0], points[3][1], points[3][2]);	//3 point

				sph2cart(1., phi1, theta1, normals[0][0], normals[0][1], normals[0][2]);	// 0 normal
				sph2cart(1., phi2, theta2, normals[1][0], normals[1][1], normals[1][2]);	// 1 normal
				sph2cart(1., phi1, theta2, normals[2][0], normals[2][1], normals[2][2]);	// 2 normal
				sph2cart(1., phi2, theta1, normals[3][0], normals[3][1], normals[3][2]);	// 3 normal

				glBegin(GL_QUADS);

				glNormal3dv(normals[1]);
				glVertex3dv(&points[0][0]);
				glNormal3dv(normals[2]);
				glVertex3dv(&points[1][0]);
				glNormal3dv(normals[0]);
				glVertex3dv(&points[2][0]);
				glNormal3dv(normals[3]);
				glVertex3dv(&points[3][0]);

				glEnd();
			}
		}
}

void make_icosphere_flat(int rows, int cols)
{
}
void make_icosphere_smooth(int rows, int cols)
{
}




