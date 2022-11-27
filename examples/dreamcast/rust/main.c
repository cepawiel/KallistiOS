#include <kos.h>
#include <stdbool.h>

KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS );

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

void print_header() {
    printf("Starting Rust Program!\n");
}

pvr_init_params_t params = {     
    /* Enable opaque and translucent polygons with size 16 */
    { PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_0 },

    /* Vertex buffer size 512K */
    512 * 1024
};

bool start_pvr() {
    printf("Initializing PVR\n");
    return pvr_init(&params);
}

/* Floating-point Sin/Cos; 256 angles, -1.0 to 1.0 */
#include "sintab.h"
#define msin(angle) sintab[angle]
#define mcos(angle) sintab[((angle)+64) % 256]

/********************************************************************/
/* Draws some nifty 3D cubes on the screen */

void send_pvr_prim(int cp, float xt, float yt, float z, float ztrans) {
    float a, r, g, b;
    pvr_vertex_t vert;

    if((cp % 12) == 9)
        vert.flags = PVR_CMD_VERTEX_EOL;
    else
        vert.flags = PVR_CMD_VERTEX;

    vert.x = xt + 320.0f;
    vert.y = yt + 240.0f;
    vert.z = 128.0 - (z / 64.0);
    a = 0.8f;

    if(ztrans == 0) ztrans++;

    switch((cp % 4)) {
        case 0:
            r = 192.0f / ztrans;
            g = 0.0f;
            b = 0.0f;
            break;
        case 1:
            r = 0.0f;
            g = 192.0f / ztrans;
            b = 0.0f;
            break;
        case 2:
            r = 0.0f;
            g = 0.0f;
            b = 192.0f / ztrans;
            break;
        case 3:
            r = 192.0f / ztrans;
            g = 192.0f / ztrans;
            b = 0.0f;
            break;
        default:
            // assert(0);
            break;
    }


#define bound(A) if ((A) < 0.0f) (A) = 0.0f; if ((A) > 1.0f) (A) = 1.0f;
    bound(r);
    bound(g);
    bound(b);
#undef bound
    vert.argb = PVR_PACK_COLOR(a, r, g, b);
    vert.oargb = 0;
    vert.u = vert.v = 0.0f;

    pvr_prim(&vert, sizeof(vert));
}

int rotang = 0;

int cubes_have_header = 0;
pvr_poly_hdr_t cubes_header;

void cubes_one_frame() {
    pvr_poly_cxt_t tmp;

    if(!cubes_have_header) {
        pvr_poly_cxt_col(&tmp, PVR_LIST_TR_POLY);
        pvr_poly_compile(&cubes_header, &tmp);
        cubes_have_header = 1;
    }

    /* Send polygon header to the TA using store queues */
    pvr_prim(&cubes_header, sizeof(cubes_header));

    /* Draw cubes */
    cube_one_frame();
}

int pvr_list_begin_tr() {
    return pvr_list_begin(PVR_LIST_TR_POLY);
}
