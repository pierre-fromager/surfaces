/**
 * @file renderer.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief math epression renderer
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACES_RENDERER_
#define _SURFACES_RENDERER_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RENDERER_BC_CMD "echo 'scale=%u;%s' | BC_LINE_LENGTH=0 bc -l"
#define RENDERER_BC_CMD_MAX_LEN 256
#define RENDERER_BC_CHUNK_SIZE 100

int renderer_render_bc(char *expr, char *res, unsigned scale);

#endif // _SURFACES_RENDERER_