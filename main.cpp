#include <cstdlib>
#include<gl/glut.h>
#include <cstdio>
#include <ctime>

#include"CRay.h"
#include"CSphere.h"
#include"triangle.h"
#include"IntersectResult.h"
#include"perspectiveCamera.h"
#include"plane.h"
#include"color.h"
#include"phongmaterial.h"
#include"checkermaterial.h"
#include"union.h"
#include"directlight.h"
#include"PointLight.h"

#include "ObjLoader.h"
#include "timeCount.h"

const int WINDOW_WIDTH=800;
const int WINDOW_HEIGHT=800;

namespace SceneToRender {
	const float horiz = 0.0;
	const float dep = 10;
	const int maxDepth = 25;
	const int maxReflect = 5;

	const float dx = 1.0f / WINDOW_WIDTH;
	const float dy = 1.0f / WINDOW_HEIGHT;
	const float dD = 255.0f / maxDepth;//灰阶，255--0，黑---白
	Color imagebuffer[WINDOW_WIDTH][WINDOW_HEIGHT] = {};

	CObject* scene = nullptr;

	PerspectiveCamera camera;
	PointLight light2;

	//PerspectiveCamera camera(GVector3(-10, -5, -10), GVector3(1, 1, 1), GVector3(0, 0, 1), 90);
	//PointLight light2(Color::white().multiply(3), GVector3(-10, -10, -10), true);

	void initWithModel() {
		camera=PerspectiveCamera(GVector3(-10, -5, -10), GVector3(1, 1, 1), GVector3(0, 0, 1), 90);
		light2=PointLight(Color::white().multiply(3), GVector3(-10, -10, -10), true);
		const string path = "test.obj";
		ObjLoader *ob = new ObjLoader(path);
		//sphere1->material = new PhongMaterial(Color::green(), Color::white(), 16);
		ob->setMaterial(new PhongMaterial(Color::green(), Color::white(), 16, 0.25f));

		Triangle* triangle1 = new Triangle(GVector3(100, 100, 50), GVector3(-100, -100, 50), GVector3(100, -100, 50));
		Triangle* triangle2 = new Triangle(GVector3(100, 100, 50), GVector3(-100, 100, 50), GVector3(-100, -100, 50));
		//triangle1->material = (new PhongMaterial(Color(5,2,3), Color::white(), 16, 0.1f));
		triangle1->material = (new PhongMaterial(Color(5, 2, 3), Color::white(), 16, 0.25f));
		triangle2->material = (new PhongMaterial(Color(5,2,3), Color::white(), 16, 0.25f));
		Union* _union = new Union();
		_union->push(ob);
		_union->push(triangle1);
		_union->push(triangle2);
		scene = _union;
	}

	void initWithSphere();
	void initWithTriangle();
	void initWithTwoSphere();
	void initWith4Triangle();
	void MyGlRenderGray();
	void MyGlRenderModel();
	void MyGlRenderModelwithPointLight();
	void MyGlRenderModelwithRayTrace();
	void destroyIfUsed() {
		if (scene != nullptr) { 
			delete scene;
			scene = nullptr;
		}
	}


	void initWithSphere2()
	{
		destroyIfUsed();
		camera = PerspectiveCamera(GVector3(horiz, 0, dep), GVector3(0, 0, -1), GVector3(0, 1, 0), 90);
		light2 = PointLight(Color::white().multiply(2), GVector3(10, 10, 10), true);
		CSphere* sphere1 = new CSphere(GVector3(0, 0, -10), 3);
		sphere1->material = (new PhongMaterial(Color::green(), Color::white(), 2, 0.25, 0.5));

		scene = sphere1;

		scene = scene;
	}
	void initWithSphere()
	{
		destroyIfUsed();
		camera=PerspectiveCamera  (GVector3(horiz, 0, dep), GVector3(0, 0, -1), GVector3(0, 1, 0), 90);
		light2=PointLight(Color::white().multiply(2), GVector3(10, 10, 10), true);
		CSphere* sphere1 = new CSphere(GVector3(0, 0, -10),3 );
		sphere1->material = (new PhongMaterial(Color::green(), Color::white(), 2, 0.25,0.5));
		/*CRay test1 = CRay(GVector3(0, 0, -7), GVector3(0, 0, -1));
		CRay test2 = CRay(GVector3(0, 0, -13), GVector3(0, 0, -1));
		sphere1->isIntersected(test1);
		sphere1->isIntersected(test2);*/

		Triangle* triangle1 = new Triangle(GVector3(100, 100, -50), GVector3(100, -100, -50), GVector3(-100, -100, -50));
		Triangle* triangle2 = new Triangle(GVector3(100, 100, -50), GVector3(-100, -100, -50), GVector3(-100, 100, -50));
		
		triangle1->material = (new PhongMaterial(Color(2.5,0.5,1), Color::white(), 16, 0.25f));
		triangle2->material = (new PhongMaterial(Color(2.5, 0.5, 1), Color::white(), 16, 0.25f));
		Union* _union = new Union();
		_union->push(sphere1);
		_union->push(triangle1);
		_union->push(triangle2);
		scene = _union;

		scene = _union;
	}

