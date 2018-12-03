#include "exam_model_context_holder.h"

namespace wally {
namespace qtfront {
namespace exam_model_sub {

void ExamModelContextHolder::init(Context* context, ExamModel* model)
{
	m_model = model;
	ContextHolder::init(context);
}

ExamModel*ExamModelContextHolder::examModel() const
{
	return m_model;
}

}}}
