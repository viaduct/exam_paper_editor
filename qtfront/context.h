#pragma once
#include <memory>
#include <vector>

namespace wally {

namespace data {
class DependencyKey;

class Root;
class TreeItem;
class Dir;
class Exam;
class Question;
}

namespace qtfront {

class App;
class AppCmdManager;
class Loader;
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