	void initWithTriangle()
	{
		camera = PerspectiveCamera(GVector3(horiz, 0, dep), GVector3(0, 0, -1), GVector3(0, 1, 0), 90);
		light2 = PointLight(Color::white().multiply(3), GVector3(10, 20, 10), true);
		destroyIfUsed();
		Triangle* triangle = new Triangle(GVector3(0,0,-10),  GVector3(4,-5,0), GVector3(-4, -5, 0));
		//Triangle* triangle = new Triangle(GVector3(0, 0, 0), GVector3(4, -5, 0), GVector3(-4, -5, 0));
		//Triangle* triangle = new Triangle(GVector3(-4, -5, 0),  GVector3(4,-5,0), GVector3(0, 0, -10));
		triangle->material = (new PhongMaterial(Color::green(), Color::blue(), 16, 0.25f));
		scene = triangle;
	}

	void initWithTwoSphere()
	{

		camera = PerspectiveCamera(GVector3(horiz, 0, dep), GVector3(0, 0, -1), GVector3(0, 1, 0), 90);
		light2 = PointLight(Color::white().multiply(3), GVector3(10, 20, 10), true);
		destroyIfUsed();


		Triangle* triangle = new Triangle(GVector3(0, 100, -60), GVector3(100, -100, -60), GVector3(-100, -100, -60));
		triangle->material = (new PhongMaterial(Color(4,5,6), Color::white(), 16, 0.25f));
		//Plane* plane1 = new Plane(GVector3(0, 1, 0), 1.0);
		CSphere* sphere1 = new CSphere(GVector3(-2, 5, -10), 5.0);
		CSphere* sphere2 = new CSphere(GVector3(5, 5, -10), 3.0);
		CSphere* sphere3 = new CSphere(GVector3(0,0,-40), 20.0);

		//plane1->material = new CheckerMaterial(0.1f);
		//sphere1->material = new PhongMaterial(Color::green(), Color::white(), 16);
		//sphere2->material = new PhongMaterial(Color::blue(), Color::white(), 16);
		sphere1->material = new PhongMaterial(Color(0.1,0.1,0.1), Color::black(), 2,0.2,0.9f);
		//sphere1->material = new PhongMaterial(Color(0.3, 0.4,0.5), Color::white(), 2, 0.3);
		sphere2->material = new PhongMaterial(Color::blue(), Color::white(), 16,0.25f);
		sphere3->material = new PhongMaterial(Color::red(), Color::white(), 16, 0.25f);

		Union *_union = new Union();
		//_union->push(plane1);
		_union->push(sphere1);
		_union->push(sphere2);
		_union->push(sphere3);
		_union->push(triangle);

		scene = _union;
	}
	void initWith4Triangle()
	{
		camera = PerspectiveCamera(GVector3(-10, -5, -10), GVector3(1, 1, 1), GVector3(0, 0, 1), 90);
		light2 = PointLight(Color::white().multiply(3), GVector3(-10, -10, -10), true);
		destroyIfUsed();
		//Triangle* triangle = new Triangle(GVector3(0,0,-10),  GVector3(4,-5,0), GVector3(-4, -5, 0));
		//Triangle* triangle = new Triangle(GVector3(0, 0, 0), GVector3(4, -5, 0), GVector3(-4, -5, 0));
		Triangle* triangle1 = new Triangle(GVector3(0, 0, 0), GVector3(10, 0, 0), GVector3(0, 10, 0));
		Triangle* triangle2 = new Triangle(GVector3(0, 0, 0), GVector3(0, 0, 10), GVector3(10, 0, 0));
		Triangle* triangle3 = new Triangle(GVector3(0, 0, 0), GVector3(0, 10, 0), GVector3(0, 0, 10));
		Triangle* triangle4 = new Triangle(GVector3(10, 0, 0), GVector3(0, 0, 10), GVector3(0, 10, 0));
		triangle1->material = (new PhongMaterial(Color::green(), Color::blue(), 16, 0.25f));
		triangle2->material = (new PhongMaterial(Color::green(), Color::blue(), 16, 0.25f));
		triangle3->material = (new PhongMaterial(Color::green(), Color::blue(), 16, 0.25f));
		triangle4->material = (new PhongMaterial(Color::green(), Color::blue(), 16, 0.25f));
		Union *_union = new Union();

		_union->push(triangle1);
		_union->push(triangle2);
		_union->push(triangle3);
		_union->push(triangle4);
		scene = _union;
	}


