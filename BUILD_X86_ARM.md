/opt/homebrew/opt/llvm/bin/clang++ -target x86_64-apple-macos13 \
  -isysroot $(xcrun --sdk macosx --show-sdk-path) \
  -I/opt/homebrew/opt/llvm/include/c++/v1 \
  -L/opt/homebrew/opt/llvm/lib \
  -stdlib=libc++ \
  avx_test.cpp -o avx_test_x86
