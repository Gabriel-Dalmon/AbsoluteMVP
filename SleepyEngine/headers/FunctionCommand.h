#pragma once
#include "AbstractCommand.h"

class FunctionCommand : public AbstractCommand
{
public:
	inline FunctionCommand(void(*callback)(EventContext context)) {
		this->commandIdentifier = new UniqueCommandIdentifier(nullptr, nullptr, callback);
	};
	~FunctionCommand() {}
	inline virtual int execute(EventContext context) {
		(this->commandIdentifier->functionPointer)(context);
		return 0;
	};
	inline virtual bool compareCommandsIdentifier(UniqueCommandIdentifier* commandIdentifier) { return (commandIdentifier->functionPointer == this->commandIdentifier->functionPointer); };
private:
};

