#pragma once
#include "AbstractCommand.h"

class FunctionCommand : public AbstractCommand
{
public:
	inline FunctionCommand(void(*callback)(), void* a) {
		this->arg = *((args*)a);

		this->commandIdentifier = new UniqueCommandIdentifier(nullptr, nullptr, callback);
	};
	~FunctionCommand() {}
	inline virtual int execute() {
		(this->commandIdentifier->functionPointer)();
		return 0;
	};
	inline virtual bool compareCommandsIdentifier(UniqueCommandIdentifier* commandIdentifier) { return (commandIdentifier->functionPointer == this->commandIdentifier->functionPointer); };
private:
	template<typename... argTypes>
	//struct args {};
	args arg;
};