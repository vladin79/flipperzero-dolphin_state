#include "dolphin_state.h"
#include "passport.h"

static uint32_t previous_callback(void* context);
static void draw_widget(void);

static Widget* widget;
static View* view;

void widget_view_alloc(void)
{
    widget = widget_alloc();
    view = widget_get_view(widget);

    view_set_previous_callback(view, previous_callback);

    view_dispatcher_add_view(app->view_dispatcher, VIEW_WIDGET, view);
}

void widget_view_free(void)
{
    view_dispatcher_remove_view(app->view_dispatcher, VIEW_WIDGET);
    widget_free(widget);
}

void widget_view_switch(void)
{
    draw_widget();

    view_dispatcher_switch_to_view(app->view_dispatcher, VIEW_WIDGET);
}

static uint32_t previous_callback(void* context)
{
    UNUSED(context);

    view_dispatcher_stop(app->view_dispatcher);

    return VIEW_IGNORE;
}

static void draw_widget(void)
{
    char buff[128];

    /* Clear widget */
    widget_reset(widget);

    widget_add_frame_element(widget, 0, 0, 128, 63, 7);
    widget_add_frame_element(widget, 0, 0, 128, 64, 7);

    widget_add_text_box_element(
        widget, 0, 4, 128, 12, AlignCenter, AlignCenter, "\e#Dolphin state", false);

    widget_add_text_scroll_element(
        widget,
        4,
        16,
        121,
        44,
        "\e#Dolphin Store Data\n"
        "DolphinAppSubGHz:\n"
        "DolphinAppRfid:\n"
        "DolphinAppNfc:\n"
        "DolphinAppIr:\n"
        "DolphinAppIbutton:\n"
        "DolphinAppBadUSB:\n"
        "DolphinAppPlugin:\n"
        "ButthurtDailyLimit:\n"
        //"\n"
        "Flags:\n"
        "Icounter:\n"
        "Butthurt:\n"
        "Timestamp:\n"
        "\n"
        "\e#Passport\n"
        "Level:\n"
        "Mood:\n"
        "Percent complete:");

    snprintf(
        buff,
        128,
        "\e#\n"
        "\er%d\n" // DolphinAppSubGHz
        "\er%d\n" // DolphinAppRfid
        "\er%d\n" // DolphinAppNfc
        "\er%d\n" // DolphinAppIr
        "\er%d\n" // DolphinAppIbutton
        "\er%d\n" // DolphinAppBadUSB
        "\er%d\n" // DolphinAppPlugin
        "\er%d\n" // ButthurtDailyLimit
        "\er%ld\n" // Flags
        "\er%ld\n" // Icounter
        "\er%ld\n" // Butthurt
        "\er%lld\n" // Timestamp
        "\er(%s)\n"
        "\e#\n"
        "\er%d\n" // Level
        "\er%s\n" // Mood
        "\er%.2f%%", // Percent complete
        app->dolphin->state->data.icounter_daily_limit[0],
        app->dolphin->state->data.icounter_daily_limit[1],
        app->dolphin->state->data.icounter_daily_limit[2],
        app->dolphin->state->data.icounter_daily_limit[3],
        app->dolphin->state->data.icounter_daily_limit[4],
        app->dolphin->state->data.icounter_daily_limit[5],
        app->dolphin->state->data.icounter_daily_limit[6],
        app->dolphin->state->data.butthurt_daily_limit,
        app->dolphin->state->data.flags,
        app->dolphin->state->data.icounter,
        app->dolphin->state->data.butthurt,
        app->dolphin->state->data.timestamp,
        timestamp_to_datetime_string(),
        passport_level(),
        passport_mood(),
        (double)passport_complete());

    widget_add_text_scroll_element(widget, 4, 16, 121, 44, buff);
}
