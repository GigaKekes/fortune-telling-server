#ifndef FT_LOGGER_H
#define FT_LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

namespace srv
{
    class Logger
    {
    public:
        Logger();
        Logger(const std::string &filename);
        ~Logger();

        void log(const std::string &message);

    private:
        std::string m_filename;
        std::ofstream m_file;
    };
} // namespace srv

#endif // FT_LOGGER_H