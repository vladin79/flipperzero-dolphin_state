#include <datetime.h>

#include "dolphin_state.h"
#include "passport.h"

/* ------------------------------------------------------------------------------------------------------------------ */
/* Definitions                                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

#define LEVEL2_THRESHOLD     300
#define LEVEL3_THRESHOLD     1800
#define MOOD_OK_THRESHOLD    4
#define MOOD_ANGRY_THRESHOLD 9
#define BUTTHURT_MAX         14

enum eMoods
{
    MOOD_HAPPY,
    MOOD_OK,
    MOOD_ANGRY
};

/* ------------------------------------------------------------------------------------------------------------------ */
/* Local variables                                                                                                    */
/* ------------------------------------------------------------------------------------------------------------------ */

static char* moods[] = {"Happy", "Ok", "Angry"};

static char strDatetime[26];

/* ------------------------------------------------------------------------------------------------------------------ */
/* Public function definitions                                                                                        */
/* ------------------------------------------------------------------------------------------------------------------ */

char* timestamp_to_datetime_string(void)
{
    uint32_t timestamp;
    DateTime datetime;

    timestamp = app->dolphin->state->data.timestamp;

    datetime_timestamp_to_datetime(timestamp, &datetime);

    snprintf(
        strDatetime,
        26,
        "%4d-%02d-%02d %02d:%02d:%02d",
        datetime.year,
        datetime.month,
        datetime.day,
        datetime.hour,
        datetime.minute,
        datetime.second);

    return strDatetime;
}

uint8_t passport_level(void)
{
    uint8_t level;
    uint32_t icounter;

    icounter = app->dolphin->state->data.icounter;

    if (icounter >= LEVEL3_THRESHOLD)
    {
        level = 3;
    }
    else if (icounter >= LEVEL2_THRESHOLD)
    {
        level = 2;
    }
    else
    {
        level = 1;
    }

    return level;
}

char* passport_mood(void)
{
    char* mood;
    int32_t butthurt;

    butthurt = app->dolphin->state->data.butthurt;

    if (butthurt <= MOOD_OK_THRESHOLD)
    {
        mood = moods[MOOD_HAPPY];
    }
    else if (butthurt <= MOOD_ANGRY_THRESHOLD)
    {
        mood = moods[MOOD_OK];
    }
    else
    {
        mood = moods[MOOD_ANGRY];
    }

    return mood;
}

float passport_complete(void)
{
    float complete;
    uint32_t icounter;

    icounter = app->dolphin->state->data.icounter;

    if (icounter >= LEVEL3_THRESHOLD)
    {
        complete = 100;
    }
    else if (icounter >= LEVEL2_THRESHOLD)
    {
        complete =
            ((float)(icounter - LEVEL2_THRESHOLD) / (float)(LEVEL3_THRESHOLD - LEVEL2_THRESHOLD)) *
            100;
    }
    else
    {
        complete = ((float)icounter / LEVEL2_THRESHOLD) * 100;
    }

    return complete;
}
