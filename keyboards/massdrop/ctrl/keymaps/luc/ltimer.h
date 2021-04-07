typedef void (*ltimer_callback) (void);

typedef struct
{
    int id;

    ltimer_callback fn;
    void           *userdata;

    uint32_t interval;
    uint32_t last_executed;

} ltimer_record;

void ltimer_init           (void);

void ltimer_select         (void);

int  ltimer_set_interval   (ltimer_callback fn, uint32_t interval);

void ltimer_clear_interval (int timer_id);
