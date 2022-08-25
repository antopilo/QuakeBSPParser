# Quake BSP Parser
A C++ single-file header-only BSP parsing library.

It's extremely easy to setup. Just include the header file in your code.

The file specification can be found here: [https://www.gamers.org/dEngine/quake/spec/quake-spec34/qkspec_4.htm#BL2]

## Simple example
```cpp
#include "BSPParser.h"

void main()
{
    BSPParser::LoadFile("myBsp.bsp");

    // You can parse the whole file.
    if(BSPParser::Parse())
    {
        auto planes = BSPParser::Planes;
        auto mips = BSPParser::MipTextures;
        auto edges = BSPParser::Edges;
        auto faces = BSPParser::Faces;
        auto models = BSPParser::Models;
    }

    // or you can parse specific data.
    BSPParser::ParseVertices();
    auto vertices = BSPParser::Vertices;

    BSPParser::UnloadFile();
}
```