	Color phongcalculate( CRay& _eyesray, CRay& _lightray, IntersectResult &_result)
	{
		CObject* _object = _result.object;
		GVector3 _position = _result.position;
		GVector3 _normal = _result.normal;

		Color LightStrong = light2.intersect(scene, _result);
		Color EnvironmentLight = Color(0.05, 0.05, 0.05);
		
		GVector3 lightdir = _lightray.getDirection().normalize();
		GVector3 ag_lightdir = lightdir * -1;

		
		//漫反射diffuse = Id•Kd• (N•L)
		float NdotL = _normal.dotMul(ag_lightdir);
		Color diffuseTerm = _object->material->diffuse.multiply(std::max(NdotL, 0.0f));

		//物体镜面反射specular = Is•Ks• (V·R)^n
		//R = 2(L•N)•N-L
		//V是相机方向向量，R是反射向量，­n­就反射强度Shininess
		/*为了提高计算效率，也可以利用HalfVectorH来计算镜面反射。
		specular = Is•Ks•(N•H)^n
		其中H = (L + V) / 2
		*/

		GVector3 eyesdir = _eyesray.getDirection().normalize()*-1.0;
		GVector3 H = (ag_lightdir + eyesdir).normalize();
		float NdotH = _normal.dotMul(H);
		Color specularTerm = _object->material->specular.multiply(pow(std::max(NdotH, (float)0), _object->material->shininess));

		Color dif_spec = LightStrong.modulate(diffuseTerm.add(specularTerm));
		Color ambient = EnvironmentLight.modulate(_object->material->Ka);
		return dif_spec.add(ambient);
	}

	Color phongcalculate(CObject* _object, CRay& _eyesray, CRay& _lightray, GVector3 _position, GVector3 _normal, Color LightColor)
	{
		
		Color EnvironmentLight = Color(0.05, 0.05, 0.05);
		//漫反射diffuse = Id•Kd• (N•L)
		GVector3 lightdir = _lightray.getDirection().normalize()*-1.0;
		GVector3 eyesdir = _eyesray.getDirection().normalize()*-1.0;
		float NdotL = _normal.dotMul(lightdir);
		Color diffuseTerm = _object->material->diffuse.multiply(std::max(NdotL, 0.0f));

		//物体镜面反射specular = Is•Ks• (V·R)^n
		//R = 2(L•N)•N-L
		//V是相机方向向量，R是反射向量，­n­就反射强度Shininess
		/*为了提高计算效率，也可以利用HalfVectorH来计算镜面反射。
		specular = Is•Ks•(N•H)^n
		其中H = (L + V) / 2
		*/


		GVector3 H = (lightdir - eyesdir).normalize();
		float NdotH = _normal.dotMul(H);
		Color specularTerm = _object->material->specular.multiply(pow(std::max(NdotH, (float)0), _object->material->shininess));

		Color dif_spec = LightColor.modulate(diffuseTerm.add(specularTerm));
		Color ambient = EnvironmentLight.modulate(_object->material->Ka);
		return dif_spec.add(ambient);
	}

	Color rayTraceRecursive(CObject* _object, CRay& _ray, int _maxReflection)
	{
		IntersectResult result = _object->isIntersected(_ray);
		if (result.isHit)
		{
			float reflectiveness = result.object->material->getReflec();
			Color color = result.object->material->sample(_ray, result.position, result.normal);
			color = color.multiply(1 - reflectiveness);
			if (reflectiveness > 0 && _maxReflection > 0)
			{
				GVector3 refle_directon = result.normal*(-2 * result.normal.dotMul(_ray.getDirection()));
				CRay refle_ray = CRay(result.position, refle_directon);
				Color reflectedColor = SceneToRender::rayTraceRecursive(_object, refle_ray, _maxReflection - 1);
				color = color.add(reflectedColor.multiply(reflectiveness));
			}
			return color;
		}
		else return Color::black();

	}

