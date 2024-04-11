#include "doctest.h"

#include "cout_capture.h"

#include "renderer/shader.h"
#include "init_glad.h"

TEST_CASE("Shaders") {
  // Initialize GLAD
  init_glad("TEST", 800, 600);

  CoutCapture capture;
  std::string output;

  SUBCASE("Shader files not found") {
    Shader testShader("non_existent_shader.vs", "non_existent_shader.fs");

    output = capture.str();
    doctest::String ts(output.c_str(), output.length());
    REQUIRE(ts == doctest::Contains("FILE_NOT_SUCCESFULLY_READ"));
    REQUIRE(ts == doctest::Contains("PROGRAM_LINKING_ERROR"));
  }

  SUBCASE("Shader files found") {
    Shader testShader("test_shaders/vertex.vs", "test_shaders/fragment.fs");

    output = capture.str();
    doctest::String ts(output.c_str(), output.length());
    REQUIRE(ts != doctest::Contains("ERROR"));
  }

  SUBCASE("Shader files found but vertex shader error") {
    Shader testShader("test_shaders/bad_vertex.vs", "test_shaders/fragment.fs");

    output = capture.str();
    doctest::String ts(output.c_str(), output.length());
    REQUIRE(ts == doctest::Contains("SHADER_COMPILATION_ERROR of type: VERTEX"));
  }

  SUBCASE("Shader files found but fragment shader error") {
    Shader testShader("test_shaders/vertex.vs", "test_shaders/bad_fragment.fs");

    output = capture.str();
    doctest::String ts(output.c_str(), output.length());
    REQUIRE(ts == doctest::Contains("SHADER_COMPILATION_ERROR of type: FRAGMENT"));
  }
}
