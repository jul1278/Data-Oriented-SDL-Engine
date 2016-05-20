#ifndef QUIT_APPLICATION_EVENT_ARGS_H
#define QUIT_APPLICATION_EVENT_ARGS_H

#include "IEventArgs.h"

class QuitApplicationEventArgs : public IEventArgs
{
public:

	QuitApplicationEventArgs() {}

	~QuitApplicationEventArgs() {}
};

#endif // QUIT_APPLICATION_EVENT_ARGS_H