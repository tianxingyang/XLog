#pragma once

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string_view>
#include <thread>

namespace LogLevel
{
constexpr std::string_view kDebug = "DEBUG";
constexpr std::string_view kInfo = "INFO";
constexpr std::string_view kWarn = "WARN";
constexpr std::string_view kError = "ERROR";
constexpr std::string_view kFatal = "FATAL";
}  // namespace LogLevel
static char buf[1 << 15] = { "" };

constexpr auto kEnableStdOut = 0;

#define FORMAT_BUF(...)     \
  extern char buf[1 << 15]; \
  sprintf_s(buf, sizeof buf, ##__VA_ARGS__);

#if kEnableStdOut
#ifdef DO_STD_OUT
#undef DO_STD_OUT
#endif  // DO_STD_OUT
#ifdef DO_LOG
#undef DO_LOG
#endif  // DO_LOG
#define DO_STD_OUT(log_lvl, ...)                                                                   \
  FORMAT_BUF(##__VA_ARGS__)                                                                        \
  std::cout << Timestamp::Now() << " [" << log_lvl << "] [" << std::this_thread::get_id() << "] [" \
            << __FILE__ << ":" << __LINE__ << "] " << buf << std::endl;

#define DO_LOG(log_lvl, ...)                                                                           \
  XLogger::Instance()->_log_file << Timestamp::Now() << " [" << log_lvl << "] ["                       \
                                 << std::this_thread::get_id() << "] [" << __FILE__ << ":" << __LINE__ \
                                 << "] " << buf << std::endl;
#else
#ifdef DO_STD_OUT
#undef DO_STD_OUT
#endif  // DO_STD_OUT
#ifdef DO_LOG
#undef DO_LOG
#endif  // DO_LOG
#define DO_STD_OUT(log_lvl, ...) void(0);
#define DO_LOG(log_lvl, ...)                                                                           \
  FORMAT_BUF(##__VA_ARGS__)                                                                            \
  XLogger::Instance()->_log_file << Timestamp::Now() << " [" << log_lvl << "] ["                       \
                                 << std::this_thread::get_id() << "] [" << __FILE__ << ":" << __LINE__ \
                                 << "] " << buf << std::endl;
#endif  // kEnableStdOut

#define LOGDBG(...)                             \
  do                                            \
  {                                             \
    DO_STD_OUT(LogLevel::kDebug, ##__VA_ARGS__) \
    DO_LOG(LogLevel::kDebug, ##__VA_ARGS__)     \
  } while (false);

#define LOGINFO(...)                           \
  do                                           \
  {                                            \
    DO_STD_OUT(LogLevel::kInfo, ##__VA_ARGS__) \
    DO_LOG(LogLevel::kInfo, ##__VA_ARGS__)     \
  } while (false);

#define LOGWARN(...)                           \
  do                                           \
  {                                            \
    DO_STD_OUT(LogLevel::kWarn, ##__VA_ARGS__) \
    DO_LOG(LogLevel::kWarn, ##__VA_ARGS__)     \
  } while (false);

#define LOGERR(...)                             \
  do                                            \
  {                                             \
    DO_STD_OUT(LogLevel::kError, ##__VA_ARGS__) \
    DO_LOG(LogLevel::kError, ##__VA_ARGS__)     \
  } while (false);

#define LOGFATAL(...)                           \
  do                                            \
  {                                             \
    DO_STD_OUT(LogLevel::kFatal, ##__VA_ARGS__) \
    DO_LOG(LogLevel::kFatal, ##__VA_ARGS__)     \
  } while (false);

class Timestamp
{
 public:
  static char* Now();

 private:
  static char _date_time[32];
};

class XLogger
{
 public:
  XLogger() = default;
  ~XLogger();

  int Init(std::string_view instance_name);

  static XLogger* Instance();

  std::ofstream _log_file;
};
