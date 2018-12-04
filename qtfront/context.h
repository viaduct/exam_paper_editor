#pragma once
#include <memory>
#include <vector>

namespace wally {

namespace data {
class DependencyKey;

class Container;
template <typename T, typename Ptr> class SingleContainer;
template <typename T, typename Ptr> class ListContainer;
template <typename T, typename Ptr> class SetContainer;
template <typename K, typename V, typename Ptr> class MapContainer;
template <typename T> class SinglePrimContainer;

class Root;
class TreeItem;
class Dir;
class Exam;
class Question;
class TextBlock;
class Choice;
class MatchingRespItem;
class MatchingResp;
class Block;
class ImageBlock;
class Image;
class Context;
class Resp;
}

namespace qtfront {

class App;
class AppCmdManager;
class Loader;
class AppCmdModel;
class DirContextVar;
class OpenedTreeItemContextVar;
class DragContextVar;

class Context
{
public:
	Context();
	~Context();
	Context(Context const&) = delete;
	Context& operator =(Context const&) = delete;

	App* app();
	void setApp(App* one);

	// Getters for conveniences.
	data::Root* root();
	AppCmdManager* cmdManager();
	Loader* loader();
	AppCmdModel* cmdModel();

	DirContextVar* dirContextVar();
	OpenedTreeItemContextVar* openedTreeItemContextVar();
	DragContextVar* dragContextVar();

	void act_setTreeItemName(data::TreeItem* item, std::string const& name);

	void act_addDir(data::Dir* parentDir, std::string const& name);
	void act_addExam(data::Dir* parentDir, std::string const& name);
	void act_addQuestion(data::Dir* parentDir, std::string const& name);
	void act_addImage(data::Dir* parentDir, std::string const& name);
	void act_addImageFromFile(data::Dir* parentDir);

	void act_removeFromDir(data::Dir* parentDir, std::vector<data::TreeItem*> const& targets);
	void act_appendExamQuestions(data::Exam* exam, std::vector<data::Question*> const& questions);
	void act_removeExamQuestions(data::Exam* exam, std::vector<data::Question*> const& questions);
	void act_moveExamQuestionUp(data::Exam* exam, data::Question* question);
	void act_moveExamQuestionDown(data::Exam* exam, data::Question* question);

	void act_setTextBlockText(data::TextBlock* item, std::string const& text);
	void act_setChoiceText(data::Choice* choice, std::string const& text);

	void act_setMatchingRespItemText(data::MatchingRespItem* item, std::string const& text);
	void act_appendMatchingRespItem(data::ListContainer<data::MatchingRespItem, std::shared_ptr<data::MatchingRespItem>>* container, std::string const& text);
	void act_removeMatchingRespItem(data::MatchingRespItem* item);
	void act_moveMatchingRespItemUp(data::MatchingRespItem* item);
	void act_moveMatchingRespItemDown(data::MatchingRespItem* item);

	void act_appendTextBlock(data::ListContainer<data::Block, std::shared_ptr<data::Block>>* container, std::string const& text);
	void act_appendImageBlock(data::ListContainer<data::Block, std::shared_ptr<data::Block>>* container);
	void act_removeBlock(data::Block* block);
	void act_moveBlockUp(data::Block* block);
	void act_moveBlockDown(data::Block* block);

	void act_removeContext(data::Container* container);
	void act_removeResp(data::Container* container);

	void act_setImageBlockImage(data::ImageBlock* block, data::Image* image);

	void act_appendChoice(data::ListContainer<data::Choice, std::shared_ptr<data::Choice>>* container, std::string const& text);
	void act_removeChoice(data::Choice* choice);
	void act_moveChoiceUp(data::Choice* choice);
	void act_moveChoiceDown(data::Choice* choice);

	void act_addBlockContext(data::SingleContainer<data::Context, std::shared_ptr<data::Context>>* container);
	void act_addMultipleChoicesResp(data::SingleContainer<data::Resp, std::shared_ptr<data::Resp>>* container);
	void act_addMatchingResp(data::SingleContainer<data::Resp, std::shared_ptr<data::Resp>>* container);

private:
	std::unique_ptr<DirContextVar>
	m_dirContextVar;
	std::unique_ptr<OpenedTreeItemContextVar>
	m_openedTreeItemContextVar;
	std::unique_ptr<DragContextVar>
	m_dragContextVar;

	App*
	m_app;
};

extern data::DependencyKey dependencyKeyFromPtr(void const* value);

}}
