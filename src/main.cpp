#include <fmt/core.h>

#include <CLI/CLI.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <range/v3/all.hpp>  // range-v3 主头文件

int main(int argc, char** argv)
{
  CLI::App app{"🧪 A delightful demo using CLI11, fmt, nlohmann/json & range-v3 🔧"};

  bool verbose = false;
  std::string name = "World";
  std::string output_file = "./output.json";

  app.add_flag("-v,--verbose", verbose, "🔊 Talk more than necessary");
  app.add_option("-n,--name", name, "🧑 Whom should we greet?")->type_name("STRING");
  app.add_option("-o,--output", output_file, "📁 Specify the output JSON file")->type_name("FILE");

  CLI11_PARSE(app, argc, argv);

  fmt::print("👋 Hello, {}!\n", name);
  fmt::print("sizeof(void*) = {}!\n", sizeof(void*));

  if (verbose)
  {
    fmt::print("🗯️ Verbose mode is ON — you're in for *lots* of output!\n");
    fmt::print("📦 Powered by CLI11 + fmt + nlohmann/json + range-v3\n");
  }
  else
  {
    fmt::print("🤫 Running in quiet mode. Use -v to hear my thoughts.\n");
  }

  // 🌟 使用 range-v3 将 name 字符转换为大写
  auto uppercased = name | ranges::views::transform([](char c) { return static_cast<char>(std::toupper(c)); });

  std::string upper_name(uppercased.begin(), uppercased.end());
  fmt::print("🔠 Uppercased name via range-v3: {}\n", upper_name);

  // 🌟 构造整数序列并处理：筛选偶数 -> 平方 -> 求和
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6};

  auto even_squares = numbers | ranges::views::filter([](int n) { return n % 2 == 0; }) |
                      ranges::views::transform([](int n) { return n * n; });

  int sum = ranges::accumulate(even_squares, 0);
  fmt::print("🧮 Sum of squares of even numbers [2,4,6]: {}\n", sum);

  // ✍️ 创建 JSON 对象
  nlohmann::json j;
  j["greeting"] = fmt::format("Hello, {}!", name);
  j["verbose"] = verbose;
  j["output_file"] = output_file;
  j["name_upper"] = upper_name;
  j["even_squares"] = even_squares | ranges::to<std::vector<int>>;
  j["even_squares_sum"] = sum;

  // 💾 输出到文件
  std::ofstream file(output_file);
  if (file.is_open())
  {
    file << j.dump(2);  // 带缩进输出
    fmt::print("📄 Output written to: {}\n", output_file);
  }
  else
  {
    fmt::print("⚠️ Failed to open the file: {}\n", output_file);
  }

  return 0;
}
