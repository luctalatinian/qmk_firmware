#include QMK_KEYBOARD_H

#include "ltimer.h"

#include "lcol.h"

static ltimer_record* ltimer_record_new(ltimer_callback fn, uint32_t interval);
static void run_timers(lcol_node *n, void *userdata);

lcol_list *timers;
int next_id = 0;

void ltimer_init()
{
    timers = lcol_list_new();
}

void ltimer_select()
{
    lcol_list_foreach(timers, run_timers, (void*)timer_read32());
}

int ltimer_set_interval(ltimer_callback fn, uint32_t interval)
{
    ltimer_record *r = ltimer_record_new(fn, interval);
    lcol_list_push(timers, r);

    return r->id;
}

void ltimer_clear_interval(int timer_id)
{
    // TODO
}

static ltimer_record* ltimer_record_new(ltimer_callback fn, uint32_t interval)
{
    ltimer_record *r = malloc(sizeof(ltimer_record));
    r->id = next_id++;
    r->fn = fn;
    r->userdata = NULL;
    r->interval = interval;
    r->last_executed = timer_read32();

    return r;
}

static void run_timers(lcol_node *n, void *userdata)
{
    uint32_t now = (uint32_t)userdata;
    ltimer_record *record = (ltimer_record*)n->data;

    if (now - record->last_executed >= record->interval)
    {
        record->fn();
        record->last_executed = now;
    }
}
