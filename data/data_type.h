#pragma once

namespace wally {
namespace data {

enum class DataType
{
	Null,
	Root,
	Dir,
	Image,
	Question,
	Exam,
	BlockContext,
	TextBlock,
	ImageBlock,
	BlockList,
	MultipleChoicesResp,
	MatchingResp,
	Choice,
	MatchingRespItem
};

}}
