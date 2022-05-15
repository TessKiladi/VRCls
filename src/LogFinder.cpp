#include "LogFinder.h"
#include <initguid.h>
#include <KnownFolders.h>
#include <shlobj.h>
#include <codecvt>
#include <filesystem>
#include <iostream>
#include <locale>
#include <regex>


/*
FOLDERID_LocalAppDataLow
	
GUID 	{A520A1A4-1780-4FF6-BD18-167343C5AF16}
Display Name 	LocalLow
Folder Type 	PERUSER
Default Path 	%USERPROFILE%\AppData\LocalLow
CSIDL Equivalent 	None
Legacy Display Name 	Not applicable
Legacy Default Path 	Not applicable
*/
std::filesystem::path GetLocalLowPath()
{
    PWSTR path{0};
    HRESULT ADLLFindRet{SHGetKnownFolderPath(FOLDERID_LocalAppDataLow, 0, 0, &path)};
    std::filesystem::path result{""};
    if (SUCCEEDED(ADLLFindRet))
    {
        std::wstring thePath{path};
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        result = conv.to_bytes(thePath);
        CoTaskMemFree(path);
    }
    else
    {
        throw std::runtime_error("Could Not Get LocalLow");
    }
    return result;
}

std::filesystem::path IdentifyMostRecentLog()
{
    const std::regex IsOutputLog{"output_log_..-..-..\\.txt"};
    std::filesystem::path LocalLow{GetLocalLowPath()};
    std::filesystem::path vrchatPath{LocalLow/"VRChat\\VRChat"};
    std::filesystem::path Result{""};
    std::filesystem::file_time_type mostRecentTime{};
    if (is_directory(vrchatPath))
    {
        // std::cout << "found VRChat (" << vrchatPath << ")" << std::endl;
        for (auto const& dir_entry : std::filesystem::directory_iterator(vrchatPath))
        {
            // std::cout << "testing: " << dir_entry.path().filename().string() << std:: endl;
            std::string pathMatch{std::regex_replace(dir_entry.path().filename().string(), IsOutputLog, "found", std::regex_constants::format_no_copy)};
            if (pathMatch.length() > 0)
            {
                // std::cout << "Matched " << dir_entry << std::endl;
                // std::cout << "testing " << dir_entry.last_write_time().time_since_epoch().count() << " > " << mostRecentTime.time_since_epoch().count() << " (now is " << std::filesystem::file_time_type::clock::now().time_since_epoch().count() << ")" << std::endl;
                if ((dir_entry.last_write_time() > mostRecentTime) || (mostRecentTime.time_since_epoch().count() == 0))
                {
                    mostRecentTime = dir_entry.last_write_time();
                    Result = dir_entry.path();
                    // std::cout << dir_entry << " is leading" << std::endl;
                }
            }
        }
    }
    return Result;
}