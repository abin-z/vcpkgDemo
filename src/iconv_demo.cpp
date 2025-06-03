#include <iconv.h>  // iconv 库，用于编码转换

#include <cstring>   // strlen 函数
#include <iostream>  // std::cout, std::cerr

int main()
{
  // 创建一个转换描述符，将输入编码 GBK 转换为输出编码 UTF-8
  iconv_t cd = iconv_open("UTF-8", "GBK");
  if (cd == (iconv_t)-1)
  {
    // 创建失败，通常是编码名错误或者系统不支持该编码
    std::cerr << "iconv_open failed\n";
    return 1;
  }

  // 输入字符串，字节序列为 GBK 编码的 “你好”
  // \xC4\xE3\xBA\xC3 是 “你”和“好”在 GBK 中的字节表示, 末尾是有 \0 的，这是 C++ 字符串字面量的默认行为
  char input[] = "\xC4\xE3\xBA\xC3";

  // 输出缓冲区，大小为 256 字节，初始化为全 0
  // 用于存放转换后 UTF-8 编码的结果
  char output[256] = {0};

  // 指向输入缓冲区的指针，iconv 会修改该指针来指示剩余未转换部分
  char* inbuf = input;

  // 指向输出缓冲区的指针，iconv 会修改该指针来指示写入位置
  char* outbuf = output;

  // 输入剩余字节数，初始为 input 的长度（不包括末尾的 \0）
  size_t inbytesleft = strlen(input);

  // 输出剩余空间大小，初始为 output 缓冲区总大小
  size_t outbytesleft = sizeof(output);

  // 调用 iconv 执行编码转换
  // 参数解释：
  //   cd          转换描述符
  //   &inbuf      输入缓冲区指针地址，会被更新为未转换字节起始位置
  //   &inbytesleft 输入剩余字节数，会被更新为剩余未转换字节数
  //   &outbuf     输出缓冲区指针地址，会被更新为下一个写入位置
  //   &outbytesleft 输出剩余空间大小，会被更新为剩余可写字节数
  if (iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft) == (size_t)-1)
  {
    // 转换失败，可能是无效编码、输出空间不足等原因
    std::cerr << "iconv conversion failed\n";
    iconv_close(cd);  // 关闭转换描述符，释放资源
    return 1;
  }

  // 转换完成后，iconv 不会自动添加字符串结束符 '\0'
  // 这里手动添加 '\0'，使 output 成为合法的 C 字符串
  *outbuf = '\0';

  // 输出原始输入字节（GBK编码，不一定能正确显示）
  std::cout << "Input(GBK): " << input << '\n';

  // 输出转换后的字符串（UTF-8编码，能正确显示“你好”）
  std::cout << "Converted(UTF-8): " << output << '\n';

  // 关闭转换描述符，释放资源
  iconv_close(cd);

  return 0;
}
