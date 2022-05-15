#pragma once
#include <string>
#include <set>
#include <cstdio>

class UserList
{
    public:
    void addUser(std::string user){
        _theList.insert(user);
        // printf("Added User \"%s\"\n", user.c_str());
    }
    void removeUser(std::string user){
        _theList.erase(user);
        // printf("Removed User \"%s\"\n", user.c_str());
    }
    void clear(){
        printf("List Cleared\n");
    }
    void dump(){
        for(const auto & a: _theList)
        {
            printf("User \"%s\"\n", a.c_str());
        }
    }
    private:
    using ilist = std::set<std::string>;
    ilist _theList;
};