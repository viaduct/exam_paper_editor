#include "name_edit.h"
#include "../question_view.h"

namespace wally {
namespace qtfront {
namespace question_view_sub {

NameEdit::NameEdit(QWidget* parent) :
	QLineEdit(parent)
{
}

void NameEdit::focusOutEvent(QFocusEvent* event)
{
	(void)event;
	if ( questionView()->m_question )
	{
		questionView()->pushName();
	}
}

void NameEdit::initialized()
{
}

}}}
