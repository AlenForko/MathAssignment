# MathAssignment

This repository contains the source code and documentation for my 3D math assignment during my studies at Futuregames. The project uses [Nano](https://github.com/pfist/Nano), a template for Unreal Engine.

## Table of Contents
- [Exercises](#exercises)
  - [State & Context](#state--context)
  - [Interpolation](#interpolation)
  - [Intersection](#intersection)
  - [Collision](#collision)
  - [Noise](#noise)

## Exercises

### [State & Context](https://github.com/AlenForko/MathAssignment/tree/main/Source/MathAssignment/State%26Context)

During this assignment, the task was to create objects that trigger different reactions based on the relationships of their transformations. To address this, I initiated the process by establishing a library. Leveraging bitflags, I implemented a method to precisely calculate the world location of each object within the [library](https://github.com/AlenForko/MathAssignment/blob/main/Source/MathAssignment/ContextLibrary.h).

This library function returns an integer, which is then translated into boolean values using an enumeration. Subsequently, these boolean values are employed within my ['StateActor'](https://github.com/AlenForko/MathAssignment/blob/main/Source/MathAssignment/State%26Context/StateActor.cpp). The `StateActor` utilizes this information to dynamically determine the object's position in relation to others, thus enabling the appropriate reactions based on the calculated context.

// Add GIF here

### [Interpolation](https://github.com/AlenForko/MathAssignment/tree/main/Source/MathAssignment/Interpolation)

In the context of my Math Assignment, the Interpolation section introduces a systematic approach to directing object movements. The objective was to implement diverse motions such as scaling, rotation, and vertical movement. To accomplish this, I introduced an enum 'ELerpType,' providing a structured mechanism for specifying the desired interpolation type.

A notable challenge emerged when the 'SelectedLerps' showed only indexes instead of the actual names of the selected interpolation types. To enhance readability, I employed a 'TMap' to convert boolean values into string representations. Now, the 'SelectedLerps' map displays the actual names of the selected interpolation types.

Based on the chosen lerp type and its corresponding value, the object undergoes continuous interpolation, smoothly transitioning between states as time progresses.

// Add GIF here

### [Intersection](https://github.com/AlenForko/MathAssignment/tree/main/Source/MathAssignment/Intersection)

Intersection was one of the two exercises I found to be relatively interesting to work on. I wanted to learn more about AABB and Sphere intersection. So I started by creating a [library](https://github.com/AlenForko/MathAssignment/blob/main/Source/MathAssignment/Intersection/IntersectionLibrary.h) and different intersection functions to later incorporate into a subsystem which will calculate the intersection type based on the object type.

As these functions became the foundation, I seamlessly integrated them into the [IntersectionSubsystem](https://github.com/AlenForko/MathAssignment/blob/main/Source/MathAssignment/Intersection/IntersectionSubsystem.cpp), a system orchestrating the dynamic intersection types based on the objects themselves. 

With the [IntersectionActor](https://github.com/AlenForko/MathAssignment/blob/main/Source/MathAssignment/Intersection/IntersectionActor.cpp) I only draw the shape of the object and then call it in the subsystem to do it's magic.

// GIF here

### [Collision](https://github.com/AlenForko/MathAssignment/tree/main/Source/MathAssignment/Intersection)

To enhance the intersection functionality, I endeavored to implement a custom 'sphere-to-sphere' collision. The key modification involved adapting the existing intersection function and incorporating a 'contact point.' The initial step involved creating a 'RaySphere' function designed to calculate the contact point of the sphere intersection, subsequently storing this value for reference.

Once the contact point was successfully established, I implemented a dedicated function within the actor class to manage collision events. When actors intersect, this function retrieves the normal of the collision point and utilizes it to reflect the velocity, effectively simulating the impact and response associated with a collision scenario.

// GIF here

### [Noise](https://github.com/AlenForko/MathAssignment/tree/main/Source/MathAssignment/Noise)

For the final exercise in this assignment, I delved into the fascinating realm of procedural noise generation. Inspired by a demonstration from our teacher on terrain generation using Perlin noise, I decided to implement my own version of this fun concept.

Utilizing Unreal Engine's 'ProceduralMeshComponent,' I created a function within the [TerrainGenerator](https://github.com/AlenForko/MathAssignment/blob/main/Source/MathAssignment/Noise/TerrainGenerator.cpp) class to dynamically generate terrain meshes by calculating the vertices and triangles. Using the 'PerlinNoise2D' function, I successfully achieved the creation of smooth and aesthetically pleasing hills which generate throughout the whole terrain.

// GIF here
