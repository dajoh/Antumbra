#ifndef STATE_STATE_HPP
#define STATE_STATE_HPP

#include <memory>

namespace Antumbra
{
	typedef std::shared_ptr<class State> StatePtr;

	class State
	{
	public:
		virtual ~State();

		virtual void Update(double dt) = 0;
		virtual void Render(double alpha) = 0;

		virtual StatePtr GetNextState(StatePtr currentState) = 0;
	};
}

#endif