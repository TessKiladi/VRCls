#include "LogScanner.h"
#include <fstream>
#include <regex>
#include <string>
#include <iostream>


void ProcessLine(std::string& line, UserList& theUserList)
{
    const std::regex PlayerJoined("\\[Behaviour\\] OnPlayerJoined (.*)");
    const std::regex PlayerLeft("\\[Behaviour\\] OnPlayerLeft (.*)");
    const std::regex LeftTheRoom("\\[Behaviour\\] OnLeftRoom");
    const std::regex_constants::match_flag_type flags{std::regex_constants::format_no_copy};
    std::string result{""};
    result = std::regex_replace(line, PlayerJoined, "$1", flags);
    if (result.length() > 0)
    {
        theUserList.addUser(result);
        return;
    }
    result = std::regex_replace(line, PlayerLeft, "$1", flags);
    if (result.length() > 0)
    {
        theUserList.removeUser(result);
        return;
    }
    result = std::regex_replace(line, LeftTheRoom, "Splat", flags);
    if (result.length() > 0)
    {
        theUserList.clear();
        return;
    }
}

size_t ScanLog(std::string LogFile, size_t StartPoint, UserList& theUserList)
{
    size_t EndPoint{0};
    std::ifstream TheLog(LogFile.c_str());
    if (TheLog.is_open())
    {
        TheLog.seekg(StartPoint);
        std::string aLine{""};
        while ( not std::getline(TheLog, aLine).eof())
        {
            if (aLine.length() > 0)
            {
                ProcessLine(aLine, theUserList);
            }
            EndPoint = TheLog.tellg();
        }
    }
    return EndPoint;
}