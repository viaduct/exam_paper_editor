#pragma once
#include "tree_item.h"

namespace wally {
namespace data {

class File : public TreeItem
{
public:
	File();
	virtual ~File();

	std::vector<Container const*> containers() const override;

private:
};

}}
