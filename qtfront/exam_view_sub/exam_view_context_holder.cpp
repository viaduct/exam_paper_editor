#include "exam_view_context_holder.h"

namespace wally {
namespace qtfront {
namespace exam_view_sub {

void ExamViewContextHolder::init(Context* context, ExamView* view)
{
	m_view = view;
	ContextHolder::init(context);
}

ExamView*ExamViewContextHolder::examView() const
{
	return m_view;
}

}}}
