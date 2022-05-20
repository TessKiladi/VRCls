#include "UserList.h"
#include "LogFinder.h"
#include "LogScanner.h"

#include <Fl/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <windows.h>

#include <iostream>
extern HINSTANCE fl_display;

class UserBrowser : public Fl_Browser, public Fl_Box
{
    public:
    UserBrowser(int X, int Y, int W, int H, std::string name)
    : Fl_Browser(X, Y+21, W, H-21, 0)
    , Fl_Box(X, Y, W, 20, nullptr)
    , _name(name)
    {
        // std::cout << "Name: " << _name << std::endl;
        Fl_Box::label(_name.c_str());
    }
    std::string GetName(){
        return _name;
    }
    void remove(UserList::UserDetails* who){
        if (who)
        {
            for (int i{0}; i <= Fl_Browser::size(); ++i)
            {
                if (static_cast<void*>(who) == data(i))
                {
                    Fl_Browser::remove(i);
                }
            }
            Fl_Browser::redraw();
            who->displayList = 0;
        }
    }
    void add(std::string user, UserList::UserDetails* who){
        if (who && (who->displayList == nullptr))
        {
            who->displayList = this;
            // std::cout << _name << ": adding " << user << std::endl;
            Fl_Browser::add(user.c_str(), who);
        }
    }
    void draw() final{
        Fl_Box::draw();
        Fl_Browser::draw();
    }
    private:
    std::string _name;
};

class MainForm : public Fl_Double_Window
{
    public:
    MainForm()
    : Fl_Double_Window(640, 480, "VRCls - Initial Loading, Please Wait!")
    , _theUserList  ()
    , _LastLog("")
    , _LastLogPosition(0)
    , _Staff        (  4,   4, 155, 445, "Staff")
    , _Guest        (163,   4, 155, 445, "Guest")
    , _Unverified   (322,   4, 155, 445, "Unverified")
    , _Unknown      (481,   4, 155, 445, "Unknown")
    , _Refresh      (  4, 454, 155,  20, "Refresh")
    , _Login        (163, 454, 155,  20, "Login")
    , _User         (322, 454, 155,  20, "Please Login")
    , _Quit         (481, 454, 155,  20, "Quit")
    , _listAssociation()
    {
        Fl_Double_Window::icon((char*)LoadIcon(fl_display, MAKEINTRESOURCE(0)));
        _Quit.callback(&_cbQuit, this);
        _listAssociation.insert(std::make_pair(_Staff.GetName(), &_Staff));
        _listAssociation.insert(std::make_pair(_Guest.GetName(), &_Guest));
        _listAssociation.insert(std::make_pair(_Unverified.GetName(), &_Unverified));
        _listAssociation.insert(std::make_pair(_Unknown.GetName(), &_Unknown));
        refresh();
        Fl_Double_Window::label("VRCls");
        Fl::add_timeout(5.0, &_timerFunc, this);
    }
    private:
    static void _cbQuit(Fl_Widget * w, void* p)
    {
        static_cast<MainForm*>(p)->hide();
    }
    static void _timerFunc(void* p)
    {
        static_cast<MainForm*>(p)->_timerFunc();
    }
    void _timerFunc()
    {
        refresh();
        Fl::repeat_timeout(5.0, &_timerFunc, this);
    }
    void updateDisplayLists()
    {
        for(auto &user: _theUserList)
        {
            if (user.second)
            {
                // std::cout << "User \"" << user.first << "\" for category " << user.second->category<<  std::endl;
                if (user.second->category == "remove") //this user is no-more, eliminate them
                {
                    if (user.second->displayList)//only remove from list if actually in a list...
                    {
                        static_cast<UserBrowser*>(user.second->displayList)->remove(user.second);
                    }
                    _theUserList.purgeUser(user.first);
                }
                else//shuffle and add
                {
                    auto iter{_listAssociation.find(user.second->category)};
                    if (iter != _listAssociation.end()) //Category is known
                    {
                        if ( user.second->displayList == iter->second)
                        {
                            //already in the right list, no action
                        }
                        else if (user.second->displayList != nullptr)
                        {
                            //wrong list, remove from old and add to new.
                            static_cast<UserBrowser*>(user.second->displayList)->remove(user.second);
                            static_cast<UserBrowser*>(iter->second)->add(user.first, user.second);
                        }
                        else
                        {
                            static_cast<UserBrowser*>(iter->second)->add(user.first, user.second);
                        }
                    }
                }
            }
            else
            {
                std::cerr << "User \"" << user.first << "\" lacks details!" << std::endl;
            }
        }
    }
    void refresh()
    {
        std::filesystem::path mrl{IdentifyMostRecentLog()};
        if (mrl != _LastLog)
        {
            _LastLogPosition = 0;
            _LastLog = mrl;
        }
        _LastLogPosition = ScanLog(_LastLog, _LastLogPosition, _theUserList);
        // _theUserList.dump();
        updateDisplayLists();
    }
    UserList _theUserList;
    std::filesystem::path _LastLog;
    size_t _LastLogPosition;
    UserBrowser _Staff;
    UserBrowser _Guest;
    UserBrowser _Unverified;
    UserBrowser _Unknown;
    Fl_Button _Refresh;
    Fl_Button _Login;
    Fl_Box    _User;
    Fl_Button _Quit;
    std::map<std::string, void*> _listAssociation;
};

int main(int argc, char * argv[])
{
  Fl::args(argc,argv);
  Fl::get_system_colors();
  Fl::scheme(Fl::scheme()); // init scheme before instantiating tests
  Fl::visual(FL_RGB);
  MainForm theMainForm;


  theMainForm.show(argc,argv);
  return(Fl::run());
}