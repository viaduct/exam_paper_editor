#pragma once
#include "file.h"

namespace wally {
namespace data {

class Context;
class Resp;

class Question : public File
{
public:
	using ContextContainer = SingleContainer<Context, std::shared_ptr<Context>>;
	using RespContainer = SingleContainer<Resp, std::shared_ptr<Resp>>;

	Question();
	virtual ~Question();

	DataType type() const override final;
	std::vector<Container const*> containers() const override final;

	ContextContainer const* contextContainer() const;
	ContextContainer* contextContainer();
	RespContainer const* respContainer() const;
	RespContainer* respContainer();

private:
	std::unique_ptr<ContextContainer>
	m_contextContainer;

	std::unique_ptr<RespContainer>
	m_respContainer;
};

}}
