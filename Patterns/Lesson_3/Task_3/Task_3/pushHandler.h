#pragma once
#include <iostream>
#include <string>
#include <exception>


class LogMessage {
public:
    enum class Type {
        _Warning,
        _Error,
        _FatalError,
        _Unknown,
    };
    
    virtual ~LogMessage() = default;

    virtual Type type() const = 0;
    virtual const std::string message() const = 0;
};

class PushHandler {
public:
    explicit PushHandler(std::unique_ptr<PushHandler> next) : next_(std::move(next)) {}
    virtual ~PushHandler() = default;
    void receivePush(const LogMessage& msg) {
        if (handlePush(msg)) {
            return;
        }
        if (!next_) {
            throw std::runtime_error("Error: Unprocessed message!");
        }
        next_->receivePush(msg);
    }
private:
    virtual bool handlePush(const LogMessage& msg) = 0;
    std::unique_ptr<PushHandler> next_;
};