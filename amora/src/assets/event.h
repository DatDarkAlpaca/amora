#pragma once

typedef enum event_type
{
	EVENT_NONE		= 0,
	EVENT_ENEMY		= 1 << 0,
	EVENT_COME_CU	= 1 << 1,
	EVENT_MAX = 3
} event_type;

typedef struct event
{
	const char* eventName;
	event_type type;
} event;

event generate_random_event();

const char* get_event_name(event_type event);