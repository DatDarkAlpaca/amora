#pragma once

typedef enum event_type
{
	EVENT_NONE = 0,
	EVENT_ENEMY = 1,
	EVENT_MAX
} event_type;

typedef struct event
{
	event_type type;
} event;

event generate_random_event();