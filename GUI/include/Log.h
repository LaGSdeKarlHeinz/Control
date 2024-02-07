#ifndef LOG_H
#define LOG_H

#include <string>

class MainLog
{
public:
    MainLog();
    ~MainLog();
    virtual void info(std::string event, std::string message) = 0;
    virtual void debug(std::string event, std::string message) = 0;
    virtual void warn(std::string event, std::string message) = 0;
    virtual void error(std::string event, std::string message) = 0;
    virtual void fatal(std::string event, std::string message) = 0;

protected:
    void write_log(std::string level, std::string module, std::string event, std::string message);
    static std::string filename_;

private:
    void check_directory(std::string dir);
    void create_file();
    void append_to_file(std::string filename, std::string content);
};

class ModuleLog : public MainLog
{
private:
    std::string module_;

public:
    ModuleLog(std::string module);
    ~ModuleLog();
    void info(std::string event, std::string message) final override;
    void debug(std::string event, std::string message) final override;
    void warn(std::string event, std::string message) final override;
    void error(std::string event, std::string message) final override;
    void fatal(std::string event, std::string message) final override;
};

#endif /* LOG_H */