#pragma once
#include <string>
#include <fstream>
#include <vector>

namespace BSPParser
{
	// Structs declaration
	typedef struct					// A Directory entry
	{
		long  offset;				// Offset to entry, in bytes, from start of file
		long  size;                 // Size of entry in file, in bytes
	} dentry_t;

	typedef struct					 // The BSP file header
	{
		long  version;               // Model version, must be 0x17 (23).
		dentry_t entities;           // List of Entities.
		dentry_t planes;             // Map Planes.
									 // numplanes = size/sizeof(plane_t)
		dentry_t miptex;             // Wall Textures.
		dentry_t vertices;           // Map Vertices.
									 // numvertices = size/sizeof(vertex_t)
		dentry_t visilist;           // Leaves Visibility lists.
		dentry_t nodes;              // BSP Nodes.
									 // numnodes = size/sizeof(node_t)
		dentry_t texinfo;            // Texture Info for faces.
									 // numtexinfo = size/sizeof(texinfo_t)
		dentry_t faces;              // Faces of each surface.
									 // numfaces = size/sizeof(face_t)
		dentry_t lightmaps;          // Wall Light Maps.
		dentry_t clipnodes;          // clip nodes, for Models.
									 // numclips = size/sizeof(clipnode_t)
		dentry_t leaves;             // BSP Leaves.
									 // numlaves = size/sizeof(leaf_t)
		dentry_t lface;              // List of Faces.
		dentry_t edges;              // Edges of faces.
									 // numedges = Size/sizeof(edge_t)
		dentry_t ledges;             // List of Edges.
		dentry_t models;             // List of Models.
									 // nummodels = Size/sizeof(model_t)
	} dheader_t;

	typedef float scalar_t;	// Scalar value,

	typedef struct					 // Vector or Position
	{
		scalar_t x;                  // horizontal
		scalar_t y;                  // horizontal
		scalar_t z;                  // vertical
	} vec3_t;

	typedef struct					 // Bounding Box, Float values
	{
		vec3_t   min;                // minimum values of X,Y,Z
		vec3_t   max;                // maximum values of X,Y,Z
	} boundbox_t;

	typedef struct					 // Bounding Box, Short values
	{
		short   min;                 // minimum values of X,Y,Z
		short   max;                 // maximum values of X,Y,Z
	} bboxshort_t;

	typedef struct
	{
		float X;                    // X,Y,Z coordinates of the vertex
		float Y;                    // usually some integer value
		float Z;                    // but coded in floating point
	} vertex_t;

	typedef struct
	{
		unsigned short vertex0;     // index of the start vertex
									//  must be in [0,numvertices[
		unsigned short vertex1;     // index of the end vertex
									//  must be in [0,numvertices[
	} edge_t;

	typedef struct
	{
		vec3_t   vectorS;           // S vector, horizontal in texture space)
		scalar_t distS;             // horizontal offset in texture space
		vec3_t   vectorT;           // T vector, vertical in texture space
		scalar_t distT;             // vertical offset in texture space
		unsigned long   texture_id; // Index of Mip Texture
									//  must be in [0,numtex[
		unsigned long   animated;   // 0 for ordinary textures, 1 for water 
	} surface_t;

	typedef struct
	{
		unsigned short plane_id;    // The plane in which the face lies
									//           must be in [0,numplanes[ 
		unsigned short side;        // 0 if in front of the plane, 1 if behind the plane
		long ledge_id;              // first edge in the List of edges
									//           must be in [0,numledges[
		unsigned short ledge_num;   // number of edges in the List of edges
		unsigned short texinfo_id;  // index of the Texture info the face is part of
									//           must be in [0,numtexinfos[ 
		unsigned char typelight;    // type of lighting, for the face
		unsigned char baselight;    // from 0xFF (dark) to 0 (bright)
		unsigned char light[2];     // two additional light models  
		long lightmap;              // Pointer inside the general light map, or -1
									// this define the start of the face light map
	} face_t;

	typedef struct
	{
		vec3_t normal;              // Vector orthogonal to plane (Nx,Ny,Nz)
									// with Nx2+Ny2+Nz2 = 1
		scalar_t dist;              // Offset to plane, along the normal vector.
									// Distance from (0,0,0) to the plane
		long    type;               // Type of plane, depending on normal vector.
	} plane_t;

