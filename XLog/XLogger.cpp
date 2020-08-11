#include "XLogger.h"

#include <iostream>

XLogger::XLogger(std::string&& instance_name) : XLogger(instance_name)
{
}

XLogger::XLogger(const std::string& instance_name)
    : _log_file(std::ofstream(instance_name.c_str(), std::ios::app | std::ios::out))
{
}

XLogger::~XLogger()
{
  _log_file.close();
}

void XLogger::Output(std::string&& log_msg)
{
  Output(log_msg);
}

void XLogger::Output(const std::string& log_msg)
{
  std::cout << log_msg << std::endl;
  _log_file << log_msg << std::endl;
}
