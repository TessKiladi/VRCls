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
        auto iter{_theList.find(user)};
        if (iter == _theList.end())
        {
            UserDetails* tmp = new UserDetails;
            _theList.insert(std::make_pair(user, tmp));
            // printf("Added User \"%s\"\n", user.c_str());
        }
        else if (iter->second->category == "remove")
        {
            iter->second->category = "Unknown";
            // printf("reAdded User \"%s\" who was marked for removal\n", user.c_str());
        }
    }
    void removeUser(std::string user){
        auto iter{_theList.find(user)};
        if (iter != _theList.end())
        {
            if (iter->second)
            {
                iter->second->category = "remove";
                // printf("User \"%s\" marked for removal\n", user.c_str());
            }
        }
    }
    void purgeUser(std::string user){
        auto iter{_theList.find(user)};
        if (iter != _theList.end())
        {
            if (iter->second && iter->second->displayList)
            {
                printf("display-list still linked! (%s)\n", user.c_str());
            }
            delete iter->second;
            iter->second = nullptr;
            _theList.erase(user);
            // printf("User \"%s\" purged\n", user.c_str());
        }
    }
    void clear(){
        printf("List Cleared\n");
        for (auto user: _theList)
        {
            if(user.second)
            {
                user.second->category = "remove";
            }
        }
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