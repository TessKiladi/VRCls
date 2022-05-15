#include "UserList.h"
#include "LogFinder.h"
#include "LogScanner.h"

#include <Fl/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

class MainForm : public Fl_Double_Window
{
    public:
    MainForm()
    : Fl_Double_Window(640, 480, "VRCls")
    , _theUserList  ()
    , _LastLog("")
    , _LastLogPosition(0)
    , _lblStaff     (  4,   4, 155,  20, "Staff")
    , _Staff        (  4,  25, 155, 425, 0)
    , _lblGuest     (163,   4, 155,  20, "Guest")
    , _Guest        (163,  25, 155, 425, 0)
    , _lblUnverified(322,   4, 155,  20, "Unverified")
    , _Unverified   (322,  25, 155, 425, 0)
    , _lblUnknown   (481,   4, 155,  20, "Unknown")
    , _Unknown      (481,  25, 155, 425, 0)
    , _Refresh      (  4, 454, 155,  20, "Refresh")
    , _Login        (163, 454, 155,  20, "Login")
    , _User         (322, 454, 155,  20, "Please Login")
    , _Quit         (481, 454, 155,  20, "Quit")
    {
        _Quit.callback(&_cbQuit, this);
        Fl::add_timeout(0.5, &_timerFunc, this);
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
        std::filesystem::path mrl{IdentifyMostRecentLog()};
        if (mrl != _LastLog)
        {
            _LastLogPosition = 0;
            _LastLog = mrl;
        }
        _LastLogPosition = ScanLog("c:/Users/tess/AppData/LocalLow/VRChat/VRChat/output_log_01-51-48.txt", _LastLogPosition, _theUserList);
        _theUserList.dump();
        // Fl::repeat_timeout(5.0, &_timerFunc, this);
    }
    UserList _theUserList;
    std::filesystem::path _LastLog;
    size_t _LastLogPosition;
    Fl_Box _lblStaff;
    Fl_Browser _Staff;
    Fl_Box _lblGuest;
    Fl_Browser _Guest;
    Fl_Box _lblUnverified;
    Fl_Browser _Unverified;
    Fl_Box _lblUnknown;
    Fl_Browser _Unknown;
    Fl_Button _Refresh;
    Fl_Button _Login;
    Fl_Box    _User;
    Fl_Button _Quit;
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