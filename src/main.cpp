#include <fmt/core.h>

#include <CLI/CLI.hpp>

int main(int argc, char** argv)
{
  CLI::App app{"🧪 A delightful demo using CLI11 & fmt 🔧"};

  bool verbose = false;
  std::string name = "World";

  app.add_flag("-v,--verbose", verbose, "🔊 Talk more than necessary");
  app.add_option("-n,--name", name, "🧑 Whom should we greet?")->type_name("STRING");

  CLI11_PARSE(app, argc, argv);

  fmt::print("👋 Hello, {}!\n", name);

  if (verbose)
  {
    fmt::print("🗯️ Verbose mode is ON — you're in for *lots* of output!\n");
    fmt::print("📦 Powered by CLI11 + fmt\n");
  }
  else
  {
    fmt::print("🤫 Running in quiet mode. Use -v to hear my thoughts.\n");
  }

  return 0;
}
