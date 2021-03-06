#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "j1Collision.h"
#include "j1App.h"
#include "j1Textures.h"

enum class ENTITY_TYPE;
enum class ENEMY_TYPE;

struct ColliderData {
	p2List<Collider*>			collider_list;

	~ColliderData() {
		for (int i = 0; i < collider_list.count(); ++i) {
			if (collider_list[i] != nullptr /*&& collider_list[i]->to_delete ==false*/)
				collider_list[i]->to_delete=true;
		}
	}
};

// ----------------------------------------------------
struct MapLayer
{
	p2SString	name;
	int			width;
	int			height;
	uint*		data;
	float		parallax=1.0f;
	float		scale = 1.0f;
	bool		visible = true;
	int			navigation=0;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	inline uint Get(int x, int y) const
	{
		return data[(y*width) + x];
	}
};

// ----------------------------------------------------
struct TileSet
{
	SDL_Rect GetTileRect(int id) const;

	p2SString			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;

	~TileSet() { App->tex->UnLoad(texture); }
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	p2List<TileSet*>	tilesets;
	p2List<MapLayer*>	layers;
	ColliderData		colliders;
	iPoint				start_position = {0,0};
	int                 wincondition = 100000;  // Large number so the player doesn't get there if we don't give it a value

};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);
  
	//Tile coordinates to pixel coordinates
	iPoint MapToWorld(int x, int y) const;

	//Pixel coordinates to tile coordinates
	iPoint WorldToMap(int x, int y) const;

	bool CreateWalkabilityMap(int& width, int& height, uchar** buffer) const;

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	

	//Add colliders
	bool LoadColliders(pugi::xml_node& node, ColliderData* collider, COLLIDER_TYPE collider_type);		


	TileSet* GetTilesetFromTileId(int id) const;

public:

	MapData data;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
	bool showlayer = false;
};

#endif // __j1MAP_H__