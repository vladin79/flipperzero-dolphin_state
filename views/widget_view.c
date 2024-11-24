#include "dolphin_state.h"
#include "passport.h"
#include "menu_view.h"

/* ------------------------------------------------------------------------------------------------------------------ */
/* Definitions                                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

typedef enum _eWidgetView
{
    WIDGET_STATE,
    WIDGET_RESET,
    WIDGET_ABOUT,
    WIDGET_INFO
} eWidgetView;

/* ------------------------------------------------------------------------------------------------------------------ */
/* Local variables                                                                                                    */
/* ------------------------------------------------------------------------------------------------------------------ */

static Widget* widget;
static View* view;
static eWidgetView ubCurrentWidget;

/* ------------------------------------------------------------------------------------------------------------------ */
/* Local function declarations                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

static uint32_t previous_callback(void* context);
static void button_click_callback(GuiButtonType result, InputType type, void* context);
static void draw_view_state(void);
static void draw_reset(void);
static void draw_about(void);
static void draw_info(char* message);

/* ------------------------------------------------------------------------------------------------------------------ */
/* Public function definitions                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

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
    draw_view_state();

    view_dispatcher_switch_to_view(app->view_dispatcher, VIEW_WIDGET);
}

void widget_reset_switch(void)
{
    draw_reset();

    view_dispatcher_switch_to_view(app->view_dispatcher, VIEW_WIDGET);
}

void widget_about_switch(void)
{
    draw_about();

    view_dispatcher_switch_to_view(app->view_dispatcher, VIEW_WIDGET);
}

/* ------------------------------------------------------------------------------------------------------------------ */
/* Static function definitions                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

static uint32_t previous_callback(void* context)
{
    uint32_t result;

    UNUSED(context);

    switch (ubCurrentWidget)
    {
        case WIDGET_STATE:
        case WIDGET_ABOUT:
            result = VIEW_MENU;
            break;
        case WIDGET_RESET:
        case WIDGET_INFO:
        default:
            result = VIEW_WIDGET;
    }

    return result;
}

static void button_click_callback(GuiButtonType result, InputType type, void* context)
{
    UNUSED(context);

    /* Short press left button (Cancel) */
    if (result == GuiButtonTypeLeft && type == InputTypeShort)
    {
        view_dispatcher_switch_to_view(app->view_dispatcher, VIEW_MENU);
    }

    /* Short press right button (Reset) */
    if (result == GuiButtonTypeRight && type == InputTypeShort)
    {
        if (reset_limits())
        {
            draw_info("Daily limits reset.");
        }
        else
        {
            draw_info("Daily limits reset failed!");
        }
    }

    /* Short press center button (Ok) */
    if (result == GuiButtonTypeCenter && type == InputTypeShort)
    {
        menu_view_switch();
    }
}

static void draw_view_state(void)
{
    char buff[128];

    /* Clear widget */
    widget_reset(widget);

    widget_add_frame_element(widget, 0, 0, 128, 63, 7);
    widget_add_frame_element(widget, 0, 0, 128, 64, 7);

    widget_add_text_scroll_element(
        widget,
        4,
        6,
        121,
        52,
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

    widget_add_text_scroll_element(widget, 4, 6, 121, 52, buff);

    ubCurrentWidget = WIDGET_STATE;
}

static void draw_reset(void)
{
    /* Clear widget */
    widget_reset(widget);

    widget_add_button_element(widget, GuiButtonTypeLeft, "Cancel", button_click_callback, app);
    widget_add_button_element(widget, GuiButtonTypeRight, "Reset", button_click_callback, app);

    widget_add_string_element(
        widget, 63, 10, AlignCenter, AlignTop, FontPrimary, "Reset daily limits?");

    ubCurrentWidget = WIDGET_RESET;
}

static void draw_about(void)
{
    /* Clear widget */
    widget_reset(widget);

    widget_add_frame_element(widget, 0, 0, 128, 63, 7);
    widget_add_frame_element(widget, 0, 0, 128, 64, 7);

    snprintf(app->cBuff, BUFF_SIZE, "\e#%s %s", APP_NAME, APP_VER);

    widget_add_text_box_element(
        widget, 0, 4, 128, 12, AlignCenter, AlignCenter, app->cBuff, false);

    widget_add_text_scroll_element(
        widget,
        4,
        16,
        121,
        44,
        "Application for viewing the\nvalues of dolphin state\n\e#Author: vladin79\ngithub.com/vladin79");

    ubCurrentWidget = WIDGET_ABOUT;
}

static void draw_info(char* message)
{
    /* Clear widget */
    widget_reset(widget);

    widget_add_button_element(widget, GuiButtonTypeCenter, "Ok", button_click_callback, app);

    widget_add_string_element(widget, 63, 10, AlignCenter, AlignTop, FontPrimary, message);

    ubCurrentWidget = WIDGET_INFO;
}
