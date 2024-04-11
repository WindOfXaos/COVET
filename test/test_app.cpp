#include "doctest.h"

#include "core/app.h"
#include "core/window_manager.h"

TEST_CASE("Main window title") {
  // Create singleton instance
  App& app = App::Create("TEST", 1366, 768);
  REQUIRE(&app != NULL);

  const WindowManager& wm = app.GetWindowManager();
  CHECK(doctest::String(wm.title) == "TEST");
  CHECK(wm.width == 1366);
  CHECK(wm.height == 768);

  // Test singleton instance
  App& app2 = App::Create("TEST2", 1000, 1000);

  const WindowManager& wm2 = app2.GetWindowManager();
  CHECK(doctest::String(wm2.title) == "TEST");
  CHECK(wm2.width == 1366);
  CHECK(wm2.height == 768);
}
