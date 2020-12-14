#include <cmath>
#include "GLDemoWindow.h"
#include "Primitives.h"
static constexpr double Pi = acos(-1.);

static VertexVector s_house_vertices {
	{  2.0, 1.0, 0.0 },
	{  2.0, 1.0, 2.0 },
	{  2.0, 0.0, 3.0 },
	{  2.0, -1.0, 2.0 },
	{  2.0, -1.0, 0.0 },
	{  -2.0, 1.0, 2.0 },
	{  -2.0, 1.0, 0.0 },
	{  -2.0, 0.0, 3.0 },
	{  -2.0, -1.0, 2.0 },
	{  -2.0, -1.0, 0.0 },
};

static FaceVector s_house_faces {
	{ 5, 4, 3, 2, 1, 0 },
	{ 5, 9, 8, 7, 5, 6 },
	{ 4, 0, 1, 5, 6 },
	{ 4, 4, 3, 8, 9 },
	{ 4, 1, 2, 7, 5 },
	{ 4, 3, 2, 7, 8 }
};

static NormalVector s_house_normals {
	{  1.0, 0.0, 0.0 },
	{  -1.0, 0.0, 0.0 },
	{  0.0, 1.0, 0.0 },
	{  0.0, -1.0, 0.0 },
	{  0.0, 1.0, 0.5 },
	{  0.0, -1.0, 0.5 },
};
static ColorVector s_house_colors {	// белые грани
	{  1.0f, 1.0f, 0.9f },
	{  0.9f, 0.9f, 1.0f },
	{  0.9f, 1.0f, 1.0f },
	{  1.0f, 0.9f, 0.9f },
	{  1.0f, 0.9f, 1.0f },
	{  1.0f, 1.0f, 0.9f },
};

static TexCoordVector s_house_tex_coords {
	{  { 0.50, 1.00 }, { 0.50, 0.50 }, { 0.625, 0.25 }, { 0.75, 0.50 }, { 0.75, 1.00 } },
	{  { 0.50, 1.00 }, { 0.50, 0.50 }, { 0.625, 0.25 }, { 0.75, 0.50 }, { 0.75, 1.00 } },
	{  { 0.00, 0.50 }, { 0.00, 0.00 }, { 0.50, 0.00 }, { 0.50, 0.50 } },
	{  { 0.00, 0.50 }, { 0.00, 0.00 }, { 0.50, 0.00 }, { 0.50, 0.50 } },
	{  { 0.00, 1.00 }, { 0.00, 0.50 }, { 0.50, 0.50 }, { 0.50, 1.00 } },
	{  { 0.00, 1.00 }, { 0.00, 0.50 }, { 0.50, 0.50 }, { 0.50, 1.00 } },
};

Model house {
	s_house_vertices, s_house_faces, s_house_normals, s_house_colors, s_house_tex_coords
};

GLDemoWindow::GLDemoWindow(int width, int height)
: Window (width, height), _crate_texture("dom.png")
{
	SDL_GL_SetSwapInterval(1); //1- VSync синхронизация с обновлением экрана
	_turn_angle = 0.;
	_tilt_phase = 0.;
}

void GLDemoWindow::setup() {
	glEnable(GL_DEPTH_TEST);//проверка буфера глубины
	glEnable(GL_LIGHTING);//расчет освещенности
	glEnable(GL_LIGHT0);//включаем источник света
	glEnable(GL_TEXTURE);
	glClearColor(0.3f, 0.1f, 1.0f, 0.6f);
	glMatrixMode(GL_PROJECTION);//матрица проекций
	gluPerspective(45.0, double (getWidth()) / double (getHeight()), 0.01, 30.0);
	glMatrixMode(GL_MODELVIEW);//матрица моделей вида MV
	glPushMatrix();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);//не рисует задние грани
	glFrontFace(GL_CW);
}
//дом
void GLDemoWindow::render() {
	double x0 = -0.5, y0 = -1.0, z0 = -1.0;	// координаты домика
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(6.0, 3.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0); //вид
	glPushMatrix();
	glTranslated(0.0, 0.0, z0);
	draw_snow();
	glPopMatrix();
	glPushMatrix();
	_crate_texture.bind();//привязка текстуры
	glEnable(GL_TEXTURE_2D);
	glTranslated(x0, y0, z0);
	glScaled(1.0, 1.0, 1.0); //размер дома
	draw_model(house);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();

	glTranslated(x0 - 0.5, y0 + 3.0 , z0); //двигаем елку
	glScaled(1.5, 1.5, 1.5); //размер ёлки
	draw_tree(6);

	glPopMatrix();
	glTranslated(x0 + 2.9, y0 - 0.8, z0 + 0.3); //двигаем снеговика
	glScaled(0.4, 0.4, 0.4); //размер снеговика
	draw_snowman();

}

