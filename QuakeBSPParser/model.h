#pragma once
#include "basic_data_types.h"

typedef struct
{
	boundbox_t bound;            // The bounding box of the Model
	vec3_t origin;               // origin of model, usually (0,0,0)
	long node_id0;               // index of first BSP node
	long node_id1;               // index of the first Clip node
	long node_id2;               // index of the second Clip node
	long node_id3;               // usually zero
	long numleafs;               // number of BSP leaves
	long face_id;                // index of Faces
	long face_num;               // number of Faces
} model_t;