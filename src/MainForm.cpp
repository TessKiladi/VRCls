#include <Fl/Fl.H>
#include <FL/Fl_Double_Window.H>


class MainForm : public Fl_Double_Window
{
    public:
    MainForm()
    : Fl_Double_Window(640, 480, "VRCls")
    {

    }
    private:
};

int main(int argc, char * argv[])
{
  Fl::args(argc,argv);
  Fl::get_system_colors();
  Fl::scheme(Fl::scheme()); // init scheme before instantiating tests
  Fl::visual(FL_RGB);
  MainForm* theMainForm = new MainForm();


  theMainForm->show(argc,argv);
  return(Fl::run());
}