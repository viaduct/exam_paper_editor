#include <cstring>
#include "dependency_key.h"

namespace wally {
namespace data {

bool operator <(const DependencyKey& first, const DependencyKey& second)
{
	return memcmp(&first, &second, DependencyKeySize) < 0;
}

}}
