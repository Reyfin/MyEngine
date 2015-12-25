#pragma once

#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLu.h>

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <math.h>


#include "stb_image.h"
#include "Errors.h"
#include "Mesh.h"
#include "Math\3DMath.h"
#include "Camera3d.h"
#include "Material.h"
#include "Transform.h"
#include "Shader.h"

struct TerrainIndex //to be removed
	{
		GLuint vao,vab,count;

		TerrainIndex(std::vector<Vertex> &vertices)
		{
			glGenVertexArrays(1,&vao);
			glGenBuffers(1,&vab);
			count = vertices.size();
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER,vab);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,pos));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,uv));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,normal));
			glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(Vertex),&vertices[0],GL_STATIC_DRAW);
		}
		~TerrainIndex()
		{
			glDeleteBuffers(1,&vab);
			glDeleteVertexArrays(1,&vao);
		}
	};
struct TerrainPatch
{
	GLuint vao, vab, count;
	Material material;
	std::vector<Vertex> vertices;
	void load()
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vab);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vab);
		Vertex::loadSet();
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	}
	TerrainPatch(std::vector<Vertex> &Vertices,Material &material2):vertices(Vertices)
	{
		count = Vertices.size();
		load();
		material = material2;
	}
	void operator=(const TerrainPatch &other)
	{
		count = other.count;
		vertices = other.vertices;
		material = other.material;
		load();

		
	}
	TerrainPatch(const TerrainPatch &other) :vertices(other.vertices)
	{
		material = other.material;
		count = other.count;
		load();
		
	}
	
	~TerrainPatch()
	{
		glDeleteBuffers(1, &vab);
		glDeleteVertexArrays(1, &vao);
	}
};

class Terrain
{
public:
	Terrain(std::string Path,std::string Texture,Vector3 Scale,bool Center = false,int NumPatches = 2);
	~Terrain(void);
	void render(Shader *Shader = NULL);
	
	Material* getMaterial() {return &material;}
	Transform* getTransform(){return &transform;};
	void loadTerrain();
	void calculateNormalMap();
	void calculateHeightMap(std::string Path);
	void calculateVertices(std::vector<std::vector<int>> &heightmap, std::vector<std::vector<Vector3>> &normalMap, std::vector<Vertex> &vertices);
	std::string getPath(){return path;}
	float getHeight(float X,float Z);
	void resizeTerrain(Vector3 Scale);
	bool isCentered(){return centered;}
	void setTransform(Transform* Transform){transform = *Transform;};



	///////////////////////////////////////////////////////////
	//TODO IMPORTANT REPLACE PIXELWIDTH,PIXELHEIGHT WITH TRANSFORM SCALE
private: 
	int width,height,numComponents,count;
	TerrainIndex* Index;
	std::vector<TerrainPatch> patches;
	Material material;
	Transform transform;
	Shader *shader;
	std::string path;
	bool success;
	std::vector<std::vector<int>> heightMap;
	std::vector<std::vector<Vector3>> normalMap;
	int extension;
	bool centered ;
	int numPatches;
};

