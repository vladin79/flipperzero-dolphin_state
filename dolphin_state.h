#ifndef DOLPHIN_STATE
#define DOLPHIN_STATE

#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/widget.h>
#include <gui/modules/popup.h>
#include <notification/notification.h>
#include <dolphin/dolphin.h>

/* Text buffer size */
#define BUFF_SIZE 32

//typedef struct DolphinState DolphinState;

/* Main application structure */
typedef struct _DolphinState
{
    /* Screen */
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    //    NotificationApp* notifications;
    //    Widget* widget;
    //    Popup* popup;

    /* Dolphin */
    Dolphin* dolphin;

    /* Text buffer */
    char* cBuff;
} DolphinState;

typedef enum _DolphinStateViews
{
    VIEW_GENERAL,
    VIEW_WIDGET,
    VIEW_POPUP,
    VIEWS_COUNT
} DolphinStateViews;

#if 1
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
#endif

#if 1
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
#endif

extern DolphinState* app;

#endif