	CRay generalRefractRay(CRay _ray,IntersectResult result , float refractRatio)
	{
		//refractRatio = sinθ' / sinθ 
		//static bool Refract(const Vector3&amp; vec, const Vector3&amp; normal, float refractRatio, Vector3&amp; refractDir)
		//	｛
		//	Vector3 inVec = vec;
		//inVec.Normalize();
		//float dt = Vector3::Dot(inVec, normal); //cosθ
		//float s2 = 1.0 - dt * dt; // sinθ ^ 2
		//float st2 = refractRatio * refractRatio * s2;// sinθ’ ^ 2 = refractRato ^ 2 * sinθ ^ 2
		//float cost2 = 1 - st2;
		//if (cost2 &gt; 0)
		//	｛
		//	refractDir = (inVec - normal * dt) * refractRatio - normal * sqrt(cost2);
		//return true;
		//｝
		//	return false;
		//｝
		GVector3 inVec = _ray.getDirection();
		GVector3 refractDir;
		inVec.normalize();
		float cosTheta = inVec.dotMul(result.normal);
		float sinTheta_2 = 1.0 - cosTheta * cosTheta;
		float sinTheta2_2 = refractRatio * refractRatio*sinTheta_2;
		float cost2 = 1 - sinTheta2_2;
		if (cost2 > 0)
		{
			refractDir = (inVec - result.normal*cosTheta)*refractRatio - result.normal*sqrt(cost2);


			CRay refracRay = CRay(result.position, refractDir);

			return refracRay;
		}
		else {
			return CRay();
		}
	}
	Color rayTraceRecursive_NEW(CObject* _object, CRay& _ray, int _maxReflection)
	{
		IntersectResult result = _object->isIntersected(_ray);
		if (result.isHit)
		{
			CRay LightRay = CRay(result.position, result.position - light2.getPosition());
			//Color PhongColor = result.object->material->sample(_ray, result.position, result.normal);
			Color PhongColor = phongcalculate(_ray, LightRay, result);

			Color AllColor = Color::black();
			float reflectiveness = result.object->material->getReflec();
			float refractRatio = result.object->material->getRatio();
			//PhongColor = PhongColor.multiply(1 - reflectiveness);
			PhongColor = PhongColor.multiply(1 - reflectiveness);
			AllColor = AllColor.add(PhongColor);
			if (reflectiveness > 0 && _maxReflection > 0)
			{
				GVector3 refle_directon = result.normal*(-2 * result.normal.dotMul(_ray.getDirection()));
				CRay ReflecRay = CRay(result.position, refle_directon);
				Color reflectedColor = rayTraceRecursive_NEW(_object, ReflecRay, _maxReflection - 1);

				AllColor = AllColor.add(reflectedColor.multiply(reflectiveness));
			}
			if (refractRatio > 0 && _maxReflection > 0)
			{
				CRay refracRay = generalRefractRay(_ray, result, refractRatio);
				IntersectResult result2 = result.object->isIntersected(refracRay);
				if (result2.object == result.object)
				{
					result2.normal = result2.normal*-1;
					refracRay = generalRefractRay(refracRay, result2, pow(refractRatio, -1));
				}
				Color refracColor = rayTraceRecursive_NEW(_object, refracRay, _maxReflection - 1);
				AllColor = AllColor.add(refracColor.multiply(refractRatio));
				//	/*GVector3 inVec = _ray.getDirection();
				//	GVector3 refractDir;
				//	inVec.normalize();
				//	float cosTheta = inVec.dotMul(result.normal);
				//	float sinTheta_2 = 1.0 - cosTheta * cosTheta;
				//	float sinTheta2_2 = refractRatio * refractRatio*sinTheta_2;
				//	float cost2 = 1 - sinTheta2_2;
				//	if (cost2 > 0)
				//	{
				//		refractDir = (inVec - result.normal*cosTheta)*refractRatio - result.normal*sqrt(cost2);
				//		CRay refracRay = CRay(result.position, refractDir);
				//		IntersectResult result2=result.object->isIntersected(refracRay);

				//		Color refracColor = rayTraceRecursive_NEW(_object, refracRay, _maxReflection - 1);
				//		AllColor.add(refracColor.multiply(refractRatio));
				//	}*/
				//	
			}
				return AllColor;
		}
			else return Color::black();

	
	}
	void MyGlRenderModel() {
		glBegin(GL_POINTS);
		for (long y = 0; y < WINDOW_HEIGHT; ++y)
		{
			float sy = 1 - dy * y;
			for (long x = 0; x < WINDOW_WIDTH; ++x)
			{
				float sx = dx * x;
				CRay ray(camera.generateRay(sx, sy));
				IntersectResult result = scene->isIntersected(ray);
				if (result.isHit)
				{
					//cout << "distance of result = " << result.distance << endl;
					//float t = MIN(result.distance*dD, 255.0f);
					//int depth = (int)(255.0f - t);
					//glColor3ub(depth, depth, depth);
					//glVertex2f(sx, sy);

					Color color = result.object->material->sample(ray, result.position, result.normal);
					color.saturate();
					glColor3ub(color.R * 255, color.G * 255, color.B * 255);
					glVertex2f(sx, sy);
				}
			}
		}
		glEnd();
		glFlush();
	}

	void MyGlRenderGray() {
		glBegin(GL_POINTS);
		for (long y = 0; y < WINDOW_HEIGHT; ++y)
		{
			float sy = 1 - dy * y;
			for (long x = 0; x < WINDOW_WIDTH; ++x)
			{
				float sx = dx * x;
				CRay ray(camera.generateRay(sx, sy));
				IntersectResult result = scene->isIntersected(ray);
				if (result.isHit)
				{
					float t = MIN(result.distance*dD, 255.0f);
					int depth = (int)(255.0f - t);
					glColor3ub(depth, depth, depth);
					glVertex2f(sx, sy);
				}
			}
		}
		glEnd();
		glFlush();
	}

