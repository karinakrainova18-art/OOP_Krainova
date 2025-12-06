#include "../include/observer.h"

std::string FileObserver::get_timestamp() const {
    std::time_t now = std::time(nullptr);
    char buf[100];
    if (std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now))) {
        return buf;
    }
    return "";
}

FileObserver::FileObserver(const std::string& filename) {
    file_.open(filename, std::ios::app);
    if (!file_.is_open()) {
        std::cerr << "Error: Could not open log file: " << filename << std::endl;
    }
}

FileObserver::~FileObserver() {
    if (file_.is_open()) {
        file_.close();
    }
}

void FileObserver::update(const std::string& event) {
    if (file_.is_open()) {
        file_ << "[" << get_timestamp() << "] " << event << std::endl;
        file_.flush();
    }
}


