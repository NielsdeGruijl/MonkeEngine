#pragma once

#include <iostream>
#include <vector>
#include <functional>

struct Action
{
	Action(std::function<void(void)> pAction, int pId)
	{
		function = pAction;
		id = pId;
	}

	bool operator==(const Action action)
	{
		if (id == action.id)
		{
			return true;
		}
		return false;
	}

	std::function<void()> function;
	int id;
};

class Event
{
public:
	void Subscribe(const std::function<void()> pFunction);
	void Unsubscribe(const std::function<void(void)> pFunction);

	void ClearSubscribers();

	void Invoke();

private:
	std::vector<Action> actions;
};