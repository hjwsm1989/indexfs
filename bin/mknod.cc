// Copyright (c) 2014 The IndexFS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include <iostream>

#include "client/libclient_helper.h"

int main(int argc, char* argv[]) {
  SetUsageMessage("IndexFS Client Toolkit - mknod");
  ParseCommandLineFlags(&argc, &argv, true);
  if (argc != 2) {
    std::cerr << "== Usage: " << argv[0] << " <path> " << std::endl;
    return -1;
  }
  struct stat buf;
  struct conf_t* config = NULL;
  if (IDX_Init(config) == 0) {
    const char* p = argv[1];
    if (IDX_Mknod(p, (S_IRWXU | S_IRWXG | S_IRWXO)) == 0) {
      if (IDX_GetAttr(p, &buf) == 0) {
        std::cout << p << ":" << std::endl;
        std::cout << "  size=" << buf.st_size << std::endl;
        std::cout << "  mode=" << std::oct << buf.st_mode << std::endl;
      }
    }
  }
  IDX_Destroy();
  return 0;
}
