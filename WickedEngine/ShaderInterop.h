#ifndef _WICKEDENGINE_SHADERINTEROP_H_
#define _WICKEDENGINE_SHADERINTEROP_H_

// Tiled rendering params:
#define BLOCK_SIZE	16
#define MAX_LIGHTS	1024


// MIP Generator params:
#define GENERATEMIPCHAIN_1D_BLOCK_SIZE 32
#define GENERATEMIPCHAIN_2D_BLOCK_SIZE 16
#define GENERATEMIPCHAIN_3D_BLOCK_SIZE 8

// Skinning compute params:
#define SKINNING_COMPUTE_THREADCOUNT 1024

// Grass culling params:
#define GRASS_CULLING_THREADCOUNT 256

// Bitonic sort params:
#define BITONIC_BLOCK_SIZE 512
#define TRANSPOSE_BLOCK_SIZE 16

#endif
