#include <vector>

#include "lua.hpp"
#include "poly2tri.h"

#define luaL_check(c, ...)    if (!(c)) luaL_error(L, __VA_ARGS__)

static int api_triangulate(lua_State *L)
{
  int args = lua_gettop(L);
  luaL_check(args >= 6, "Pass at least 3 vertices to triangulate.", args);
  return 1;
}

static const struct luaL_Reg thislib[] = {
  {"triangulate", api_triangulate},
  {NULL, NULL}
};

extern "C" {
  LUALIB_API int luaopen_poly2tri (lua_State *L);
}

LUALIB_API int luaopen_poly2tri(lua_State * L) {
  lua_newtable(L);

  for (int i = 0; thislib[i].name != NULL; ++i)
  {
    luaL_Reg l = thislib[i];
    lua_pushcfunction(L, l.func);
    lua_setfield(L, -2, l.name);
  }

  lua_pushstring(L, "VERSION");
  lua_pushstring(L, "1.2");
  lua_settable(L, -3);

  return 1;
}
