#include "file.h"

namespace wally {
namespace data {

File::File()
{
}

File::~File()
{
}

std::vector<const Container*> File::containers() const
{
	auto result = TreeItem::containers();

	return result;
}

}}