	typedef struct					// Mip texture list header
	{
		long numtex;                // Number of textures in Mip Texture list
		long* offset;				// Offset to each of the individual texture
	} mipheader_t;					//  from the beginning of mipheader_t

	typedef struct					// Mip Texture
	{
		char   name[16];            // Name of the texture.
		unsigned long width;        // width of picture, must be a multiple of 8
		unsigned long height;       // height of picture, must be a multiple of 8
		unsigned long offset1;      // offset to u_char Pix[width   * height]
		unsigned long offset2;      // offset to u_char Pix[width/2 * height/2]
		unsigned long offset4;      // offset to u_char Pix[width/4 * height/4]
		unsigned long offset8;      // offset to u_char Pix[width/8 * height/8]
	} miptex_t;

	typedef struct
	{
		boundbox_t bound;			// The bounding box of the Model
		vec3_t origin;				// origin of model, usually (0,0,0)
		long node_id0;				// index of first BSP node
		long node_id1;				// index of the first Clip node
		long node_id2;				// index of the second Clip node
		long node_id3;				// usually zero
		long numleafs;				// number of BSP leaves
		long face_id;				// index of Faces
		long face_num;				// number of Faces
	} model_t;

	// Parsed output, access these after calling Parse().
	std::vector<plane_t> Planes;
	std::vector<vertex_t> Vertices;
	std::vector<miptex_t> MipTextures;
	std::vector<face_t> Faces;
	std::vector<edge_t> Edges;
	std::vector<model_t> Models;

	// Private data
	std::ifstream bspFile;
	bool _headerParsed = false;
	dheader_t _header;

	int LoadFile(const std::string& path)
	{
		bspFile.open(path, std::ios::out | std::ios::binary);

		if (!bspFile.is_open())
		{
			return -1;
		}

		return 1;
	}

	void UnloadFile()
	{
		bspFile.close();
	}

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

	inline void Seek(long offset)
	{
		bspFile.seekg(offset);
	}

	void ParseHeader()
	{
		_headerParsed = true;
		Read(_header);
	}

	void ParsePlanes()
	{
		if (!_headerParsed) ParseHeader();
		Seek(_header.planes.offset);
		uint32_t planeAmount = _header.planes.size / sizeof(plane_t);
		Planes = std::vector<plane_t>(planeAmount);
		Read(Planes[0], planeAmount);
	}

	void ParseVertices()
	{
		if (!_headerParsed) ParseHeader();
		Seek(_header.vertices.offset);
		const uint32_t vertexAmount = _header.vertices.size / sizeof(vertex_t);
		Vertices = std::vector<vertex_t>(vertexAmount);
		Read(Vertices[0], vertexAmount);
	}

	void ParseMips()
	{
		if (!_headerParsed) ParseHeader();
		Seek(_header.miptex.offset);
		long mipTextureAmount;
		Read(mipTextureAmount);

		// offsets are from mipTextureHeader, not from start of file.
		std::vector<long> mipTextureOffsets(mipTextureAmount);
		Read(mipTextureOffsets[0], mipTextureAmount);

		MipTextures = std::vector<miptex_t>(mipTextureAmount);
		for (uint32_t i = 0; i < mipTextureAmount; i++)
		{
			bspFile.seekg(_header.miptex.offset + mipTextureOffsets[i]);
			MipTextures.push_back(miptex_t());
			Read(MipTextures[i]);
		}
	}

	void ParseFaces()
	{
		if (!_headerParsed) ParseHeader();
		Seek(_header.faces.offset);
		uint32_t faceAmount = _header.faces.size / sizeof(face_t);
		Faces = std::vector<face_t>(faceAmount);
		Read(Faces[0], faceAmount);
	}

	void ParseEdges()
	{
		if (!_headerParsed) ParseHeader();
		Seek(_header.edges.offset);
		uint32_t edgesAmount = _header.edges.size / sizeof(edge_t);
		Edges = std::vector<edge_t>(edgesAmount);
		Read(Edges[0], edgesAmount);
	}

	void ParseModels()
	{
		if (!_headerParsed) ParseHeader();

		Seek(_header.models.offset);
		uint32_t modelAmount = _header.models.size / sizeof(model_t);
		Models = std::vector<model_t>(modelAmount);
		Read(Models[0], modelAmount);
	}

	void Parse()
	{
		ParseHeader();
		ParsePlanes();
		ParseMips();
		ParseFaces();
		ParseEdges();
		ParseModels();
	}
}