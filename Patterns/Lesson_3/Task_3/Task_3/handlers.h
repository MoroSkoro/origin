#pragma once
#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include "pushHandler.h"
#include "messagers.h"


class WarningHandler : public PushHandler {
public:
	using PushHandler::PushHandler;
private:
	bool handlePush(const LogMessage& msg) override {
		if (msg.type() != WarningMessage::Type::_Warning) {
			return false;
		}
		std::cout << msg.message() << std::endl;
		return true;
	}
};

class ErrorHandler : public PushHandler {
public:
	using PushHandler::PushHandler;
private:
	bool handlePush(const LogMessage& msg) override {
		if (msg.type() != LogMessage::Type::_Error) {
			return false;
		}
		std::ofstream out;
		out.open(_file_path);
		if (out.is_open())
		{
			out <<msg.message() << std::endl;
		}
		out.close();
		std::cout << "Error. Ошибка записана в файл." << std::endl;
		return true;
	}

	std::string _file_path = "error_log.txt";
};

class FatalErrorHandler : public PushHandler {
public:
	using PushHandler::PushHandler;
private:
	bool handlePush(const LogMessage& msg) override {
		if (msg.type() != LogMessage::Type::_FatalError) {
			return false;
		}

		throw std::runtime_error("Fatal Error! Фатальная ошибка!");
		
		return true;
	}
};

class UnknownHandler : public PushHandler {
public:
	using PushHandler::PushHandler;
private:
	bool handlePush(const LogMessage& msg) override {
		if (msg.type() != LogMessage::Type::_Unknown) {
			return false;
		}

		throw std::runtime_error("Error: Unprocessed message! Необработанная неизвестная ошибка!");
		
		return true;
	}
};