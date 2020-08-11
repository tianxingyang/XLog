#include "XLogger.h"

int main()
{
  XLogger logger("all_msgs.log");
  logger.Output("abc");

  return 0;
}