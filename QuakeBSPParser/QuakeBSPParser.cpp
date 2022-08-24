// QuakeBSPParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

#include "header.h"
#include "basic_data_types.h"
 
#include <vector>
#include <cassert>

std::ifstream bspFile;

template<typename T>
void Read(T& data)
{
    bspFile.read((char*)&data, sizeof(T));
}

template<typename T>
void Read(T& data, size_t size)
{
    bspFile.read((char*)&data, sizeof(T) * size);
}


int main()
{
    const std::string filename = "fortress_1_1.bsp";
    bspFile.open(filename, std::ios::out | std::ios::binary);

    if (!bspFile.is_open())
    {
        std::cout << "File not found" << std::endl;
        return -1;
    }

    dheader_t header;
    Read(header);
    if (header.version != 29)
    {
        std::cout << "Wrong bsp version." << std::endl;
        return -1;
    }

    // Planes
    bspFile.seekg(header.planes.offset);
    uint32_t planeAmount = header.planes.size / sizeof(plane_t);
    std::vector<vertex_t> planes(planeAmount);
    Read(planes[0], planeAmount);
    
    // Vertices
    bspFile.seekg(header.vertices.offset);
    const uint32_t vertexAmount = header.vertices.size / sizeof(vertex_t);
    std::vector<vertex_t> vertices(vertexAmount);
    Read(vertices[0], vertexAmount);

    // MIPs
    bspFile.seekg(header.miptex.offset);
    long mipTextureAmount;
    Read(mipTextureAmount);

    // offsets are from mipTextureHeader, not from start of file.
    std::vector<long> mipTextureOffsets(mipTextureAmount);
    Read(mipTextureOffsets[0], mipTextureAmount);

    std::vector<miptex_t> mipTextures(mipTextureAmount);
    for(uint32_t i = 0; i < mipTextureAmount; i++)
    {
        bspFile.seekg(header.miptex.offset + mipTextureOffsets[i]);
        mipTextures.push_back(miptex_t());
        Read(mipTextures[i]);
    }

    // TODO: access pixels of texture.

    // Faces
    bspFile.seekg(header.faces.offset);
    uint32_t faceAmount = header.faces.size / sizeof(face_t);
    std::vector<face_t> faces(faceAmount);
    Read(faces[0], faceAmount);


    std::cout << "Hello World!\n";
}