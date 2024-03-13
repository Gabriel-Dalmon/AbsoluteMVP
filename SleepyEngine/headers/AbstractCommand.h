#pragma once
#include <cstdarg>
#include <functional>

class VoidClass {};

struct EventContext {};

struct UniqueCommandIdentifier {
	void* methodInstancePointer;
	void(VoidClass::* methodPointer)();
	std::function<void()> *functionPointer;

	UniqueCommandIdentifier(void* methodInstancePtr, void (VoidClass::* methodPtr)(), std::function<void()> funcPtr) {
		methodInstancePointer = methodInstancePtr;
		methodPointer = methodPtr;
		functionPointer = &funcPtr;
	}
};

class AbstractCommand
{
	public:
		AbstractCommand() {};
		~AbstractCommand() {};
		virtual int execute(/*EventContext* context*/...) = 0;
		virtual bool compareCommandsIdentifier(UniqueCommandIdentifier* commandIdentifier) = 0;
		UniqueCommandIdentifier* commandIdentifier = nullptr;
};

