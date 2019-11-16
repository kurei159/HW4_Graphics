#include "Scene.h"
#include <iostream>
#include <cmath>
using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray &ray) {
    HitRecord result;
    result.t = -1;
    bool foundSomething = false;

	//My Comment: This is a for loop for the # of shapes in the vector
    for (unsigned int i = 0; i < shapes.size(); i++) {
        HitRecord r = shapes[i]->intersect(ray);
        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {
            result = r;
            foundSomething = true;
        }
    }

    return result;
}

// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray &ray) {
    // For now we'll have diffuse shading with no shadows, so it's easy!
    HitRecord r = closestHit(ray);

    Vector3d result;
    result[0] = result[1] = result[2] = 0;

    if (r.t < numeric_limits<double>::epsilon()) return result;

	//At this point r has result of an object

	//Problem 2: Add Phong Shading
	Vector3d lightColor = {1, 1, 1};
	Vector3d lightDir = (lightPos - r.position).normalized();
	
	//Problem 3: Shadow
	//This tmpRay is between the point on the normal and the light source, this is so we can see if something is in between the two
	//tmpR is used to obtain the information of the object which the ray hits
	Ray tmpRay;
	HitRecord tmpR;
	tmpRay.origin = r.position;
	tmpRay.direction = lightDir;
	float bias = 1; //Use a bias value to reduce shadow acne
	//Since shapes are saved as vectors, we can traverse to see if there are any shapes intersect with the ray, if it meets the condition then there is shadow 
	for (int i = 0; i < shapes.size(); i++)
	{
		tmpR = shapes[i]->intersect(tmpRay);
		
		if (tmpR.t > bias)
		{
			return result;
		}

	}



	//Ambient
	Vector3d Ambient = 0.2 * lightColor;
	
	//Diffuse

    double dot = lightDir.dot(r.normal);

	//Specular
	double specularStrength = 0.5;
	Vector3d viewDir = (ray.origin - r.position).normalized();

	Vector3d reflectDir = -lightDir - 2 * -lightDir.dot(r.normal.normalized()) * r.normal.normalized();

	double spec = pow(max(0.0, viewDir.dot(reflectDir)), 32);
	Vector3d objectColor = r.color;
	
	if (dot < 0)
	{
		dot = 0;
		spec = 0;
	}

	Vector3d Specular = specularStrength * spec * lightColor;
	

	result[0] = (Ambient[0] + dot + Specular[0]) * objectColor[0];
	result[1] = (Ambient[1] + dot + Specular[1]) * objectColor[1];
	result[2] = (Ambient[2] + dot + Specular[2]) * objectColor[2];

	//Check if surface is a mirror
	/*if (r.mirror)
	{

		Ray reflectRay;
		HitRecord ReflectRayRecord;
		Vector3d ReflectRayDirection = -viewDir - 2 * -viewDir.dot(r.normal.normalized()) * r.normal.normalized();
		reflectRay.origin = r.normal;
		reflectRay.direction = ReflectRayDirection;
		for (int i = 0; i < shapes.size(); i++)
		{
			ReflectRayRecord = shapes[i]->intersect(reflectRay);
			if (ReflectRayRecord.t > 1e-4 && ray.depth < 3) //Reflection intersects with object
			{
				reflectRay.depth++;
				
				return result += 0.8 * trace(reflectRay);
			}

		}

	}*/



	return result;
}

void Scene::render(Image &image) {
    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).

    assert(image.getWidth() == image.getHeight());

    int size = image.getWidth();
    double pixelSize = 2. / size;
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++) {
			Ray curRay;
			curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

			curRay.direction[0] = (x + 0.5) * pixelSize - 1;
			curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
			curRay.direction[2] = 1;

			Vector3d color = trace(curRay);
			image.setColor(x, y, color[0], color[1], color[2]);
		}
		system("CLS");
		printf("%3.2f%% done", (double)x / (size - 1) * 100);
		cout << flush;
	}

}
