#pragma once
#include "../context_holder.h"

namespace wally {
namespace qtfront {

class QuestionView;

namespace question_view_sub {

class QuestionViewContextHolder : public ContextHolder
{
public:
	void init(Context* context, QuestionView* view);

	QuestionView* questionView() const;

private:
	using ContextHolder::init;

	QuestionView*
	m_view;
};

}}}
