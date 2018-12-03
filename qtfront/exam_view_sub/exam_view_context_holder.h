#pragma once
#include "../context_holder.h"

namespace wally {
namespace qtfront {

class ExamView;

namespace exam_view_sub {

class ExamViewContextHolder : public ContextHolder
{
public:
	void init(Context* context, ExamView* view);

	ExamView* examView() const;

private:
	using ContextHolder::init;

	ExamView*
	m_view;
};

}}}
