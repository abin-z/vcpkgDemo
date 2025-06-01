#include <fmt/core.h>

#include <cppcodec/base64_rfc4648.hpp>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

using base64 = cppcodec::base64_rfc4648;

void print_hex(const std::vector<uint8_t>& data)
{
  for (size_t i = 0; i < data.size(); ++i)
  {
    fmt::print("{:02x}{}", data[i], (i + 1 < data.size()) ? " " : "");
  }
  fmt::print("\n");
}

int main()
{
  // 示例 1：简单字符串编码/解码
  std::string input_text = "hello vcpkg";
  std::string encoded_text = base64::encode(input_text);
  std::string decoded_text = base64::decode<std::string>(encoded_text);

  fmt::print("=== Example 1: String encoding/decoding ===\n");
  fmt::print("Original: {}\n", input_text);
  fmt::print("Encoded : {}\n", encoded_text);
  fmt::print("Decoded : {}\n\n", decoded_text);

  // 示例 2：二进制数据编码/解码 + 验证, 二进制数据可以来自任何来源，例如文件、网络数据等
  std::vector<uint8_t> original_data = {0x00, 0x01, 0xFF, 0x20, 0x42, 0x99, 0xAB, 0xCD, 0xEF, 0x00,
                                        0x11, 0x22, 0x33, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32};

  std::string encoded = base64::encode(original_data);
  std::vector<uint8_t> decoded = base64::decode(encoded);

  fmt::print("=== Example 2: Binary data encoding/decoding ===\n");
  fmt::print("Base64 encoded:\n{}\n\n", encoded);

  fmt::print("Original data (hex):\n");
  print_hex(original_data);

  fmt::print("\nDecoded data (hex):\n");
  print_hex(decoded);

  if (original_data == decoded)
  {
    fmt::print("\n✅ Decoded data matches original\n");
  }
  else
  {
    fmt::print("\n❌ Decoded data does NOT match original\n");
  }

  return 0;
}
