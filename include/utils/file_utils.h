// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#ifndef UTILS_FILE_UTILS_H
#define UTILS_FILE_UTILS_H
#include <string>
#include <vector>

[[nodiscard]] std::vector<std::string> ReadFile(const std::string &file_path);

#endif // UTILS_FILE_UTILS_H