#pragma once
#include <functional>
#include <cstdarg>
#include "AbstractCommand.h"

class FunctionCommand : public AbstractCommand
{
public:
	inline FunctionCommand(std::function<void()> callback) {
		this->commandIdentifier = new UniqueCommandIdentifier(nullptr, nullptr, callback);
	};
	~FunctionCommand() {}
	inline virtual int execute(...) {
		(this->commandIdentifier->functionPointer)(...);
		return 0;
	};
	inline virtual bool compareCommandsIdentifier(UniqueCommandIdentifier* commandIdentifier) { return (commandIdentifier->functionPointer == this->commandIdentifier->functionPointer); };
private:
};

