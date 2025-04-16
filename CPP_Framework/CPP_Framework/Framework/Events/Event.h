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

template<typename... Parameters>
struct ParamAction
{
	ParamAction(std::function<void(Parameters...)> pFunction, int pId)
	{
		function = pFunction;
		id = pId;
	}

	bool operator==(const ParamAction action)
	{
		if (id == action.id)
		{
			return true;
		}
		return false;
	}

	std::function<void(Parameters...)> function;
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

template<typename... Parameters>
class ParamEvent
{
public:
	void AddListener(const std::function<void(Parameters...)> pFunction)
	{
		actions.push_back(ParamAction<Parameters...>(pFunction, actions.size()));
	}

	void RemoveListener(const std::function<void(Parameters...)> pFunction)
	{
		for (Action action : actions)
		{
			if (*(long*)(char*)&pFunction == *(long*)(char*)&action.function)
			{
				auto it = std::find(actions.begin(), actions.end(), action);
				actions.erase(it);
			}
		}
	}

	void Invoke(Parameters&... parameters)
	{
		if (actions.size() <= 0)
			return;

		for (ParamAction<Parameters...> action : actions)
		{
			action.function(parameters...);
		}
	}	

private:
	std::vector<ParamAction<Parameters...>> actions;
};