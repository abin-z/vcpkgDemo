#include <fmt/core.h>
#include <spdlog/sinks/basic_file_sink.h>  // 用于文件输出（可选）
#include <spdlog/spdlog.h>

#include <CLI/CLI.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <range/v3/all.hpp>

int main(int argc, char** argv)
{
  CLI::App app{"🧪 A delightful demo using CLI11, fmt, spdlog, nlohmann/json & range-v3 🔧"};

  bool verbose = false;
  std::string name = "World";
  std::string output_file = "./output.json";
  std::string log_file;

  app.add_flag("-v,--verbose", verbose, "🔊 Talk more than necessary");
  app.add_option("-n,--name", name, "🧑 Whom should we greet?")->type_name("STRING");
  app.add_option("-o,--output", output_file, "📁 Specify the output JSON file")->type_name("FILE");
  app.add_option("--log-file", log_file, "🪵 Optional log file to write logs")->type_name("FILE");

  CLI11_PARSE(app, argc, argv);

  // 🧱 初始化 spdlog
  if (!log_file.empty())
  {
    try
    {
      auto file_logger = spdlog::basic_logger_mt("file_logger", log_file);
      spdlog::set_default_logger(file_logger);
      spdlog::set_level(verbose ? spdlog::level::debug : spdlog::level::info);
    }
    catch (const spdlog::spdlog_ex& ex)
    {
      fmt::print("❌ Failed to initialize file logger: {}\n", ex.what());
    }
  }
  else
  {
    spdlog::set_level(verbose ? spdlog::level::debug : spdlog::level::info);
  }

  spdlog::info("👋 Hello, {}!", name);
  spdlog::info("sizeof(void*) = {}", sizeof(void*));

  if (verbose)
  {
    spdlog::debug("🗯️ Verbose mode is ON — you're in for *lots* of output!");
    spdlog::debug("📦 Powered by CLI11 + fmt + spdlog + nlohmann/json + range-v3");
  }
  else
  {
    spdlog::info("🤫 Running in quiet mode. Use -v to hear my thoughts.");
  }

  // 🌟 使用 range-v3 将 name 字符转换为大写
  auto uppercased = name | ranges::views::transform([](char c) { return static_cast<char>(std::toupper(c)); });
  std::string upper_name(uppercased.begin(), uppercased.end());
  spdlog::info("🔠 Uppercased name via range-v3: {}", upper_name);

  // 🌟 构造整数序列并处理：筛选偶数 -> 平方 -> 求和
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
  auto even_squares = numbers | ranges::views::filter([](int n) { return n % 2 == 0; }) |
                      ranges::views::transform([](int n) { return n * n; });
  int sum = ranges::accumulate(even_squares, 0);
  spdlog::info("🧮 Sum of squares of even numbers [2,4,6]: {}", sum);

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
    spdlog::info("📄 Output written to: {}", output_file);
  }
  else
  {
    spdlog::error("⚠️ Failed to open the file: {}", output_file);
  }

  return 0;
}
