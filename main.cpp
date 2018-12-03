#include<stdlib.h>
#include<gl/glut.h>
#include<stdio.h>
#include"CRay.h"
#include"CSphere.h"
#include"IntersectResult.h"
#include"perspectiveCamera.h"
#include"plane.h"
#include"color.h"
#include"phongmaterial.h"
#include"checkermaterial.h"
#include"union.h"

const int  WINDOW_WIDTH=800;
const int  WINDOW_HEIGHT=800;

void initScene(int w, int h)
{
	glutInitDisplayMode(GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutCreateWindow("cglearn_lab3");
	// set up viewing GL_PROJECTION 投影, GL_MODELVIEW 模型视图, GL_TEXTURE 纹理.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0.0, 10000, 0.0, 1000);//可见坐标范围


	glShadeModel(GL_SMOOTH);//启用阴影平滑
	glClearColor(0, 0, 0, 0);//背景黑色
	glClearDepth(1.0);//设置深度缓存
	glEnable(GL_DEPTH_TEST);//启用深度测试
	glDepthFunc(GL_LEQUAL);//所作深度测试的类型
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//告诉系统对透视进行修正
}

void display()
{
	float colorSpan = 0.0005f;
	float color = 0.0f;
	float pixelSize = 2.0f;
	float posY = -1.0f;
	float posX = -1.0f;
	long maxDepth = 20;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//将原点移动到左下角
	glTranslatef(-0.5f, -0.5f, -1.0f);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	double dx = 1.0f / WINDOW_WIDTH;
	double dy = 1.0f / WINDOW_HEIGHT;
	float dD = 255.0f / maxDepth;
	glBegin(GL_POINTS);

	for (long y = 0; y < WINDOW_HEIGHT; ++y)
	{
		double sy = 1 - dy * y;
		for (long x = 0; x < WINDOW_WIDTH; ++x)
		{
			double sx = dx * x;
			float colorR = x * 1.0 / WINDOW_WIDTH * 255;
			float colorB = y * 1.0 / WINDOW_HEIGHT * 255;
			glColor3ub(colorR, 0, colorB);
			glVertex2f(sx, sy);
		}
	}
	glEnd();
	glFlush();
}

void renderDepth()
{
	int WW = 800, HH = 800;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();                                   // Reset The View
	glTranslatef(-0.5f, -0.5f, -1.0f);
	glPointSize(2.0);
	float horiz = 0.0;
	float dep = 10;
	PerspectiveCamera camera(GVector3(horiz, 0, dep), GVector3(0, 0, -1), GVector3(0, 1, 0), 90);
	long maxDepth = 18;
	CSphere* sphere1 = new CSphere(GVector3(0, 0, -10), 10.0);
	float dx = 1.0f / WW;
	float dy = 1.0f / HH;
	float dD = 255.0f / maxDepth;//灰阶，255--0，黑---白
	glBegin(GL_POINTS);
	for (long y = 0; y < HH; ++y)
	{
		float sy = 1 - dy * y;
		for (long x = 0; x < WW; ++x)
		{
			float sx = dx * x;
			CRay ray(camera.generateRay(sx, sy));
			IntersectResult result = sphere1->isIntersected(ray);
			if (result.isHit)
			{
				double t = MIN(result.distance*dD, 255.0f);
				int depth = (int)(255 - t);
				glColor3ub(depth, depth, depth);
				glVertex2f(sx, sy);
			}

		}
	}

	glEnd();
	glFlush();
}

void renderDepth2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();                                   // Reset The View
	glTranslatef(-0.5f, -0.5f, -1.0f);
	glPointSize(2.0);
	PerspectiveCamera camera(GVector3(0, 10, 10), GVector3(0, -0.5, -1), GVector3(0, 1, 0), 90);
	//Plane plane1(GVector3(0, 1, 0), 1.0);
	CSphere sphere1(GVector3(0, 5, -10), 5.0);
	//plane1.material = new CheckerMaterial(0.1f);
	sphere1.material = new PhongMaterial(Color::red(), Color::white(), 16.0f);
	long maxDepth = 20;

	float dx = 1.0f / WINDOW_WIDTH;
	float dy = 1.0f / WINDOW_HEIGHT;
	float dD = 255.0f / maxDepth;
	glBegin(GL_POINTS);
	for (long y = 0; y < WINDOW_HEIGHT; ++y)
	{
		float sy = 1 - dy * y;
		for (long x = 0; x < WINDOW_WIDTH; ++x)
		{
			float sx = dx * x;
			CRay ray(camera.generateRay(sx, sy));
			IntersectResult result = sphere1.isIntersected(ray);
			//IntersectResult result = plane1.isIntersected(ray);
			if (result.isHit)
			{
				Color color = sphere1.material->sample(ray, result.position, result.normal);
				//Color color =plane1.material->sample(ray, result.position, result.normal);
				color.saturate();
				//color.show();
				glColor3ub(color.R * 255, color.G * 255, color.B * 255);
				glVertex2f(sx, sy);
			}
		}
	}
	glEnd();
	glFlush();
}

