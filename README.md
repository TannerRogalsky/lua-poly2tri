lua-poly2tri
===

This is a Lua wrapper around [poly2line](http://sites-final.uclouvain.be/mema/Poly2Tri/). It provides fast, stable Constrained Delauney Triangulation of convex or concave polygons with or without holes. It has been tested with Lua 5.1 and LuaJIT but should be able to be built against newer version of Lua as well.

This is a continuation and expansion of peete-q's [lua-polygon](https://github.com/peete-q/lua-polygon) work.

# Usage

Download or compile the appropriate binary for your system.

```Lua
-- require the module
local poly2tri = assert(package.loadlib(PATH_TO_BINARY, 'luaopen_poly2tri'))()

local vertices = {0, 0, 0, 200, 200, 200, 200, 0}
local holes = {
  {10, 10, 50, 10, 10, 50},
  {100, 10, 175, 10, 175, 100, 100, 50, 10, 100},
  {10, 175, 150, 100, 190, 175}
}
local triangles = poly2tri.triangulate(verts, holes)
```

The output will be a table where each entry is a table consisting of 6 numbers (3 vertices).

# Compile

The dependencies for this project are very minimal:

- Lua 5.1
- CMake >= 2.8

Then clone this project and it's submodule. `git submodule update --init --recursive`

### Linux && OSX

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Windows
Use Powershell or your favourite terminal emulator.
You also need MSVC installed but you almost certainly already have it.

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```