void GLDemoWindow::draw_model(Model &model) {
	for (unsigned i =0; i < model.faces.size(); ++i){
		int count = model.faces[i][0];
		if (count == 3)
			glBegin(GL_TRIANGLES);
		else if (count == 4)
			glBegin(GL_QUADS);
		else
			glBegin(GL_POLYGON);

		glNormal3dv(&model.normals[i][0]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &model.colors[i][0]);
		for (int j = 1; j <= count; ++j){
			glTexCoord2dv(&model.tex_coords[i][j-1][0]);
			glVertex3dv(&model.vertices[model.faces[i][j]][0]);
		}
		glEnd();
	}
}
//елка
void GLDemoWindow::draw_tree(int n) {
	ColorVector tree_color{
		{0.0f, 1.0f, 0.2f}
	};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &tree_color[0][0]);
	make_cone_smooth(20);
	for (int i = 0; i < n; ++i){
		glScaled(0.7, 0.7, 0.7);
		glTranslated(0.0, 0.0, 0.9);//расстояние между частями елки
		make_cone_smooth(50);
	}
}
//снеговик
void GLDemoWindow::draw_snowman() {
	 ColorVector snowman_colors {
			{  1.0f, 1.0f, 1.0f },
			{  1.0f, 0.1f, 0.0f },
			{  0.0f, 0.0f, 0.0f },
		};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &snowman_colors[0][0]);
	make_sphere_smooth(20,20);
	for (int i = 0; i < 2; ++i){
			glScaled(0.7, 0.7, 0.7);
			glTranslated(0.0, 0.0, 2.0); //тело снеговика
			make_sphere_smooth(20,20);
		}
	glScaled(0.5, 0.5, 0.5);
	glTranslated(0.0, -5.0, -3.0);
	make_sphere_smooth(10,10);

	glTranslated(0.0, 10.0, 0.0);
	make_sphere_smooth(20,20);

	glTranslated(2.0, -3.0, 3.0);
	glRotated(90, 0.0, 2.0, 1.0);

	glScaled(0.3, 0.3, 0.8);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &snowman_colors[1][0]);
	make_cone_smooth(10);

}
//поверхность земли
void GLDemoWindow::draw_snow() {
	ColorVector snow_color{
		{  1.0f, 1.0f, 1.0f }
	};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &snow_color[0][0]);
	glBegin(GL_QUADS);
	glVertex3d(-15.0, -15.0, 0.0);
	glVertex3d(-15.0, 15.0, 0.0);
	glVertex3d(15.0, 15.0, 0.0);
	glVertex3d(15.0, -15.0, 0.0);

	glEnd();
}

void GLDemoWindow::do_logic()
{
	_turn_angle += 2.;
	if (_turn_angle >= 360.)
		_turn_angle -= 360.;

	_tilt_phase += Pi / 200.;
	if (_tilt_phase >= Pi * 2.)
		_tilt_phase -= Pi * 2.;
}

void GLDemoWindow::coord_surface() {
	static ColorVector coord_colors {
		{  1.0f, 0.0f, 0.0f },
		{  1.0f, 1.0f, 0.0f },
		{  0.0f, 1.0f, 0.0f },
	};

	glLineWidth(3);
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &coord_colors[0][0]);
	glVertex3d(-5.0, 2.0, 0.0);
	glVertex3d(5.0, 2.0, 0.0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &coord_colors[1][0]);
	glVertex3d(0.0, -5.0, 0.0);
	glVertex3d(0.0, 5.0, 0.0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &coord_colors[2][0]);
	glVertex3d(0.0, 0.0, -5.0);
	glVertex3d(0.0, 0.0, 5.0);

	glEnd();
}
