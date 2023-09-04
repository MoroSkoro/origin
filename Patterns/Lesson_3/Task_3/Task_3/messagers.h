#pragma once
#include <iostream>
#include <string>
#include "pushHandler.h"

class WarningMessage : public LogMessage {
public:
	Type type() const override { return Type::_Warning; }
	const std::string message() const override {
		return "Warning! ��������������. ";
	}
};

class ErrorMessage : public LogMessage {
public:
	Type type() const override { return Type::_Error; }
	const std::string message () const override {
		return "������. ";
	}
};

class FatallErrorMessage : public LogMessage {
public:
	Type type() const override { return Type::_FatalError; }
	const std::string message() const override {
		return "Fatal Error!��������� ������!";
	}
};

class UnknownErrorMessage : public LogMessage {
public:
	Type type() const override { return Type::_Unknown; }
	const std::string message() const override {
		return "Error: Unprocessed message! �������������� ����������� ������!";
	}
};