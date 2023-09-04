#pragma once
#include <iostream>
#include <string>
#include "pushHandler.h"

class WarningMessage : public LogMessage {
public:
	Type type() const override { return Type::_Warning; }
	const std::string message() const override {
		return "Warning! Предупреждение. ";
	}
};

class ErrorMessage : public LogMessage {
public:
	Type type() const override { return Type::_Error; }
	const std::string message () const override {
		return "Ошибка. ";
	}
};

class FatallErrorMessage : public LogMessage {
public:
	Type type() const override { return Type::_FatalError; }
	const std::string message() const override {
		return "Fatal Error!Фатальная ошибка!";
	}
};

class UnknownErrorMessage : public LogMessage {
public:
	Type type() const override { return Type::_Unknown; }
	const std::string message() const override {
		return "Error: Unprocessed message! Необработанная неизвестная ошибка!";
	}
};