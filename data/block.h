#pragma once
#include "data.h"

namespace wally {
namespace data {

class Block : public Data
{
public:
	Block();
	virtual ~Block();

	std::vector<Container const*> containers() const override;

private:
};

}}
