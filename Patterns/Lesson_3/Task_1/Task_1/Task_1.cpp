#include <iostream>
#include <fstream>
#include <string>


class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class PrintConsolCommand : public LogCommand {
public:
    virtual ~PrintConsolCommand() = default;
   
    void print(const std::string& message) override {
        std::cout << message << std::endl;
    };
};

class PrintFileCommand : public LogCommand {
public:
    virtual ~PrintFileCommand() = default;
    PrintFileCommand() {};
    PrintFileCommand(const std::string& file_path): _file_path(file_path) {};

    void print(const std::string& message) override {
        std::ofstream out;
        out.open(_file_path);
        if (out.is_open())
        {
            out << message << std::endl;
        }
        out.close();
    };
private:
    std::string _file_path = "file.txt";
};

void print(LogCommand& c, const std::string& message) {
    c.print(message);
}

int main(){
    PrintConsolCommand con_msg;
    PrintFileCommand f_msg;

    print(con_msg, "Hello World!\n");
    print(f_msg, "Hello World!\n");
}
