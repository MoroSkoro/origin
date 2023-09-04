#include <iostream>
#include <string>
#include <vector>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

class Observed {
public:
    void AddObserver(Observer* observer) {
        observers_.push_back(observer);
    }

    void warning(const std::string& message) const {
        for (auto observer : observers_) {
            observer->onWarning(message);
        }
    }

    void error(const std::string& message) const {
        for (auto observer : observers_) {
            observer->onError(message);
        }
    }

    void fatalError(const std::string& message) const {
        for (auto observer : observers_) {
            observer->onFatalError(message);
        }
    }

    void RemoveObserver(Observer* observer) {
        auto it = std::remove(observers_.begin(), observers_.end(), observer);
        observers_.erase(it, observers_.end());
    }

private:
    std::vector<Observer*> observers_;
};

class ObserverWarn : public Observer{
public:
    ObserverWarn(Observed* observed): _observed(observed){}
    virtual ~ObserverWarn() { _observed->RemoveObserver(this); }
    virtual void onWarning(const std::string& message) { std::cout << "Warning: " << message << std::endl; }
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}

private:
    Observed* _observed;
};

class ObserverErr : public Observer {
public:
    ObserverErr(Observed* observed) : _observed(observed) {}
    virtual ~ObserverErr() { _observed->RemoveObserver(this); }
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) { std::cout << "Error: " << message << std::endl; }
    virtual void onFatalError(const std::string& message) {}

private:
    Observed* _observed;
};

class ObserverFat : public Observer {
public:
    ObserverFat(Observed* observed) : _observed(observed) {}
    virtual ~ObserverFat() { _observed->RemoveObserver(this); }
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) { std::cout << "Fatal Error: " << message<< " !!!" << std::endl; }

private:
    Observed* _observed;
};

int main(){
    Observed observed;
    ObserverWarn observer1(&observed);
    ObserverErr observer2(&observed);
    ObserverFat observer3(&observed);

    observed.AddObserver(&observer1);
    observed.AddObserver(&observer2);
    observed.AddObserver(&observer3);


    observed.warning("warning");
    observed.error("error");
    observed.fatalError("fatalError");
}