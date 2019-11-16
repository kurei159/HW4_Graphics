# HW4_Graphics

By Cheuk-Wang Chau

# Description:
Based on the given starter code, NewShape.cpp and NewShape.h is added. This allows the program to draw a triangle with a ray tracer.

Major edits made on Scene.cpp, giving Phong Shading and Shadow Support. (Reflection incomplete)

Minor edits were made on Shape, and Sphere files. These were done to allow color and reflection options, however reflection is incomplete.

The new way to add a shape is by the following:
    scene.addShape(new Sphere(center, radius, Sphere Color, mirror));
      Where center and Sphere Color being Vector3's, radius being a double, and mirror being a boolean.
    
    scene.addShape(new NewShape(v0, v1, v2, TriangleColor, mirror));
      Where v0,v1,v2, and TriangleColor being Vector3's, and mirror being a boolean.
     
      
# Requirements:
Eigen 3.1.1 library (Not uploaded here)
libpng.lib
zlib.lib

# Environment:
Windows 10
Visual Studio Community 2017
  -Windows 8.1 SDK
  -VC++ 2015 V140
  
# Extra:
Progress percentage shown in console is given by Corey Smith to cure boredom while waiting.
