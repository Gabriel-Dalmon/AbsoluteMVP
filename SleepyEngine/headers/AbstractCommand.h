#pragma once
#include "EventContext.h"

class VoidClass {};

struct UniqueCommandIdentifier {
	void* methodInstancePointer;
	void(VoidClass::* methodPointer)();
	void(*functionPointer)(EventContext context);

	UniqueCommandIdentifier(void* methodInstancePtr, void (VoidClass::* methodPtr)(), void (*funcPtr)(EventContext context)) {
		methodInstancePointer = methodInstancePtr;
		methodPointer = methodPtr;
		functionPointer = funcPtr;
	}
};

class AbstractCommand
{
	public:
		AbstractCommand() {};
		~AbstractCommand() {};
		virtual int execute(EventContext context) = 0;
		virtual bool compareCommandsIdentifier(UniqueCommandIdentifier* commandIdentifier) = 0;
		UniqueCommandIdentifier* commandIdentifier = nullptr;
};

