#include "XLogger.h"

int main()
{
  XLogger::Instance()->Init("all_msgs.log");

  for (int i = 0; i < 500000; ++i)
  {
    LOGDBG("%d", 10001);
  }

  return 0;
}