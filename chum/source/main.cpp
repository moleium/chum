#include "chum.h"

void create_test_binary() {
  chum::binary bin = {};

  // Import a routine from ntdll.dll.
  auto const ntdll = bin.create_import_module("ntdll.dll");
  auto const close_handle = ntdll->create_routine("CloseHandle");
  assert(close_handle->sym_id == 1);

  // Create a basic block that calls the imported routine.
  auto const bb = bin.create_basic_block("basic_block_1");
  bb->instructions.push_back({ 1, { 0x90 } });
  bb->instructions.push_back({ 6, { 0xFF, 0x15, 0x01, 0x00, 0x00, 0x00 } });

  bin.print();
}

int main() {
  //create_test_binary();

  //auto bin = chum::disassemble("C:\\Users\\realj\\Desktop\\ntoskrnl (19041.1110).exe");
  auto bin = chum::disassemble("hello-world-x64.dll");
  //auto bin = chum::disassemble("hello-world-x64-min.dll");

  if (!bin) {
    std::printf("[!] Failed to disassemble binary.\n");
    return 0;
  }

  bin->print();
}

