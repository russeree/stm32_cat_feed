#include <gui/main_menu_screen/main_menuView.hpp>
#include <gui/main_menu_screen/main_menuPresenter.hpp>

main_menuPresenter::main_menuPresenter(main_menuView& v)
    : view(v)
{

}

void main_menuPresenter::activate()
{

}

void main_menuPresenter::deactivate()
{

}

void main_menuPresenter::updateRngStatusModel(bool value){
	view.rngStatusUpdate(value);
}
