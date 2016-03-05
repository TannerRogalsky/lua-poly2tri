#include <vector>

#include "lua.hpp"
#include "poly2tri.h"

#include "lua-poly2tri.h"

#define luaL_check(c, ...)    if (!(c)) luaL_error(L, __VA_ARGS__)

static int api_triangulate(lua_State *L) {
  luaL_check(lua_gettop(L) == 2, "Pass two tables: vertices and holes.");

  luaL_check(lua_istable(L, 1) == 1, "First arg must be a table of vertices.");
  luaL_check(lua_istable(L, 2) == 1, "Second arg must be a table of holes.");

  size_t vertexcount = lua_objlen(L, 1);
  luaL_check(vertexcount >= 6, "Only got %d vertices. Pass at least 6.", vertexcount);
  luaL_check(vertexcount % 2 == 0, "Pass an even number of vertices. Got %d.", vertexcount);
  std::vector<p2t::Point*> verts;
  verts.reserve(vertexcount / 2);
  lua_pushnil(L);
  while (lua_next(L, 1) != 0) {
    double x = (double) lua_tonumber(L, -1);
    lua_pop(L, 1);
    lua_next(L, 1);
    double y = (double) lua_tonumber(L, -1);
    lua_pop(L, 1);

    verts.push_back(new p2t::Point(x, y));
  }

  p2t::CDT* cdt = new p2t::CDT(verts);

  lua_pushnil(L);
  while (lua_next(L, 2) != 0) {
    lua_pushnil(L);

    luaL_check(lua_istable(L, -2) == 1, "Each hole must be a table of vertices.");
    size_t holevertexcount = lua_objlen(L, -2);
    luaL_check(holevertexcount >= 6, "Only got %d vertices for a hole. Pass at least 6.", holevertexcount);
    luaL_check(holevertexcount % 2 == 0, "Pass an even number of vertices for a hole. Got %d.", holevertexcount);
    std::vector<p2t::Point*> hole;
    hole.reserve(holevertexcount);

    while (lua_next(L, -2) != 0) {
      double x = (double) lua_tonumber(L, -1);
      lua_pop(L, 1);
      lua_next(L, -2);
      double y = (double) lua_tonumber(L, -1);
      lua_pop(L, 1);

      hole.push_back(new p2t::Point(x, y));
    }
    cdt->AddHole(hole);

    lua_pop(L, 1);
  }

  cdt->Triangulate();
  std::vector<p2t::Triangle*> tris = cdt->GetTriangles();
  lua_createtable(L, tris.size(), 0);
  for (size_t i = 0; i < tris.size(); ++i)
  {
    lua_createtable(L, 6, 0);

    lua_pushnumber(L, tris[i]->GetPoint(0)->x);
    lua_rawseti(L, -2, 1);
    lua_pushnumber(L, tris[i]->GetPoint(0)->y);
    lua_rawseti(L, -2, 2);
    lua_pushnumber(L, tris[i]->GetPoint(1)->x);
    lua_rawseti(L, -2, 3);
    lua_pushnumber(L, tris[i]->GetPoint(1)->y);
    lua_rawseti(L, -2, 4);
    lua_pushnumber(L, tris[i]->GetPoint(2)->x);
    lua_rawseti(L, -2, 5);
    lua_pushnumber(L, tris[i]->GetPoint(2)->y);
    lua_rawseti(L, -2, 6);

    lua_rawseti(L, -2, i + 1);
  }
  for (size_t i = 0; i < verts.size(); ++i)
    delete verts[i];
  delete cdt;
  return 1;
}

static const struct luaL_Reg thislib[] = {
  {"triangulate", api_triangulate},
  {NULL, NULL}
};

extern "C" {
#ifdef _WINDOWS
  int __declspec(dllexport) luaopen_poly2tri (lua_State *L);
#else
  LUALIB_API int luaopen_poly2tri (lua_State *L);
#endif
}

LUALIB_API int luaopen_poly2tri(lua_State * L) {
  lua_newtable(L);

  for (int i = 0; thislib[i].name != NULL; ++i)
  {
    luaL_Reg l = thislib[i];
    lua_pushcfunction(L, l.func);
    lua_setfield(L, -2, l.name);
  }

  lua_pushstring(L, "VERSION_MAJOR");
  lua_pushnumber(L, VERSION_MAJOR);
  lua_settable(L, -3);

  lua_pushstring(L, "VERSION_MINOR");
  lua_pushnumber(L, VERSION_MINOR);
  lua_settable(L, -3);

  lua_pushstring(L, "AUTHOR");
  lua_pushstring(L, AUTHOR);
  lua_settable(L, -3);

  return 1;
}
