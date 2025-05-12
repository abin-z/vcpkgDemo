#include <fmt/core.h>

#include <CLI/CLI.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

int main(int argc, char** argv)
{
  CLI::App app{"🧪 A delightful demo using CLI11, fmt & nlohmann/json 🔧"};

  bool verbose = false;
  std::string name = "World";
  std::string output_file = "./output.json";

  app.add_flag("-v,--verbose", verbose, "🔊 Talk more than necessary");
  app.add_option("-n,--name", name, "🧑 Whom should we greet?")->type_name("STRING");
  app.add_option("-o,--output", output_file, "📁 Specify the output JSON file")->type_name("FILE");

  CLI11_PARSE(app, argc, argv);

  fmt::print("👋 Hello, {}!\n", name);

  if (verbose)
  {
    fmt::print("🗯️ Verbose mode is ON — you're in for *lots* of output!\n");
    fmt::print("📦 Powered by CLI11 + fmt + nlohmann/json\n");
  }
  else
  {
    fmt::print("🤫 Running in quiet mode. Use -v to hear my thoughts.\n");
  }

  // Create a JSON object and populate it with some data
  nlohmann::json j;
  j["greeting"] = fmt::format("Hello, {}!", name);
  j["verbose"] = verbose;
  j["output_file"] = output_file;

  // Optionally, write the JSON data to a file
  std::ofstream file(output_file);
  if (file.is_open())
  {
    file << j.dump(2);  // Write with indentation for readability
    fmt::print("📄 Output written to: {}\n", output_file);
  }
  else
  {
    fmt::print("⚠️ Failed to open the file: {}\n", output_file);
  }

  return 0;
}
