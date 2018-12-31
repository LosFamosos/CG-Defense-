#include "Entities.h"

#include "SDL/include/SDL.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1EntityManager.h"
#include "Animation.h"

Entity::Entity(EntityType entity_type): entity_type(entity_type)
{
	position = { 0,0 };

	texture = App->entity_manager->entities_texture;
	
}

bool Entity::CleanUp()
{

	texture = nullptr;

	return true;
}

void Entity::Draw()
{
	App->render->Blit(texture, position.x, position.y, &animation->GetCurrentFrame());
}
