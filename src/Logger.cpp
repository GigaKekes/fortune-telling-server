#include "Logger.h"

namespace srv
{
    Logger::Logger() : m_filename("server.log")
    {
        m_file.open(m_filename, std::ios::app);
        if (!m_file.is_open())
        {
            std::cerr << "Failed to open file: " << m_filename << std::endl;
        }
    }

    Logger::Logger(const std::string &filename) : m_filename(filename)
    {
        m_file.open(filename, std::ios::app);
        if (!m_file.is_open())
        {
            std::cerr << "Failed to open file: " << filename << std::endl;
        }
    }

    Logger::~Logger()
    {
        if (m_file.is_open())
        {
            m_file.close();
        }
    }

    void Logger::log(const std::string &message)
    {
        if (m_file.is_open())
        {
            std::time_t now = std::time(nullptr);
            std::string timestamp = std::ctime(&now);
            timestamp.pop_back(); // Remove newline character

            m_file << "[" << timestamp << "] " << message << std::endl;
        }
    }
}