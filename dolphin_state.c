#include <furi.h>
#include <saved_struct.h>

#include "views/widget_view.h"
#include "views/menu_view.h"
#include "dolphin_state.h"

/* ------------------------------------------------------------------------------------------------------------------ */
/* Definitions                                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

#define DOLPHIN_STATE_PATH           "/int/.dolphin.state"
#define DOLPHIN_STATE_HEADER_MAGIC   0xD0
#define DOLPHIN_STATE_HEADER_VERSION 0x01

/* ------------------------------------------------------------------------------------------------------------------ */
/* Global variables and constants                                                                                     */
/* ------------------------------------------------------------------------------------------------------------------ */

/* Application data*/
DolphinState* app;

/* ------------------------------------------------------------------------------------------------------------------ */
/* Local function declarations                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

static void dolphin_state_alloc(void);
static void dolphin_state_free(void);

/* ------------------------------------------------------------------------------------------------------------------ */
/* Public function definitions                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

int32_t dolphin_state_app(void* p)
{
    UNUSED(p);

    /* Application memory allocation */
    dolphin_state_alloc();

    menu_view_switch();

    view_dispatcher_run(app->view_dispatcher);

    /* Freeing memory */
    dolphin_state_free();

    return 0;
}

bool reset_limits(void)
{
    bool result;
    int i;

    for (i = 0; i < DolphinAppMAX; i++)
    {
        app->dolphin->state->data.icounter_daily_limit[i] = 0;
    }

    app->dolphin->state->data.butthurt_daily_limit = 0;

    result = saved_struct_save(
        DOLPHIN_STATE_PATH,
        &app->dolphin->state->data,
        sizeof(DolphinStoreData),
        DOLPHIN_STATE_HEADER_MAGIC,
        DOLPHIN_STATE_HEADER_VERSION);

    if (result)
    {
        app->dolphin->state->dirty = false;
    }

    return result;
}

/* ------------------------------------------------------------------------------------------------------------------ */
/* Static function definitions                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

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

    menu_view_alloc();
    widget_view_alloc();

    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);
}

/**
 * @brief Freeing memory after application running
 */
static void dolphin_state_free(void)
{
    widget_view_free();
    menu_view_free();

    free(app->cBuff);

    view_dispatcher_free(app->view_dispatcher);
    furi_record_close(RECORD_GUI);

    furi_record_close(RECORD_DOLPHIN);

    free(app);
}
