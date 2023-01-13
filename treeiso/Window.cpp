
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Window.h"
#include "Graph.h"
#include "GUI.h"

//------------------------------------------------------------------------------

namespace Graph_lib {

Window::Window(int ww, int hh, const string& title)
    :Fl_Window(ww,hh,title.c_str()),w(ww),h(hh)
{
    init();
}

//------------------------------------------------------------------------------

Window::Window(Point xy, int ww, int hh, const string& title)
    :Fl_Window(xy.x,xy.y,ww,hh,title.c_str()),w(ww),h(hh)
{ 
    init();
}

//------------------------------------------------------------------------------

void Window::init()
{
    resizable(this);
    show();
}

//------------------------------------------------------------------------------

void Window::draw()
{
    Fl_Window::draw();
    for (unsigned int i=0; i<shapes.size(); ++i) shapes[i]->draw();
}

//------------------------------------------------------------------------------

void Window::attach(Widget& w)
{
    begin();         // FTLK: begin attaching new Fl_Wigets to this window
    w.attach(*this); // let the Widget create its Fl_Wigits
    end();           // FTLK: stop attaching new Fl_Wigets to this window
}

//------------------------------------------------------------------------------

void Window::detach(Widget& b)
{
    b.hide();
}

//------------------------------------------------------------------------------

void Window::detach(Shape& s)
    // guess that the last attached will be first released
{
    for (unsigned int i = shapes.size(); 0<i; --i)    
        if (shapes[i-1]==&s)
            shapes.erase(shapes.begin()+(i-1));
}

//------------------------------------------------------------------------------

void Window::put_on_bottom(Shape& p) {
    for (int i=0; i<shapes.size(); ++i) {
        if (&p==shapes[i]) {//找到p的位置，对于在p之前的shape将其向后移动一个
            for (--i; i>=0; i--)
                shapes[i+1] = shapes[i];
            shapes[0] = &p;
            return;
        }
    }
}


//------------------------------------------------------------------------------

int gui_main()
{
    return Fl::run();
}

//------------------------------------------------------------------------------

}; // of namespace Graph_lib
