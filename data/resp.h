#pragma once
#include "data.h"

namespace wally {
namespace data {

class Resp : public Data
{
public:
	Resp();
	virtual ~Resp();

	std::vector<Container const*> containers() const override;

private:
};

}}
