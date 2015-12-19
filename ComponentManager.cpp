#include "ComponentManager.h"

void ComponentManager::initialize()
{
	graphics.reserve(50);
	collisions.reserve(50);
	directionals.reserve(5);
	collisions.reserve(50);
	skies.reserve(5);
	terrains.reserve(2);
}
void ComponentManager::destroy()
{
	ambients.clear();
	graphics.clear();
	collisions.clear();
	terrains.clear();
	directionals.clear();
	skies.clear();
	for (auto &i = positions.begin(); i != positions.end(); i++)
	{
		for (auto &k = i->second.begin(); k != i->second.end(); k++)
		{
			delete(k->second);
		}
	}
}
void ComponentManager::update()
{
	for (unsigned int i = 0; i < directionals.size(); i++) directionals[i].update();
	for (unsigned int i = 0; i < ambients.size(); i++) ambients[i].update();
	for (unsigned int i = 0; i < graphics.size(); i++) graphics[i].update();
	for (unsigned int i = 0; i < collisions.size(); i++) collisions[i].update();
	for (unsigned int i = 0; i < terrains.size(); i++) terrains[i].update();
}
void ComponentManager::render(Shader* shader, Camera3d* camera)
{
	AmbientLightComponent::setColor(ambients, shader);
	for (unsigned int i = 0; i < skies.size(); i++) skies[i].render(shader, camera);
	for (unsigned int i = 0; i < directionals.size(); i++) directionals[i].render(shader, camera);
	for (unsigned int i = 0; i < graphics.size(); i++) graphics[i].render(shader, camera);
	for (unsigned int i = 0; i < collisions.size(); i++) collisions[i].render(shader, camera);
	for (unsigned int i = 0; i < terrains.size(); i++) terrains[i].render(shader, camera);
}
ComponentPosition* ComponentManager::createGraphics(std::string texturePath, std::string normalMap, std::string ObjectPath, Vector3 color, bool autoCenter)
{
	graphics.emplace_back(texturePath, normalMap, ObjectPath, color, autoCenter);
	ComponentPosition* r = new ComponentPosition(GRAPHICS, graphics.size() - 1);
	positions[GRAPHICS].insert(std::make_pair(r->ID, r));
	return r;
}
ComponentPosition* ComponentManager::createTerrain(std::string Path, std::string Texture, Vector3 Scale, bool Center)
{
	terrains.emplace_back(Path, Texture, Scale, Center);
	ComponentPosition* r = new ComponentPosition(TERRAIN, terrains.size() - 1);
	positions[TERRAIN].insert(std::make_pair(r->ID, r));
	return r;
}
ComponentPosition* ComponentManager::createAmbient(Vector3 Color)
{
	ambients.emplace_back(Color);
	ComponentPosition* r = new ComponentPosition(TERRAIN, ambients.size() - 1);
	positions[AMBIENT].insert(std::make_pair(r->ID, r));
	return r;
}
ComponentPosition* ComponentManager::createDirectional(Vector3 Color, float Intensity, Vector3 Dir)
{
	directionals.emplace_back(BaseLight(Color, Intensity), Dir);
	ComponentPosition* r = new ComponentPosition(DIRECTIONAL, directionals.size() - 1);
	positions[DIRECTIONAL].insert(std::make_pair(r->ID, r));
	return r;
}
ComponentPosition*  ComponentManager::createSkyBox(Vector3 color, std::string Directory, std::string posx, std::string negx, std::string posy, std::string negy, std::string posz, std::string negz)
{
	std::vector<std::string> paths;
	paths.push_back(Directory);
	paths.push_back(posx);
	paths.push_back(negx);
	paths.push_back(posy);
	paths.push_back(negy);
	paths.push_back(posz);
	paths.push_back(negz);
	skies.emplace_back(color, paths);//emplace back only accepts certtain number of variables for whatever reason
	ComponentPosition* r = new ComponentPosition(SKYBOX, skies.size() - 1);
	positions[SKYBOX].insert(std::make_pair(r->ID, r));
	return r;

}
Component* ComponentManager::findComponent(ComponentPosition* Posi)
{
	ComponentPosition &Pos = *Posi;
	switch (Pos.type)
	{
	case GRAPHICS:
	{
		if (Pos.position >= graphics.size()) return NULL;
		return &graphics[Pos.position];
	}break;
	case COLLISIONS:
	{
		if (Pos.position >= collisions.size()) return NULL;
		return &collisions[Pos.position];
	}break;
	case TERRAIN:
	{
		if (Pos.position >= terrains.size()) return NULL;
		return &terrains[Pos.position];
	}break;
	case AMBIENT:
	{
		if (Pos.position >= ambients.size()) return NULL;
		return &ambients[Pos.position];

	}break;
	case DIRECTIONAL:
	{
		if (Pos.position >= directionals.size()) return NULL;
		return &directionals[Pos.position];
	}break;
	case SKYBOX:
	{
		if (Pos.position >= skies.size()) return NULL;
		return &skies[Pos.position];
	}break;
	default:
	{
		return NULL;
	}
	}
}

void ComponentManager::deleteComponent(ComponentPosition* Posi)
{
	ComponentPosition &Pos = *Posi;
	switch (Pos.type)
	{
	case GRAPHICS:
	{
		if (Pos.position >= graphics.size()) return;
		graphics.erase(graphics.begin() + Pos.position);

	}break;
	case COLLISIONS:
	{
		if (Pos.position >= collisions.size()) return;
		collisions.erase(collisions.begin() + Pos.position);
	}break;
	case TERRAIN:
	{
		if (Pos.position >= terrains.size()) return;
		terrains.erase(terrains.begin() + Pos.position);
	}break;
	case AMBIENT:
	{
		if (Pos.position >= ambients.size()) return;
		ambients.erase(ambients.begin() + Pos.position);

	}break;
	case DIRECTIONAL:
	{
		if (Pos.position >= directionals.size()) return;
		directionals.erase(directionals.begin() + Pos.position);
	}break;
	case SKYBOX:
	{
		if (Pos.position >= skies.size()) return;
		skies.erase(skies.begin() + Pos.position);
	}break;
	default:
	{
		return;
	}
	}
	auto r = positions.find(Pos.type);
	for (auto i = r->second.find(Pos.ID); i != r->second.end(); i++)
	{
		i->second->position -= 1;
	}

	r->second.erase(r->second.find(Pos.ID));
}