	void MyGlRenderModelwithPointLight()
	{
		glBegin(GL_POINTS);
		for (long y = 0; y < WINDOW_HEIGHT; ++y)
		{
			float sy = 1 - dy * y;
			//double sy = 1 - dy * y;
			for (long x = 0; x < WINDOW_WIDTH; ++x)
			{
				float sx = dx * x;
				//double sx = dx * x;
				CRay ray(camera.generateRay(sx, sy));
				IntersectResult result = scene->isIntersected(ray);

				if (result.isHit)
				{
					Color resultcolor;
					////Color color1 = rayTraceRecursive(scene, ray, maxReflect);
					//Color lightShadowstrong = light2.intersect(scene, result);
					//resultcolor = lightShadowstrong;
					//CRay lightray = CRay(result.position, result.position - light2.getPosition());
					//resultcolor = phongcalculate(result.object, ray, lightray, result.position, result.normal, lightShadowstrong);

					CRay lightray = CRay(result.position, result.position - light2.getPosition());
					resultcolor = phongcalculate(ray, lightray,result);
					resultcolor.saturate();
					glColor3f(resultcolor.R * 255.0, resultcolor.G * 255.0, resultcolor.B * 255.0);
					glVertex2f(sx, sy);
				}
			}
		}
		glEnd();
		glFlush();
	}
	void MyGlRenderModelwithRayTrace()
	{
		glBegin(GL_POINTS);
		for (long y = 0; y < WINDOW_HEIGHT; ++y)
		{
			float sy = 1 - dy * y;
			//double sy = 1 - dy * y;
			for (long x = 0; x < WINDOW_WIDTH; ++x)
			{
				float sx = dx * x;
				//double sx = dx * x;
				CRay ray(camera.generateRay(sx, sy));
				IntersectResult result = scene->isIntersected(ray);

				if (result.isHit)
				{
					Color resultcolor;
					Color lightShadowstrong = light2.intersect(scene, result);
					resultcolor = lightShadowstrong;
					CRay lightray = CRay(result.position, result.position - light2.getPosition());
					resultcolor = phongcalculate(result.object, ray, lightray, result.position, result.normal, lightShadowstrong);

					Color color1 = SceneToRender::rayTraceRecursive(scene, ray, maxReflect);
					resultcolor.add(color1);

					resultcolor.saturate();
					glColor3f(resultcolor.R * 255.0, resultcolor.G * 255.0, resultcolor.B * 255.0);
					glVertex2f(sx, sy);
				}
			}
		}
		glEnd();
		glFlush();
	}
	void MyGlRenderModelwithRayTrace_NEW() {
		glBegin(GL_POINTS);

		//CRay testa = CRay(GVector3(0, 0, 0), GVector3(0, 0, -1));
		//IntersectResult resulta = scene->isIntersected(testa);
		//Color resultcolor = rayTraceRecursive_NEW(scene, testa, maxReflect);
		for (int y = 0; y < WINDOW_HEIGHT; ++y)
		{
			float sy = 1 - dy * y;
			//double sy = 1 - dy * y;
			for (int x = 0; x < WINDOW_WIDTH; ++x)
			{
				float sx = dx * x;
				//double sx = dx * x;
				CRay ray(camera.generateRay(sx, sy));
				IntersectResult result = scene->isIntersected(ray);

				if (result.isHit)
				{
					Color resultcolor = rayTraceRecursive_NEW(scene, ray, maxReflect);
					resultcolor.saturate();
					imagebuffer[x][y]=resultcolor;
				//	glColor3f(resultcolor.R * 255.0, resultcolor.G * 255.0, resultcolor.B * 255.0);
				//	glVertex2f(sx, sy);
				}
			}
		}
		for (int y = 0; y < WINDOW_HEIGHT; ++y)
		{
			float sy = 1 - dy * y;
			for (int x = 0; x < WINDOW_WIDTH; ++x)
			{
				float sx = dx * x;
				Color resultcolor = imagebuffer[x][y];
				glColor3f(resultcolor.R * 255.0, resultcolor.G * 255.0, resultcolor.B * 255.0);
				glVertex2f(sx, sy);
			}
		}
		glEnd();
		glFlush();
	}

	void renderGray()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();                                   // Reset The View
		glTranslatef(-0.5f, -0.5f, -1.0f);
		glPointSize(2.0);
		

