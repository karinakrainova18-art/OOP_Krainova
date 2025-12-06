#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <ctime>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& event) = 0;
};

class ConsoleObserver : public Observer {
public:
    void update(const std::string& event) override {
        std::cout << "[BATTLE LOG] " << event << std::endl;
    }
};

class FileObserver : public Observer {
private:
    std::ofstream file_;
    std::string get_timestamp() const;

public:
    FileObserver(const std::string& filename = "log.txt");
    ~FileObserver();
    void update(const std::string& event) override;
};

#endif


