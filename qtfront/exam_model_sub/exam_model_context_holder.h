#pragma once
#include "../context_holder.h"

namespace wally {
namespace qtfront {

class ExamModel;

namespace exam_model_sub {

class ExamModelContextHolder : public ContextHolder
{
public:
	void init(Context* context, ExamModel* model);

	ExamModel* examModel() const;

private:
	using ContextHolder::init;

	ExamModel*
	m_model;
};

}}}
