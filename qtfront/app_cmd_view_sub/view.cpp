#include "view.h"
#include "../context.h"
#include "../app_cmd_manager.h"
#include "../app_cmd_model.h"

namespace wally {
namespace qtfront {
namespace app_cmd_view_sub {

View::View(QWidget* parent) : QListView(parent)
{
}

View::~View()
{
}

void View::initialized()
{
}

}}}
