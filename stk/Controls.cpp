#include "Controls.h"


Controls::Controls()
{
	for (int i = 0; i < MAX_FLAGS; i++)
		flags[i] = false;

	for (int i = 0; i < MAX_VALUES; i++)
		values[i] = 0.0;
}
