#include "core/app.h"

int main(void)
{
  App& app = App::Create("COVET", 1366, 768);
  app.Run();

  return 0;
}
