#pragma once

#include <glew.h>
 
 
#include <GL/GLu.h>
#include <string>
#include "Errors.h"
#include <vector>
#include <fstream>
#include <unordered_map>
#include "Math/3DMath.h"
#include "Shader.h"
#include "FBO.h"
#include "RenderUtil.h"
class ShadowMapFBO //funktioniert irgentwie nicht 
{
    public:
        ShadowMapFBO(unsigned int ShadowWidth, unsigned int ShadowHeight,unsigned int WindowWidth, unsigned int WindowHeight,Vector3 LightDirection,bool enabled);

		~ShadowMapFBO();

        void BindForWriting();
        void BindForReading();
		
		
		Vector3 lightDirection;
		void calculateMatrices();
		void setLightDirection(Vector3 LightDirection);
		void render();

		Matrix4 biasMatrix, depthProjectionMatrix, depthViewMatrix,depthModelMatrix,depthMVP,depthBiasMVP;
        FBO fbo;
		bool isEnabled;
		unsigned int shadowWidth,shadowHeight;
		unsigned int windowWidth,windowHeight;

		//braucht verbesserung
		//irgentwie funktioniert es nicht ein statischen pointer zu haben und den zu initialisieren
		Shader *shader;
private:
		
		
};
