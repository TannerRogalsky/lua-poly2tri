lua-poly2tri
===

This is a Lua wrapper around [poly2line](http://sites-final.uclouvain.be/mema/Poly2Tri/). It provides fast, stable Constrained Delauney Triangulation of convex or concave polygons with or without holes. It works with Lua 5.1 and LuaJIT.

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

# Limitations
There are limitations based on the underlying poly2tri library.

- If you have a cyclic function that generates random points make sure you don't add the same coordinate twice.
- Polygons must not self-intersect.
- Interior holes must not touch other holes, nor touch the polyline boundary.

It might be useful to clean up your polygon data using something like [clipper](https://luapower.com/clipper).

# Compile

The dependencies for this project are very minimal:

- CMake >= 2.8
- MSVC on Windows

Then clone this project and it's submodule. `git submodule update --init --recursive`

### Linux && OSX

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Windows
Use Powershell or your favourite terminal emulator.

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

# Benchmarks
Benchmarks done using [Nazca Heron](https://github.com/TannerRogalsky/poly2tri/blob/master/testbed/data/nazca_heron.dat) data.

### [Delauney Lua](https://github.com/Yonaba/delaunay)
```
> luajit performance/bench.lua
Test 01: triangulating 1036 points in 240.70 ms
Test 02: triangulating 1036 points in 232.44 ms
Test 03: triangulating 1036 points in 228.36 ms
Test 04: triangulating 1036 points in 222.50 ms
Test 05: triangulating 1036 points in 241.56 ms

> lua5.1 performance/bench.lua
Test 01: triangulating 1036 points in 3426.86 ms
Test 02: triangulating 1036 points in 3445.12 ms
Test 03: triangulating 1036 points in 3378.10 ms
Test 04: triangulating 1036 points in 3415.09 ms
Test 05: triangulating 1036 points in 3438.49 ms
```

### [love.math.triangulate](https://love2d.org/wiki/love.math.triangulate)
```
> love .
Test 01: triangulating 1036 points in 2.42 ms
Test 02: triangulating 1036 points in 2.30 ms
Test 03: triangulating 1036 points in 2.54 ms
Test 04: triangulating 1036 points in 2.37 ms
Test 05: triangulating 1036 points in 2.61 ms
```

### lua-poly2tri
```
> lua5.1 performance/bench.lua
Test 01: triangulating 1036 points in 3.96 ms
Test 02: triangulating 1036 points in 4.79 ms
Test 03: triangulating 1036 points in 6.22 ms
Test 04: triangulating 1036 points in 4.73 ms
Test 05: triangulating 1036 points in 4.31 ms

> luajit performance/bench.lua
Test 01: triangulating 1036 points in 2.85 ms
Test 02: triangulating 1036 points in 3.64 ms
Test 03: triangulating 1036 points in 3.49 ms
Test 04: triangulating 1036 points in 5.73 ms
Test 05: triangulating 1036 points in 3.71 ms
```
