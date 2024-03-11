#pragma once

namespace Sleepy {
	class Utils
	{
	public:
		Utils() {};
		~Utils() {};
		inline static bool CheckFlags(int flags, int flagsComparator) { return (flags & flagsComparator); };

	private:

	};
}