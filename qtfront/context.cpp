#include <sstream>
#include <cstring>

#include <QFileDialog>

#include "context.h"
#include "app.h"
#include "app_cmd.h"
#include "app_cmd_manager.h"

#include "dir_context_var.h"
#include "opened_tree_item_context_var.h"
#include "drag_context_var.h"

#include "../data/single_container_cmd.h"
#include "../data/set_container_cmd.h"
#include "../data/list_container_cmd.h"
#include "../data/map_container_cmd.h"
#include "../data/single_prim_container_cmd.h"

#include "../data/tree_item.h"
#include "../data/dir.h"
#include "../data/exam.h"
#include "../data/question.h"
#include "../data/image.h"

#include "../data/dependency_key.h"

namespace wally {
namespace qtfront {

Context::Context() :
	m_dirContextVar(new DirContextVar),
	m_openedTreeItemContextVar(new OpenedTreeItemContextVar),
	m_dragContextVar(new DragContextVar)
{
}

Context::~Context()
{
}

App*Context::app()
{
	return m_app;
}

void Context::setApp(App* one)
{
	m_app = one;
}

data::Root*Context::root()
{
	return m_app->root();
}

AppCmdManager*Context::cmdManager()
{
	return m_app->cmdManager();
}

Loader*Context::loader()
{
	return m_app->loader();
}

DirContextVar*Context::dirContextVar()
{
	return m_dirContextVar.get();
}

OpenedTreeItemContextVar*Context::openedTreeItemContextVar()
{
	return m_openedTreeItemContextVar.get();
}

DragContextVar*Context::dragContextVar()
{
	return m_dragContextVar.get();
}

void Context::act_setTreeItemName(data::TreeItem* item, const std::string& name)
{
	if ( item->nameContainer()->single() != name )
	{
		auto changeName = std::make_shared<data::SetSinglePrim<std::string>>();
		changeName->setContainer(item->nameContainer());
		changeName->setValue(name);

		auto cmd = std::make_shared<AppDataCmd>(std::move(changeName));

		AppCmdInfo info;
		std::stringstream brief;
		brief << "Change file name from \"" << item->nameContainer()->single() << "\" to \"" << name << "\".";
		info.setBrief(brief.str());
		cmd->setInfo(std::move(info));

		cmdManager()->run(std::move(cmd));
	}
}

void Context::act_addDir(data::Dir* parentDir, const std::string& name)
{
	auto make = std::make_shared<data::CreateAddToSet<data::Dir, data::TreeItem>>();
	make->setContainer(parentDir->subItemContainer());
	auto setName = std::make_shared<data::SetSinglePrim<std::string>>();
	setName->setContainer(make->result()->nameContainer());
	setName->setValue(name);

	auto cmds = std::make_shared<data::DataCmdList>();
	cmds->reserve(2);
	cmds->append(std::move(make));
	cmds->append(std::move(setName));

	auto appCmd = std::make_shared<AppDataCmd>(std::move(cmds));

	AppCmdInfo info;
	std::stringstream brief;
	brief << "Add Directory with name \"" << name << "\".";
	info.setBrief(brief.str());
	appCmd->setInfo(std::move(info));

	cmdManager()->run(std::move(appCmd));
}

void Context::act_addExam(data::Dir* parentDir, const std::string& name)
{
	auto make = std::make_shared<data::CreateAddToSet<data::Exam, data::TreeItem>>();
	make->setContainer(parentDir->subItemContainer());
	auto setName = std::make_shared<data::SetSinglePrim<std::string>>();
	setName->setContainer(make->result()->nameContainer());
	setName->setValue(name);

	auto cmds = std::make_shared<data::DataCmdList>();
	cmds->reserve(2);
	cmds->append(std::move(make));
	cmds->append(std::move(setName));

	auto appCmd = std::make_shared<AppDataCmd>(std::move(cmds));

	AppCmdInfo info;
	std::stringstream brief;
	brief << "Add Exam with name \"" << name << "\".";
	info.setBrief(brief.str());
	appCmd->setInfo(std::move(info));

	cmdManager()->run(std::move(appCmd));
}

void Context::act_addQuestion(data::Dir* parentDir, const std::string& name)
{
	auto make = std::make_shared<data::CreateAddToSet<data::Question, data::TreeItem>>();
	make->setContainer(parentDir->subItemContainer());
	auto setName = std::make_shared<data::SetSinglePrim<std::string>>();
	setName->setContainer(make->result()->nameContainer());
	setName->setValue(name);

	auto cmds = std::make_shared<data::DataCmdList>();
	cmds->reserve(2);
	cmds->append(std::move(make));
	cmds->append(std::move(setName));

	auto appCmd = std::make_shared<AppDataCmd>(std::move(cmds));

	AppCmdInfo info;
	std::stringstream brief;
	brief << "Add Question with name \"" << name << "\".";
	info.setBrief(brief.str());
	appCmd->setInfo(std::move(info));

	cmdManager()->run(std::move(appCmd));
}

void Context::act_addImage(data::Dir* parentDir, const std::string& name)
{
	auto make = std::make_shared<data::CreateAddToSet<data::Image, data::TreeItem>>();
	make->setContainer(parentDir->subItemContainer());
	auto setName = std::make_shared<data::SetSinglePrim<std::string>>();
	setName->setContainer(make->result()->nameContainer());
	setName->setValue(name);

	auto cmds = std::make_shared<data::DataCmdList>();
	cmds->reserve(2);
	cmds->append(std::move(make));
	cmds->append(std::move(setName));

	auto appCmd = std::make_shared<AppDataCmd>(std::move(cmds));

	AppCmdInfo info;
	std::stringstream brief;
	brief << "Add Image with name \"" << name << "\".";
	info.setBrief(brief.str());
	appCmd->setInfo(std::move(info));

	cmdManager()->run(std::move(appCmd));
}

void Context::act_addImageFromFile(data::Dir* parentDir)
{
	auto fileName = QFileDialog::getOpenFileName();

	if ( fileName.isEmpty() == false )
	{
		// Load image based on the fileName.
		QImage image;
		auto imageLoadingResult = image.load(fileName);

		if ( imageLoadingResult == true )
		{
			auto makeImageItem = std::make_shared<data::CreateAddToSet<data::Image, data::TreeItem>>();
			makeImageItem->setContainer(parentDir->subItemContainer());
			auto setName = std::make_shared<data::SetSinglePrim<std::string>>();
			setName->setContainer(makeImageItem->result()->nameContainer());
			setName->setValue(fileName.toStdString());
			auto setImage = std::make_shared<data::SetSinglePrim<QImage>>();
			setImage->setContainer(makeImageItem->result()->imageContainer());
			setImage->setValue(image);

			auto cmds = std::make_shared<data::DataCmdList>();
			cmds->reserve(3);
			cmds->append(std::move(makeImageItem));
			cmds->append(std::move(setName));
			cmds->append(std::move(setImage));

			auto appCmd = std::make_shared<AppDataCmd>(std::move(cmds));

			AppCmdInfo info;
			std::stringstream brief;
			brief << "Add Image from file \"" << fileName.toStdString() << "\".";
			info.setBrief(brief.str());
			appCmd->setInfo(std::move(info));

			cmdManager()->run(std::move(appCmd));
		}
	}
}

void Context::act_removeFromDir(data::Dir* parentDir, const std::vector<data::TreeItem*>& targets)
{
	if ( targets.empty() == false )
	{
		auto cmds = std::make_shared<data::DataCmdList>();
		cmds->reserve(targets.size());

		for ( auto const& item : targets )
		{
			if ( item->parent() == parentDir )
			{
				auto remove = std::make_shared<data::RemoveFromSet<data::TreeItem>>();
				remove->setContainer(static_cast<data::Dir::SubItemContainer*>(item->parentContainer()));
				remove->setTarget(item);

				cmds->append(std::move(remove));
			}
		}

		auto appCmd = std::make_shared<AppDataCmd>(std::move(cmds));

		AppCmdInfo info;
		std::stringstream brief;
		brief << "Delete files from \"" << parentDir->nameContainer()->single() << "\".";
		info.setBrief(brief.str());
		appCmd->setInfo(std::move(info));

		cmdManager()->run(std::move(appCmd));
	}
}

data::DependencyKey dependencyKeyFromPtr(const void* value)
{
	static_assert(sizeof(data::DependencyKey) >= sizeof(nullptr), "DependencyKey has size smaller than a pointer.");

	data::DependencyKey result;
	memset(&result, 0, sizeof(data::DependencyKey));
	memcpy(&result, &value, sizeof(value));

	return result;
}

}}
