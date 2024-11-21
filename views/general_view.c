#include "dolphin_state.h"

static void _draw_callback(Canvas* canvas, void* _model);
static bool _input_callback(InputEvent* event, void* context);

static View* view;

void general_view_alloc(void)
{
    view = view_alloc();
    view_set_context(view, app);
    view_set_draw_callback(view, _draw_callback);
    view_set_input_callback(view, _input_callback);

    view_dispatcher_add_view(app->view_dispatcher, VIEW_GENERAL, view);
}

void general_view_switch(void)
{
    view_dispatcher_switch_to_view(app->view_dispatcher, VIEW_GENERAL);
}

void general_view_free(void)
{
    view_dispatcher_remove_view(app->view_dispatcher, VIEW_GENERAL);
    view_free(view);
}

static bool _input_callback(InputEvent* event, void* context)
{
    UNUSED(context);

    /* Short press "back" */
    if (event->key == InputKeyBack && event->type == InputTypeShort)
    {
        /* Application end */
        view_dispatcher_stop(app->view_dispatcher);
    }

    /* Short press "OK" */
    if (event->key == InputKeyOk && event->type == InputTypeShort)
    {
        return true;
    }

    /* Short press "down" */
    if (event->key == InputKeyDown && event->type == InputTypeShort)
    {
        return true;
    }

    /* Short press "up" */
    if (event->key == InputKeyUp && event->type == InputTypeShort)
    {
        return true;
    }

    /* Short press "right" */
    if (event->key == InputKeyRight && event->type == InputTypeShort)
    {
        return true;
    }

    /* Short press "left" */
    if (event->key == InputKeyLeft && event->type == InputTypeShort)
    {
        return true;
    }

    /* Long press "OK" */
    if (event->key == InputKeyOk && event->type == InputTypeLong)
    {
        //
    }

    return true;
}

static void _draw_callback(Canvas* canvas, void* _model)
{
    UNUSED(_model);

    /* Draw borders */
    canvas_draw_rframe(canvas, 0, 0, 128, 63, 7);
    canvas_draw_rframe(canvas, 0, 0, 128, 64, 7);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str_aligned(canvas, 63, 10, AlignCenter, AlignCenter, "Dolphin state");
    canvas_set_font(canvas, FontSecondary);
    const uint8_t x = 65, y = 32;
    canvas_draw_rframe(canvas, x - 4, y - 11, 54, 33, 3);
    canvas_draw_rframe(canvas, x - 4, y - 11, 54, 34, 3);
    canvas_draw_str(canvas, x, y, "To exit");
    canvas_draw_str(canvas, x, y + 9, "app press");
    canvas_draw_str(canvas, x, y + 18, "back");

    snprintf(app->cBuff, BUFF_SIZE, "%lu", app->dolphin->state->data.icounter);
    snprintf(app->cBuff, BUFF_SIZE, "%u", app->dolphin->state->data.butthurt_daily_limit);
    //    snprintf(app->cBuff, BUFF_SIZE, "%lu", (uint32_t)100);
    canvas_set_font(canvas, FontBigNumbers);
    canvas_draw_str_aligned(canvas, 30, y, AlignCenter, AlignCenter, app->cBuff);
}
