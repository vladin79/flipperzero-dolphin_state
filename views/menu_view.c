#include <gui/modules/variable_item_list.h>

#include "dolphin_state.h"
#include "widget_view.h"

/* ------------------------------------------------------------------------------------------------------------------ */
/* Local variables                                                                                                    */
/* ------------------------------------------------------------------------------------------------------------------ */

static View* view;
static VariableItemList* variable_item_list;

/* ------------------------------------------------------------------------------------------------------------------ */
/* Local function declarations                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

static void enter_callback(void* context, uint32_t index);
static bool navigation_event_callback(void* context);

/* ------------------------------------------------------------------------------------------------------------------ */
/* Public function definitions                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

void menu_view_alloc(void)
{
    variable_item_list = variable_item_list_alloc();

    variable_item_list_reset(variable_item_list);

    variable_item_list_add(variable_item_list, "Dolphin state view", 1, NULL, NULL);
    variable_item_list_add(variable_item_list, "Daily limits reset", 1, NULL, NULL);
    variable_item_list_add(variable_item_list, "About", 1, NULL, NULL);

    variable_item_list_set_enter_callback(variable_item_list, enter_callback, app);

    view = variable_item_list_get_view(variable_item_list);

    view_dispatcher_set_navigation_event_callback(app->view_dispatcher, navigation_event_callback);

    view_dispatcher_add_view(app->view_dispatcher, VIEW_MENU, view);
}

void menu_view_free(void)
{
    variable_item_list_free(variable_item_list);

    view_free(view);

    view_dispatcher_remove_view(app->view_dispatcher, VIEW_MENU);
}

void menu_view_switch(void)
{
    variable_item_list_set_selected_item(variable_item_list, 0);

    view_dispatcher_switch_to_view(app->view_dispatcher, VIEW_MENU);
}

/* ------------------------------------------------------------------------------------------------------------------ */
/* Static function definitions                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

static void enter_callback(void* context, uint32_t index)
{
    UNUSED(context);

    if (index == 0)
    {
        /* Dolphin state view */
        widget_view_switch();
    }

    if (index == 1)
    {
        /* Daily limits reset */
        widget_reset_switch();
    }

    if (index == 2)
    {
        /* About */
        widget_about_switch();
    }
}

static bool navigation_event_callback(void* context)
{
    UNUSED(context);

    /* Return false to stop view dispatcher */

    return false;
}
