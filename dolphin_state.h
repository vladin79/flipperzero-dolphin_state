#ifndef DOLPHIN_STATE
#define DOLPHIN_STATE

#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/widget.h>
#include <gui/modules/popup.h>
#include <notification/notification.h>
#include <dolphin/dolphin.h>

/* ------------------------------------------------------------------------------------------------------------------ */
/* Definitions                                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

/* Application name */
#define APP_NAME "Dolphin State"

/* Application version */
#define APP_VER "v1.1"

/* Text buffer size */
#define BUFF_SIZE 32

/* Main application structure */
typedef struct _DolphinState
{
    /* Screen */
    Gui* gui;
    ViewDispatcher* view_dispatcher;

    /* Dolphin */
    Dolphin* dolphin;

    /* Text buffer */
    char* cBuff;
} DolphinState;

enum DolphinStateViews
{
    VIEW_MENU,
    VIEW_WIDGET
};

typedef struct
{
    uint8_t icounter_daily_limit[DolphinAppMAX];
    uint8_t butthurt_daily_limit;

    uint32_t flags;
    uint32_t icounter;
    int32_t butthurt;
    uint64_t timestamp;
} DolphinStoreData;

struct DolphinState
{
    DolphinStoreData data;
    bool dirty;
};

struct Dolphin
{
    struct DolphinState* state;
    FuriPubSub* pubsub;
    FuriMessageQueue* event_queue;
    FuriEventLoop* event_loop;
    FuriEventLoopTimer* butthurt_timer;
    FuriEventLoopTimer* flush_timer;
    FuriEventLoopTimer* clear_limits_timer;
};

/* ------------------------------------------------------------------------------------------------------------------ */
/* Global Data                                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

extern DolphinState* app;

/* ------------------------------------------------------------------------------------------------------------------ */
/* Public Function Declarations                                                                                       */
/* ------------------------------------------------------------------------------------------------------------------ */

bool reset_limits(void);

#endif
