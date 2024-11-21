#include <furi.h>

#include "views/general_view.h"
#include "views/widget_view.h"
#include "dolphin_state.h"

/* Application data*/
DolphinState* app;

/**
 * @brief Application memory allocation
 */
static void dolphin_state_alloc(void)
{
    /* Application data memory allocation */
    app = malloc(sizeof(DolphinState));

    app->dolphin = furi_record_open(RECORD_DOLPHIN);

    app->gui = furi_record_open(RECORD_GUI);

    app->view_dispatcher = view_dispatcher_alloc();

    app->cBuff = malloc(BUFF_SIZE);

    general_view_alloc();
    widget_view_alloc();

    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);
}

/**
 * @brief Freeing memory after application running
 */
static void dolphin_state_free(void)
{
    widget_view_free();
    general_view_free();

    free(app->cBuff);

    view_dispatcher_free(app->view_dispatcher);
    furi_record_close(RECORD_GUI);

    furi_record_close(RECORD_DOLPHIN);

    free(app);
}

int32_t dolphin_state_app(void* p)
{
    UNUSED(p);

    /* Application memory allocation */
    dolphin_state_alloc();

    // general_view_switch();
    widget_view_switch();

    view_dispatcher_run(app->view_dispatcher);

    /* Freeing memory */
    dolphin_state_free();

    return 0;
}
