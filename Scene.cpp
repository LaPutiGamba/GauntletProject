#include "Scene.h"

Scene::Scene(){
	_reInit = true;
}

Scene::~Scene(){

}

void Scene::Init(){
	_reInit = false;
}

void Scene::ReInit(){
	_reInit = true;
}
