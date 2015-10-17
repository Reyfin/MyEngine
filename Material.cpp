#include "Material.h"


Material::Material(std::string path,std::string normalPath,Vector3 Color,float intensity ,float power,bool fromCache)
{
	if(fromCache)
	{
		texture = TextureCache::getTexture(path);
		normalMap = NormalCache::getTexture(normalPath);
	}
	else
	{
		texture = TextureLoader::load(path);
		normalMap = TextureLoader::loadNormal(normalPath);
	}
	isCached = fromCache;
	color=Color;
	specularIntensity=intensity;
	specularPower= power;
}


Material::~Material(void)
{
	if(isCached) TextureCache::lowerCount(texture.texturepath);
}

void Material::update(Shader *shader)
{
	
		texture.bind();
		shader->setUniform("Texture",0);
		normalMap.bind(1);
		shader->setUniform("normalMap",1);
		shader->setUniform("specularIntensity",specularIntensity);
		shader->setUniform("specularPower",specularPower);
		shader->setbaseColor(color);
}