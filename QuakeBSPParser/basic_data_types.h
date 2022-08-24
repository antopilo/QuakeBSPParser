#pragma once
typedef float scalar_t;        // Scalar value,

typedef struct                 // Vector or Position
{
	scalar_t x;                  // horizontal
	scalar_t y;                  // horizontal
	scalar_t z;                  // vertical
} vec3_t;

typedef struct                 // Bounding Box, Float values
{
	vec3_t   min;                // minimum values of X,Y,Z
	vec3_t   max;                // maximum values of X,Y,Z
} boundbox_t;

typedef struct                 // Bounding Box, Short values
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
	unsigned short vertex0;             // index of the start vertex
								//  must be in [0,numvertices[
	unsigned short vertex1;             // index of the end vertex
								 //  must be in [0,numvertices[
} edge_t;

typedef struct
{
	vec3_t   vectorS;            // S vector, horizontal in texture space)
	scalar_t distS;              // horizontal offset in texture space
	vec3_t   vectorT;            // T vector, vertical in texture space
	scalar_t distT;              // vertical offset in texture space
	unsigned long   texture_id;         // Index of Mip Texture
								 //           must be in [0,numtex[
	unsigned long   animated;           // 0 for ordinary textures, 1 for water 
} surface_t;

typedef struct
{
	unsigned short plane_id;            // The plane in which the face lies
								//           must be in [0,numplanes[ 
	unsigned short side;                // 0 if in front of the plane, 1 if behind the plane
	long ledge_id;               // first edge in the List of edges
								 //           must be in [0,numledges[
	unsigned short ledge_num;           // number of edges in the List of edges
	unsigned short texinfo_id;          // index of the Texture info the face is part of
								 //           must be in [0,numtexinfos[ 
	unsigned char typelight;            // type of lighting, for the face
	unsigned char baselight;            // from 0xFF (dark) to 0 (bright)
	unsigned char light[2];             // two additional light models  
	long lightmap;               // Pointer inside the general light map, or -1
								 // this define the start of the face light map
} face_t;

typedef struct
{
	vec3_t normal;               // Vector orthogonal to plane (Nx,Ny,Nz)
								// with Nx2+Ny2+Nz2 = 1
	scalar_t dist;               // Offset to plane, along the normal vector.
								 // Distance from (0,0,0) to the plane
	long    type;                // Type of plane, depending on normal vector.
} plane_t;

typedef struct                 // Mip texture list header
{
	long numtex;                 // Number of textures in Mip Texture list
	long* offset;         // Offset to each of the individual texture
} mipheader_t;                 //  from the beginning of mipheader_t

typedef struct                 // Mip Texture
{
	char   name[16];             // Name of the texture.
	unsigned long width;                // width of picture, must be a multiple of 8
	unsigned long height;               // height of picture, must be a multiple of 8
	unsigned long offset1;              // offset to u_char Pix[width   * height]
	unsigned long offset2;              // offset to u_char Pix[width/2 * height/2]
	unsigned long offset4;              // offset to u_char Pix[width/4 * height/4]
	unsigned long offset8;              // offset to u_char Pix[width/8 * height/8]
} miptex_t;