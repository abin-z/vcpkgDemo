#include <cppcodec/base64_rfc4648.hpp>
#include <iostream>

int main()
{
  using base64 = cppcodec::base64_rfc4648;

  std::string encoded = base64::encode("hello vcpkg");
  std::string decoded = base64::decode<std::string>(encoded);

  std::cout << "Encoded: " << encoded << std::endl;
  std::cout << "Decoded: " << decoded << std::endl;
}
