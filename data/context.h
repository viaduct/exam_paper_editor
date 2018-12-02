#pragma once
#include "data.h"

namespace wally {
namespace data {

class Context : public Data
{
public:
	Context();
	virtual ~Context();

	std::vector<Container const*> containers() const override;

private:
};

}}
