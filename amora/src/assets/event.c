#include "event.h"
#include "utils/random.h"

event generate_random_event()
{
	event randomEvent;
	randomEvent.type = (event_type)get_rand_int(EVENT_NONE, EVENT_MAX);
	randomEvent.eventName = get_event_name(randomEvent.type);

	return randomEvent;
}

const char* get_event_name(event_type event)
{
	switch (event)
	{
		case EVENT_NONE:		return "NONE";
		case EVENT_ENEMY:		return "ENEMY";
		case EVENT_COME_CU:		return "COME_CU";
		case EVENT_MAX:			return "MAX";
	}

	return "";
}
