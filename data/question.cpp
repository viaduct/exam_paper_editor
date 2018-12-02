#include "question.h"
#include "context.h"
#include "resp.h"

namespace wally {
namespace data {

Question::Question() :
	m_contextContainer(new ContextContainer(this)),
	m_respContainer(new RespContainer(this))
{
}

Question::~Question()
{
}

DataType Question::type() const
{
	return DataType::Question;
}

std::vector<const Container*> Question::containers() const
{
	auto result = File::containers();

	result.push_back(m_contextContainer.get());
	result.push_back(m_respContainer.get());

	return result;
}

const Question::ContextContainer*Question::contextContainer() const
{
	return m_contextContainer.get();
}

Question::ContextContainer*Question::contextContainer()
{
	return m_contextContainer.get();
}

const Question::RespContainer*Question::respContainer() const
{
	return m_respContainer.get();
}

Question::RespContainer*Question::respContainer()
{
	return m_respContainer.get();
}

}}