void renderDepth3()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();                                   // Reset The View
	glTranslatef(-0.5f, -0.5f, -1.0f);
	glPointSize(2.0);
	PerspectiveCamera camera(GVector3(0, 10, 10), GVector3(0, -0.5, -1), GVector3(0, 1, 0), 90);
	Plane plane1(GVector3(0, 1, 0), 1.0);
	//CSphere sphere1(GVector3(0, 5, -10), 5.0);
	plane1.material = new CheckerMaterial(0.1f);
	//sphere1.material = new PhongMaterial(Color::red(), Color::white(), 16.0f);
	long maxDepth = 20;

	float dx = 1.0f / WINDOW_WIDTH;
	float dy = 1.0f / WINDOW_HEIGHT;
	float dD = 255.0f / maxDepth;
	glBegin(GL_POINTS);
	for (long y = 0; y < WINDOW_HEIGHT; ++y)
	{
		float sy = 1 - dy * y;
		for (long x = 0; x < WINDOW_WIDTH; ++x)
		{
			float sx = dx * x;
			CRay ray(camera.generateRay(sx, sy));
			//IntersectResult result = sphere1.isIntersected(ray);
			IntersectResult result = plane1.isIntersected(ray);
			if (result.isHit)
			{
				//Color color = sphere1.material->sample(ray, result.position, result.normal);
				Color color =plane1.material->sample(ray, result.position, result.normal);
				color.saturate();
				//color.show();
				glColor3ub(color.R * 255, color.G * 255, color.B * 255);
				glVertex2f(sx, sy);
			}
		}
	}
	glEnd();
	glFlush();
}

void renderUnion()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-0.5f, -0.5f, -1.0f);
	glPointSize(2.0f);

	PerspectiveCamera camera(GVector3(0, 10, 10), GVector3(0, -0.5, -1), GVector3(0, 1, 0), 90);
	Plane* plane1 = new Plane(GVector3(0, 1, 0), 1.0);
	CSphere* sphere1 = new CSphere(GVector3(-2, 5, -10), 5.0);
	CSphere* sphere2 = new CSphere(GVector3(5, 5, -10), 3.0);

	plane1->material = new CheckerMaterial(0.1f);
	sphere1->material = new PhongMaterial(Color::green(), Color::white(), 16);
	sphere2->material = new PhongMaterial(Color::blue(), Color::white(), 16);

	Union scence;
	scence.push(plane1);
	scence.push(sphere1);
	scence.push(sphere2);

	long maxDepth = 20;
	float dx = 1.0f / WINDOW_WIDTH;
	float dy = 1.0f / WINDOW_HEIGHT;
	float dDeep = 255.0f / maxDepth;
	glBegin(GL_POINTS);
	for (long y = 0; y < WINDOW_HEIGHT; y++)
	{
		float sy = 1 - dy * y;
		for (long x = 0; x < WINDOW_WIDTH; x++)
		{
			
			float sx =1- dx * x;
			CRay ray(camera.generateRay(sx, sy));
			IntersectResult result = scence.isIntersected(ray);
			if (result.isHit)
			{
				//cout << "hey";
				//cout << result.object;
				Color color = result.object->material->sample(ray, result.position, result.normal);
				color.saturate();
				//color.show();
				glColor3ub(color.R * 255, color.G * 255, color.B * 255);
				glVertex2f(sx, sy);
			}
		}
	}
	glEnd();
	glFlush();


}
void windowChangeSize(GLsizei w,GLsizei h)
{
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//建立裁剪空间的范围
	if (w <= h)
		glOrtho(0, 250.0, 0.0, 250.0*h / w, 1.0, -1.0);
	else
		glOrtho(0, 250.0*w / h,0.0, 250.0,  1.0, -1.0);

}
void windowChangeSize2(GLsizei width, GLsizei height)
{
	// 防止窗口大小变为0
	if (height == 0)
	{
		height = 1;
	}
	// 重置当前的视口
	glViewport(0, 0, (GLint)width, (GLint)height);
	// 选择投影矩阵
	glMatrixMode(GL_PROJECTION);
	// 重置投影矩阵
	glLoadIdentity();
	// 设置视口的大小
	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	// 选择模型观察矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc,char*argv[]) {

	glutInit(&argc, argv);
	initScene(800,800);
	//glutDisplayFunc(display);
	
	//glutDisplayFunc(renderDepth2);
	glutDisplayFunc(renderUnion);
	glutReshapeFunc(windowChangeSize2);
	glutMainLoop();
	return 0;

}