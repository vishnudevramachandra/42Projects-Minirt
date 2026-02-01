# 42Projects-Minirt

This project has been created as part
of the 42 curriculum by vramacha & majkijew

Description

miniRT is a graphics project focused on building a minimal ray tracer in C. The main reference for the project was The Ray Tracer Challenge book, which guided the overall architecture and ray tracing concepts.

Our ray tracer handles the following:

- Ambient, diffuse, and specular lighting (Phong model)

- Multiple light sources (bonus)

- Colored lights and light intensity (bonus)

- Camera positioning and orientation

The following primitive objects:

- Sphere

- Plane

- Cylinder

- Cone (bonus)

- Object patterns (bonus)

- Texture mapping (bonus)


---------------------------------------------------------------
Instructions
----------------------------------------------------------------

- make bulid

- make

- ./miniRT <existing .rt file>

================================================

Example of .rt file :

C 0,0.2,-2    0.2,0.0,1 70
A 0.5 255,255,255
L -2,-3,8 0.8 255,000,000

co 0,0,8 3 4   255,100,100
sp 5,0,8      3   255,255,0
sp 0,3,4     3   255,128,0 P 255,0,0 1.3,1.2,0 chr 60

sp 2.5,-1,4     3   255,0,0

pl 0.0,5.0,-10.0 0.0,-1.0,0.0 0,0,225 P 0,0,0 0.5,0.5,0.5 chr 10
pl 5.0,0.0,0.0 -1.0,0.0,0.0 0,125,225 P 0,0,0 0.5,0.5,0.5 str 159
pl -5.0,0.0,0.0 1.0,0.0,0.0 125,0,225 P 0,0,0 0.5,0.5,0.5 ring 12
pl 0.0,-6.0,0.0 0.0,1.0,0.0 125,125,225 P 0,0,0 0.5,0.5,0.5 chr 43

==================================================

C [camera_position] [orientation_vector] [hotizontal_field]
A [brightness_ratio] [color]
L [position] [brightness_ratio] [color]

sp - SPHERE   [sphere_center] [sphere_diameter] [color]
pl - PLANE    [coordinates] [normal_vector] [color]
cy - CYLINDER [cylinder_center] [normal_vector_of_axis] [cylinder_diameter] [cylinder_height] [color]
co - CONE     [cone_apex_position] [cone_dia] [cone_height] [color]

PATTERNS (optional)
<after any figure> P [colors] [coordinates] [pattern type] 

Ratios: 

C [camera_position] none
C [orientation_vector] [-1 - 1]
C [hotizontal_field] [0 - 180]

A [brightness_ratio] [0.0 - 1.0]
A [color] [0 - 255]

L [position] none
L [brightness_ratio] [0.0 - 1.0]
L [color] [0 - 255]

------------------------------------------------------------------------

Resources

The Ray Tracer Challenge: https://www.playbook.com/s/tsang-hei-yiu/6Wiy1JmoGnQFp6oTQVJEzcaf?assetToken=a451apWr4b2yYJA16YUAFttF
