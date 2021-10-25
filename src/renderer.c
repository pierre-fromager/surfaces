
#include "renderer.h"

static int renderer_bc_execute(char *expr, char *res, unsigned scale)
{
    FILE *ps;
    char bc_cmd[RENDERER_BC_CMD_MAX_LEN];
    char chunk[RENDERER_BC_CHUNK_SIZE];
    snprintf(
        bc_cmd,
        sizeof(char) * RENDERER_BC_CMD_MAX_LEN,
        RENDERER_BC_CMD,
        scale,
        expr);

    ps = popen(bc_cmd, "r");
    if (ps == NULL)
        return -1;
    while (fgets(chunk, RENDERER_BC_CHUNK_SIZE, ps) != NULL)
        strncat(res, chunk, (size_t)sizeof(char *) * RENDERER_BC_CHUNK_SIZE);
    pclose(ps);
    res[strcspn(res, "\n")] = 0;
    return 0;
}

int renderer_render_bc(char *expr, char *res, unsigned scale)
{
    if (-1 == renderer_bc_execute(expr, res, scale))
        return -1;
    return 0;
}
