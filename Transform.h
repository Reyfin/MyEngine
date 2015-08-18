#pragma once

#include "Math/3DMath.h"
#include "Shader.h"
class Transform
{
public:
	Transform(const Vector3 &pos = Vector3() ,const Vector3 &rot = Vector3(),const Vector3 &scale = Vector3(1.0f,1.0f,1.0f));
	~Transform(void);
	
	Matrix4 modelMatrix;
	Vector3 getPos(){return pos;};
	Vector3 getRot(){return rot;};
	Vector3 getScale(){return sca;};
	//check if the transform has changed
	//will be turned to false once getMatrix() is called
	bool hasUpdate;
	void setPos(Vector3& Pos);
	void setRot(Vector3& Rot);
	void setScale(Vector3& Scale);
	/*
		returns modelMatrix
	*/
	Matrix4 getMatrix();
	/*
		param shader the shader which is used for rendering
		Will update the modelMatrix in the shader
	*/
	void update(Shader* shader){shader->setUniform("modelMatrix",getMatrix());};
	void calculateMatrix();
	bool needsUpdate(){return hasUpdate;}
private:
	Vector3 pos;
	Vector3 rot;
	Vector3 sca;
};

