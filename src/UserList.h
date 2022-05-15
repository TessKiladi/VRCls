#pragma once
#include <string>
#include <map>
#include <cstdio>


class UserList
{
    public:
    struct UserDetails
    {
        void* displayList{0};
        std::string icon{""};
        std::string category{"Unknown"};
        unsigned char red{0};
        unsigned char green{0};
        unsigned char blue{0};
    };
    using ilist = std::map<std::string, UserDetails*>;
    void addUser(std::string user){
        if (_theList.find(user) == _theList.end())
        {
            UserDetails* tmp = new UserDetails;
            _theList.insert(std::make_pair(user, tmp));
        }
        // printf("Added User \"%s\"\n", user.c_str());
    }
    void removeUser(std::string user){
        _theList.erase(user);
        // printf("Removed User \"%s\"\n", user.c_str());
    }
    void clear(){
        // printf("List Cleared\n");
        _theList.clear();
    }
    void dump(){
        for(const auto & a: _theList)
        {
            printf("User \"%s\"\n", a.first.c_str());
        }
    }
    ilist::iterator begin(){
        return _theList.begin();
    }
    ilist::iterator end(){
        return _theList.end();
    }
    private:
    
    ilist _theList;
};