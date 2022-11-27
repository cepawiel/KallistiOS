/* KallistiOS ##version##

   pvrmark.c
   (c)2002 Dan Potter
*/

#include <kos.h>
#include <stdlib.h>
#include <time.h>

pvr_init_params_t pvr_params = {
    { PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_0, PVR_BINSIZE_0, PVR_BINSIZE_0 },
    512 * 1024
};

enum { PHASE_HALVE, PHASE_INCR, PHASE_DECR, PHASE_FINAL };

int polycnt;
int phase = PHASE_HALVE;
float avgfps = -1;

void running_stats() {
    pvr_stats_t stats;
    pvr_get_stats(&stats);

    if(avgfps == -1)
        avgfps = stats.frame_rate;
    else
        avgfps = (avgfps + stats.frame_rate) / 2.0f;
}

void stats() {
    pvr_stats_t stats;

    pvr_get_stats(&stats);
    dbglog(DBG_DEBUG, "3D Stats: %d VBLs, frame rate ~%f fps\n",
           stats.vbl_count, stats.frame_rate);
}


int check_start() {
    maple_device_t *cont;
    cont_state_t *state;

    cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);

    if(cont) {
        state = (cont_state_t *)maple_dev_status(cont);

        if(!state)
            return 0;

        return (state->buttons & CONT_START);
    }
    else
        return 0;
}

pvr_poly_hdr_t hdr;

void setup() {
    pvr_poly_cxt_t cxt;

    pvr_init(&pvr_params);
    pvr_set_bg_color(0, 0, 0);

    pvr_poly_cxt_col(&cxt, PVR_LIST_OP_POLY);
    cxt.gen.shading = PVR_SHADE_FLAT;
    pvr_poly_compile(&hdr, &cxt);
}

void do_frame() {
    pvr_vertex_t vert;
    int x, y, z;
    int size;
    int i, col;

    vid_border_color(0, 0, 0);
    pvr_wait_ready();
    vid_border_color(255, 0, 0);
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_OP_POLY);
    pvr_prim(&hdr, sizeof(hdr));

    for(i = 0; i < polycnt; i++) {
        x = rand() % 640;
        y = rand() % 480;
        z = rand() % 100 + 1;
        size = rand() % 50;
        col = rand() % 256;

        vert.flags = PVR_CMD_VERTEX;
        vert.x = x - size;
        vert.y = y + size;
        vert.z = z;
        vert.u = vert.v = 0.0f;
        vert.argb = col | (col << 8) | (col << 16) | 0xff000000;
        vert.oargb = 0;
        pvr_prim(&vert, sizeof(vert));

        vert.y = y - size;
        pvr_prim(&vert, sizeof(vert));

        vert.flags = PVR_CMD_VERTEX_EOL;
        vert.x = x + size;
        vert.y = y + size;
        pvr_prim(&vert, sizeof(vert));
    }

    pvr_list_finish();
    pvr_scene_finish();
    vid_border_color(0, 255, 0);
}

time_t start_time;
void switch_tests(int ppf) {
    printf("Beginning new test: %d polys per frame (%d per second at 60fps)\n",
           ppf, ppf * 60);
    avgfps = -1;
    polycnt = ppf;
}

void check_switch() {
    time_t now;

    now = time(NULL);

    if(now >= (start_time + 5)) {
        start_time = time(NULL);
        printf("  Average Frame Rate: ~%f fps (%d pps)\n", avgfps, (int)(polycnt * avgfps));

        switch(phase) {
            case PHASE_HALVE:

                if(avgfps < 55) {
                    switch_tests(polycnt / 2);
                }
                else {
                    printf("  Entering PHASE_INCR\n");
                    phase = PHASE_INCR;
                }

                break;
            case PHASE_INCR:

                if(avgfps >= 55) {
                    switch_tests(polycnt + 500);
                }
                else {
                    printf("  Entering PHASE_DECR\n");
                    phase = PHASE_DECR;
                }

                break;
            case PHASE_DECR:

                if(avgfps < 55) {
                    switch_tests(polycnt - 200);
                }
                else {
                    printf("  Entering PHASE_FINAL\n");
                    phase = PHASE_FINAL;
                }

                break;
            case PHASE_FINAL:
                break;
        }
    }
}

int main(int argc, char **argv) {
    setup();

    /* start_time off with something obscene */
    switch_tests(2000000 / 60);
    start_time = time(NULL);

    for(;;) {
        if(check_start())
            break;

        printf(" \r");
        do_frame();
        running_stats();
        check_switch();
    }

    stats();

    return 0;
}


