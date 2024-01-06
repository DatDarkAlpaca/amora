#include "event.h"
#include "utils/random.h"

event generate_random_event()
{
	event randomEvent;
	randomEvent.type = (event_type)get_rand_int(EVENT_NONE, EVENT_MAX);

	return randomEvent;
}