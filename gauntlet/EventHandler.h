#pragma once

#include <functional>
#include <iostream>

//TODO: move implementation to cpp
class EventHandler {
public:
	using Func = std::function<void()>;

private:
	Func _func;

public:
	int id;
	static int counter;

	EventHandler() : id{ 0 } {
	}

	EventHandler(const Func &func) : _func{ func } {
		this->id = ++EventHandler::counter;
	}

	void operator()() {
		this->_func();
	}

	void operator=(const EventHandler &func) {
		if (this->_func == nullptr) {
			this->_func = func;
			this->id = ++EventHandler::counter;
		}
		else {
			// Throw as exception or just log it out.
			std::cerr << "Nope!" << std::endl;
		}
	}

	bool operator==(const EventHandler &del) {
		return this->id == del.id;
	}
	bool operator!=(nullptr_t) {
		return this->_func != nullptr;
	}
};
