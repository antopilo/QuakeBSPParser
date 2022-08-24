#pragma once
typedef struct                 // A Directory entry
{
    long  offset;                // Offset to entry, in bytes, from start of file
    long  size;                  // Size of entry in file, in bytes
} dentry_t;

typedef struct                 // The BSP file header
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