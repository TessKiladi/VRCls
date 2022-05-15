#pragma once
#include "UserList.h"

#include <string>
#include <cstddef>
#include <filesystem>


size_t ScanLog(std::filesystem::path LogFile, size_t StartPoint, UserList& theUserList);