		MyTimeCount::countTime(false);
		MyGlRenderGray();
		MyTimeCount::countTime(true);
	}
	void renderModel() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();                                   // Reset The View
		glTranslatef(-0.5f, -0.5f, -1.0f);
		glPointSize(2.0);
		//PerspectiveCamera camera(GVector3(horiz, 0, dep), GVector3(0, 0, -1), GVector3(0, 1, 0), 90);
		//PerspectiveCamera camera(GVector3(1, 1, 1), GVector3(-1, -1, -1), GVector3(0, 1, 0), 90);

		MyTimeCount::countTime(false);
		MyGlRenderModel();
		MyTimeCount::countTime(true);
	}
	void renderModelwithPointLight()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();                                  
		glTranslatef(-0.5f, -0.5f, -1.0f);
		glPointSize(2.0);

		MyTimeCount::countTime(false);
		MyGlRenderModelwithPointLight();
		MyTimeCount::countTime(true);
	}
	void renderModelwithRayTrace() 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glTranslatef(-0.5f, -0.5f, -1.0f);
		glPointSize(2.0);

		MyTimeCount::countTime(false);
		MyGlRenderModelwithRayTrace_NEW();

		MyTimeCount::countTime(true);
	}

}


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
			float colorR = x * 1.0f / WINDOW_WIDTH * 255;
			float colorB = y * 1.0f / WINDOW_HEIGHT * 255;

			//glColor3ub(colorR, 0, colorB);
			glColor3f(colorR, 0.0, colorB);
			glVertex2f(sx, sy);
		}
	}
	glEnd();
	glFlush();
}

void renderTriangle()
{
	int WW = WINDOW_WIDTH, HH = WINDOW_HEIGHT;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();                                   // Reset The View
	glTranslatef(-0.5f, -0.5f, -1.0f);
	glPointSize(2.0);
	float horiz = 0.0;
	float dep = 10;
	PerspectiveCamera camera(GVector3(horiz, 0, dep), GVector3(0, 0, -1), GVector3(0, 1, 0), 90);
	long maxDepth = 18;
	//CSphere* sphere1 = new CSphere(GVector3(0, 0, -10), 10.0);
	Triangle* triangle = new Triangle(GVector3(0,0,-10),  GVector3(4,-5,0),GVector3(-4, -5, 0));
	triangle->material = new PhongMaterial(Color::green(), Color::white(), 5, 0.25f);
	//Triangle* triangle = new Triangle(GVector3(-4,5,0),  GVector3(4,-5,0),GVector3(0,0,-10));
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
			//IntersectResult result = sphere1->isIntersected(ray);
			IntersectResult result = triangle->isIntersected(ray);
			if (result.isHit)
			{
				//double t = MIN(result.distance*dD, 255.0f);
				//int depth = (int)(255 - t);
				//glColor3ub(depth, depth, depth);
				//glVertex2f(sx, sy);

				Color color = result.object->material->sample(ray, result.position, result.normal);
				color.saturate();
				glColor3ub(color.R * 255, color.G * 255, color.B * 255);
				glVertex2f(sx, sy);
			}

		}
	}

	glEnd();
	glFlush();
}

