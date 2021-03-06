#ifndef _MAPGEN_SPEC_H_
#define _MAPGEN_SPEC_H_

#include "terrain.h"
#include <istream>
#include <vector>
#include <map>

// MAPGEN_SIZE must be a divisor of SUBMAP_SIZE (specified in map.h)!
// Also, changing MAPGEN_SIZE will break all of the already-written mapgen specs
#define MAPGEN_SIZE 25

struct Terrain_chance
{
  Terrain_chance(int C = 10, Terrain* T = NULL) : chance (C), terrain(T) {};
  int chance;
  Terrain* terrain;
};

struct Variable_terrain
{
public:
  Variable_terrain();
  ~Variable_terrain(){};

  void load_data(std::istream &data, std::string name = "unknown");
  void add_terrain(int chance, Terrain* terrain);
  void add_terrain(Terrain_chance terrain);

  Terrain* pick();

private:
  std::vector<Terrain_chance> ter;
  int total_chance;

};

struct Mapgen_spec
{
  Mapgen_spec();
  ~Mapgen_spec(){};

  bool load_data(std::istream &data);
  Terrain* pick_terrain(int x, int y);

  int uid;
  std::string name;
  std::string terrain_name; // World_terrain we belong to

  std::map<char,Variable_terrain> terrain_defs;
  Variable_terrain base_terrain; // Default terrain

  char terrain[MAPGEN_SIZE][MAPGEN_SIZE]; // Keys to terrain_defs

};

#endif
