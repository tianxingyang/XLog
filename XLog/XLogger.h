#pragma once

#include <fstream>
#include <string>

class XLogger
{
 public:
  XLogger(std::string&& instance_name);
  XLogger(const std::string& instance_name);
  ~XLogger();

  void Output(std::string&& log_msg);

  void Output(const std::string& log_msg);

 private:
  std::ofstream _log_file;
};