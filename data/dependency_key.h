#pragma once

namespace wally {
namespace data {

constexpr size_t DependencyKeySize = 32/*bytes*/;

struct DependencyKey
{
	char data[DependencyKeySize];
};
bool operator <(DependencyKey const& first, DependencyKey const& second);

}}
