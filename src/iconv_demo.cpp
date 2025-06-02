#include <iconv.h>

#include <cstring>
#include <iostream>

int main()
{
  iconv_t cd = iconv_open("UTF-8", "GBK");
  if (cd == (iconv_t)-1)
  {
    std::cerr << "iconv_open failed\n";
    return 1;
  }

  char input[] = "\xC4\xE3\xBA\xC3";  // “你好” in GBK
  char output[256] = {0};
  char* inbuf = input;
  char* outbuf = output;
  size_t inbytesleft = strlen(input);
  size_t outbytesleft = sizeof(output);

  if (iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft) == (size_t)-1)
  {
    std::cerr << "iconv conversion failed\n";
    iconv_close(cd);
    return 1;
  }

  std::cout << "Converted: " << output << '\n';
  iconv_close(cd);
  return 0;
}
