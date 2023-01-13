
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"

//------------------------------------------------------------------------------

Simple_window::Simple_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
    next_button(Point(x_max()-70,0), 100, 40, "Next", cb_next),
    button_pushed(false)
{
    
    //attach(next_button);
}

//------------------------------------------------------------------------------

bool Simple_window::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    show();
    button_pushed = false;
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait();//等待next+button被按下之前都进行忙等待
    Fl::redraw();
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return button_pushed;
}

//------------------------------------------------------------------------------

void Simple_window::cb_next(Graph_lib::Address, Graph_lib::Address pw)
// call Simple_window::next() for the window located at pw
{
    Graph_lib::reference_to<Simple_window>(pw).next_button.label = "pushed!";
    Graph_lib::reference_to<Simple_window>(pw).next();
}

//------------------------------------------------------------------------------

void Simple_window::next()//定义了按钮被按下时会发生的操作，即将button_pushed变量置真，同时hide()
{
    button_pushed = true;
}

//------------------------------------------------------------------------------