void renderDepth()
{
	//int WW = 800, HH = 800;
	int WW = WINDOW_WIDTH, HH = WINDOW_HEIGHT;

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
				//double t = MIN(result.distance*dD, 255.0f);
				float t = MIN(result.distance*dD, 255.0f);

				//int depth = (int)(255 - t);
				//glColor3ub(depth, depth, depth);
				float depth = 255.0f - t;
				glColor3f(depth, depth, depth);

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
	//sphere1.material = new PhongMaterial(Color(1.0f,2.0f,3.0f).normalize(),Color::red(), Color::white(), 16.0f);

	sphere1.material = new PhongMaterial(Color::red().multiply(0.15), Color::red(), Color::white(), 16.0f);//Ka ,Kd,Ks,shinness,reflective
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

Color rayTraceRecursive(CObject* _object, CRay& _ray, int _maxReflection)
{
	IntersectResult result = _object->isIntersected(_ray);
	if (result.isHit)
	{
		float reflectiveness = result.object->material->getReflec();
		Color color = result.object->material->sample(_ray, result.position, result.normal);
		color = color.multiply(1 - reflectiveness);
		if (reflectiveness > 0 && _maxReflection > 0)
		{
			GVector3 refle_directon = result.normal*(-2 * result.normal.dotMul(_ray.getDirection()));
			CRay refle_ray = CRay(result.position, refle_directon);
			Color reflectedColor = rayTraceRecursive(_object, refle_ray, _maxReflection - 1);
			color = color.add(reflectedColor.multiply(reflectiveness));
		}
		return color;
	}
	else return Color::black();

}

void renderRecursive()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-0.5f, -0.5f, -1.0f);
	glPointSize(2.0f);

	PerspectiveCamera camera(GVector3(0, 20, 10), GVector3(0, -0.5, -1), GVector3(0, 1, 0), 90);
	Plane* plane1 = new Plane(GVector3(0, 1, 0), 1.0);
	CSphere* sphere1 = new CSphere(GVector3(-2, 5, -10), 5.0);
	CSphere* sphere2 = new CSphere(GVector3(5, 5, -10), 3.0);

	plane1->material = new CheckerMaterial(0.1f,0.5f);
	sphere1->material = new PhongMaterial(Color::green(), Color::white(), 16,0.25f);
	sphere2->material = new PhongMaterial(Color::blue(), Color::white(), 16,0.25f);

	Union scence;
	scence.push(plane1);
	scence.push(sphere1);
	scence.push(sphere2);

	long maxDepth = 20;
	long maxReflect = 5;
	float dx = 1.0f / WINDOW_WIDTH;
	float dy = 1.0f / WINDOW_HEIGHT;
	float dDeep = 255.0f / maxDepth;
	glBegin(GL_POINTS);
	for (long y = 0; y < WINDOW_HEIGHT; y++)
	{
		float sy = 1 - dy * y;
		for (long x = 0; x < WINDOW_WIDTH; x++)
		{

			float sx = 1 - dx * x;
			CRay ray(camera.generateRay(sx, sy));
			IntersectResult result = scence.isIntersected(ray);
			if (result.isHit)
			{
				
				Color color = rayTraceRecursive(&scence, ray, maxReflect);
				//Color color = result.object->material->sample(ray, result.position, result.normal);
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

void renderLight()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-0.5f, -0.5f, -1.0f);
	glPointSize(2.0f);

	Union scene;
	PerspectiveCamera camera(GVector3(0, 10, 10), GVector3(0, 0, -1), GVector3(0, 1, 0), 90);
	Plane*plane1 = new Plane(GVector3(0, 1, 0), 0.0);
	Plane*plane2 = new Plane(GVector3(0, 0, 1), -50);
	Plane*plane3 = new Plane(GVector3(1, 0, 0), -20);
	CSphere* sphere1 = new CSphere(GVector3(0, 10, -10), 10.0);

	//	plane1->material = new CheckerMaterial(0.1f, 0.5f);
	//	plane2->material = new CheckerMaterial(0.1f, 0.5f);
	//	plane3->material = new CheckerMaterial(0.1f, 0.5f);

	plane1->material = new PhongMaterial(Color::red(), Color::white(), 0.1, 0.01f);
	plane2->material = new PhongMaterial(Color::blue(), Color::white(), 0.1, 0.01f);
	plane3->material = new PhongMaterial(Color::white(), Color::white(), 0.1, 0.01f);



	sphere1->material = new PhongMaterial(Color::green(), Color::white(), 5, 0.25f);

	DirectLight light1(Color::white(), GVector3(-1.75, -2, -1.5), true);
	//PointLight light2(Color::white().multiply(200), GVector3(10, 20, 10), true);

	scene.push(plane1);
	scene.push(plane2);
	scene.push(plane3);
	scene.push(sphere1);
	long maxDepth = 20;
	long maxReflect = 5;
	float dx = 1.0f / WINDOW_WIDTH;
	float dy = 1.0f / WINDOW_HEIGHT;
	float dD = 255.0f / maxDepth;

	//time_t timeBegin, timeEnd;
	//timeBegin = time(NULL);
	MyTimeCount::countTime(false);

	glBegin(GL_POINTS);
	for (long y = 0; y < WINDOW_HEIGHT; ++y)
	{
		float sy = 1 - dy * y;
		for (long x = 0; x < WINDOW_WIDTH; ++x)
		{
			float sx = dx * x;
			CRay ray(camera.generateRay(sx, sy));
			IntersectResult result = scene.isIntersected(ray);

			if (result.isHit)
			{
				Color color1 = rayTraceRecursive(&scene, ray, maxReflect);
				Color color2= light1.intersect(scene, result);
				Color color = color1.modulate(color2);

				
				//Color color = light1.intersect(scene, result);

				color.saturate();
			//	color.show();
				//color = color.normalize();
				glColor3ub(color.R * 255, color.G * 255, color.B * 255);
				glVertex2f(sx, sy);
			}
		}
	}
	glEnd();
	glFlush();
	//timeEnd = time(NULL);
	//cout << "用时：" << timeEnd - timeBegin << endl;
	MyTimeCount::countTime(true);
}


//void renderPointLight()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
//	glTranslatef(-0.5f, -0.5f, -1.0f);
//	glPointSize(2.0f);
//
//	CObject* scene;
//	PerspectiveCamera camera(GVector3(0, 10, 10), GVector3(0, 0, -1), GVector3(0, 1, 0), 90);
//	Plane*plane1 = new Plane(GVector3(0, 1, 0), 0.0);
//	Plane*plane2 = new Plane(GVector3(0, 0, 1), -50);
//	Plane*plane3 = new Plane(GVector3(1, 0, 0), -20);
//	CSphere* sphere1 = new CSphere(GVector3(0, 10, -10), 10.0);
//
//	plane1->material = new CheckerMaterial(0.1f, 0.5f);
//	plane2->material = new CheckerMaterial(0.1f, 0.5f);
//	plane3->material = new CheckerMaterial(0.1f, 0.5f);
//
//	//plane1->material = new PhongMaterial(Color::red(), Color::white(), 0.1, 0.25f);
//	//plane2->material = new PhongMaterial(Color::blue(), Color::white(), 0.1, 0.25f);
//	//plane3->material = new PhongMaterial(Color::white(), Color::white(), 0.1, 0.25f);
//
//	sphere1->material = new PhongMaterial(Color::green(), Color::white(), 5, 0.25f);
//	
//	//DirectLight light1(Color::white().multiply(0.5), GVector3(-1.75, -2, -1.5), true);
//	PointLight light2(Color::white().multiply(200), GVector3(10, 20, 10), true);
//	Union * uniona;
//	uniona->push(plane1);
//	uniona->push(plane2);
//	uniona->push(plane3);
//	uniona->push(sphere1);
//	scene = uniona;
//	long maxDepth = 20;
//	long maxReflect = 5;
//	float dx = 1.0f / WINDOW_WIDTH;
//	float dy = 1.0f / WINDOW_HEIGHT;
//	float dD = 255.0f / maxDepth;
//
//	//time_t timeBegin, timeEnd;
//	//timeBegin = time(NULL);
//
//	MyTimeCount::countTime(false);
//
//	glBegin(GL_POINTS);
//	for (long y = 0; y < WINDOW_HEIGHT; ++y)
//	{
//		float sy = 1 - dy * y;
//		//double sy = 1 - dy * y;
//		for (long x = 0; x < WINDOW_WIDTH; ++x)
//		{
//			float sx = dx * x;
//			//double sx = dx * x;
//			CRay ray(camera.generateRay(sx, sy));
//			IntersectResult result = scene->isIntersected(ray);
//
//			if (result.isHit)
//			{
//				Color color1 = rayTraceRecursive(&scene, ray, maxReflect);
//				//Color color2= light1.intersect(scene, result);
//				Color color2 = light2.intersect(scene, result);
//				Color color = color1.modulate(color2);
//				/*pixelColor = SDL_MapRGB(screen->format, std::min(color.r * 255, (float)255), std::min(color.g * 255, (float)255.0), std::min(color.b * 255, (float)255.0));
//				drawPixel(screen, x, y, pixelColor);*/
//				color.saturate();
//				//color.show();
//
//				glColor3ub(color.R * 255, color.G * 255, color.B * 255);
//				//glColor3f(color.R * 255.0, color.G * 255.0, color.B * 255.0);
//
//				glVertex2f(sx, sy);
//			}
//		}
//	}
//	glEnd();
//	glFlush();
//	//timeEnd = time(NULL);
//	//cout << "用时：" << timeEnd - timeBegin << endl;
//
//	MyTimeCount::countTime(true);
//}


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
	//initScene(800,800);
	initScene(WINDOW_WIDTH, WINDOW_HEIGHT);

	//glutDisplayFunc(display);
	
	//glutDisplayFunc(renderDepth2);//单个球的局部光照
	//glutDisplayFunc(renderDepth3);//渲染棋盘平面
	//glutDisplayFunc(renderUnion);//场景：两个球与棋盘平平面的局部光照
	//glutDisplayFunc(renderRecursive);//场景：两个球与棋盘平平面的局部光照//非透明体
	//glutDisplayFunc(renderLight); // 场景：单球与三平面平面的局部光照

	//glutDisplayFunc(renderTriangle);//三角形的局部光照

	//初始化场景
	SceneToRender::initWithModel();//加载一个四面体的网格模型
	//SceneToRender::initWithTriangle();//加载一个三角形
	//SceneToRender::initWithSphere();  //加载一个球一个平面
	//SceneToRender::initWithSphere2(); //加载一个球
	//SceneToRender::initWithTwoSphere(); //加载三球三角面
	//SceneToRender::initWith4Triangle(); // 加载多个三角面

	//glutDisplayFunc(SceneToRender::renderGray);//渲染深度//求交测试
	//glutDisplayFunc(SceneToRender::renderModel);
	//glutDisplayFunc(SceneToRender::renderModelwithPointLight);//渲染局部光照//单点光源
	
	glutDisplayFunc(SceneToRender::renderModelwithRayTrace);//渲染全局光照

	glutReshapeFunc(windowChangeSize2);
	glutMainLoop();
	return 0;

}