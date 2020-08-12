#include "XLogger.h"

#include <ctime>
#include <iostream>
#include <thread>

char Timestamp::_date_time[32] = { "" };

XLogger::~XLogger()
{
  _log_file.close();
}

int XLogger::Init(std::string_view instance_name)
{
  _log_file = std::ofstream(instance_name.data(), std::ios::app | std::ios::out);
  return 0;
}

XLogger* XLogger::Instance()
{
  static XLogger instance;
  return &instance;
}

char* Timestamp::Now()
{
  auto t = time(nullptr);
  tm s_t;
  localtime_s(&s_t, &t);
  strftime(_date_time, sizeof _date_time, "%d/%m/%Y %H:%M:%S", &s_t);
  return _date_time;
}
