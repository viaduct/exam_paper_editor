#include "question_view_context_holder.h"

namespace wally {
namespace qtfront {
namespace question_view_sub {

void QuestionViewContextHolder::init(Context* context, QuestionView* view)
{
	m_view = view;
	ContextHolder::init(context);
}

QuestionView*QuestionViewContextHolder::questionView() const
{
	return m_view;
}

}}}
