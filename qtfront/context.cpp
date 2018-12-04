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
#include "../data/text_block.h"
#include "../data/image_block.h"
#include "../data/block_list.h"
#include "../data/choice.h"
#include "../data/matching_resp_item.h"
#include "../data/matching_resp.h"
#include "../data/multiple_choices_resp.h"
#include "../data/block_context.h"

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

void Context::act_appendExamQuestions(data::Exam* exam, std::vector<data::Question*> const& questions)
{
	auto cmds = std::make_shared<data::DataCmdList>();

	for ( auto& question : questions )
	{
		if ( !exam->questionContainer()->has(question) )
		{
			auto add = std::make_shared<data::AppendRefToList<data::Question>>();
			add->setContainer(exam->questionContainer());
			add->setData(question);

			cmds->append(std::move(add));
		}
	}

	if ( cmds->isEmpty() == false )
	{
		auto appCmd = std::make_shared<AppDataCmd>(std::move(cmds));

		AppCmdInfo info;
		std::stringstream brief;
		brief << "Append Exam Questions.";
		info.setBrief(brief.str());
		appCmd->setInfo(std::move(info));

		cmdManager()->run(std::move(appCmd));
	}
}

void Context::act_removeExamQuestions(data::Exam* exam, const std::vector<data::Question*>& questions)
{
	auto cmds = std::make_shared<data::DataCmdList>();

	for ( auto& question : questions )
	{
		bool isValid;
		auto index = exam->questionContainer()->index(question, &isValid);

		if ( isValid )
		{
			auto remove = std::make_shared<data::RemoveRefFromList<data::Question>>();
			remove->setContainer(exam->questionContainer());
			remove->setTarget(index);

			cmds->append(std::move(remove));
		}
	}

	if ( cmds->isEmpty() == false )
	{
		auto appCmd = std::make_shared<AppDataCmd>(std::move(cmds));

		AppCmdInfo info;
		std::stringstream brief;
		brief << "Delete Exam Questions.";
		info.setBrief(brief.str());
		appCmd->setInfo(std::move(info));

		cmdManager()->run(std::move(appCmd));
	}
}

void Context::act_moveExamQuestionUp(data::Exam* exam, data::Question* question)
{
	bool isExamHasQuestion;
	auto questionIndex = exam->questionContainer()->index(question, &isExamHasQuestion);

	if ( isExamHasQuestion )
	{
		if ( questionIndex != 0 )
		{
			auto move = std::make_shared<data::MoveRefList<data::Question>>();
			move->setContainer(exam->questionContainer());
			move->setTarget(questionIndex, questionIndex - 1);

			auto appCmd = std::make_shared<AppDataCmd>(std::move(move));

			AppCmdInfo info;
			std::stringstream brief;
			brief << "Move Exam Question up.";
			info.setBrief(brief.str());
			appCmd->setInfo(std::move(info));

			cmdManager()->run(std::move(appCmd));
		}
	}
}

void Context::act_moveExamQuestionDown(data::Exam* exam, data::Question* question)
{
	bool isExamHasQuestion;
	auto questionIndex = exam->questionContainer()->index(question, &isExamHasQuestion);

	if ( isExamHasQuestion )
	{
		if ( questionIndex != exam->questionContainer()->size() - 1 )
		{
			auto move = std::make_shared<data::MoveRefList<data::Question>>();
			move->setContainer(exam->questionContainer());
			move->setTarget(questionIndex, questionIndex + 1);

			auto appCmd = std::make_shared<AppDataCmd>(std::move(move));

			AppCmdInfo info;
			std::stringstream brief;
			brief << "Move Exam Question down.";
			info.setBrief(brief.str());
			appCmd->setInfo(std::move(info));

			cmdManager()->run(std::move(appCmd));
		}
	}
}

void Context::act_setTextBlockText(data::TextBlock* item, const std::string& text)
{
	// Check the new text is really different from the original one.
	if ( item->textContainer()->single() != text )
	{
		auto changeText = std::make_shared<data::SetSinglePrim<std::string>>();
		changeText->setContainer(item->textContainer());
		changeText->setValue(text);

		auto appCmd = std::make_shared<AppDataCmd>(std::move(changeText));

		AppCmdInfo info;
		std::stringstream brief;
		brief << "Change Text Block \"" << item->textContainer()->single() << "\" text.";
		info.setBrief(brief.str());
		appCmd->setInfo(std::move(info));

		cmdManager()->run(std::move(appCmd));
	}
}

void Context::act_setChoiceText(data::Choice* choice, const std::string& text)
{
	if ( choice->textContainer()->single() != text )
	{
		auto changeText = std::make_shared<data::SetSinglePrim<std::string>>();
		changeText->setContainer(choice->textContainer());
		changeText->setValue(text);

		auto appCmd = std::make_shared<AppDataCmd>(std::move(changeText));

		AppCmdInfo info;
		std::stringstream brief;
		brief << "Change Choice \"" << choice->textContainer()->single() << "\" text.";
		info.setBrief(brief.str());
		appCmd->setInfo(std::move(info));

		cmdManager()->run(std::move(appCmd));
	}
}

void Context::act_setMatchingRespItemText(data::MatchingRespItem* item, const std::string& text)
{
	if ( item->textContainer()->single() != text )
	{
		auto changeText = std::make_shared<data::SetSinglePrim<std::string>>();
		changeText->setContainer(item->textContainer());
		changeText->setValue(text);

		auto appCmd = std::make_shared<AppDataCmd>(std::move(changeText));

		AppCmdInfo info;
		std::stringstream brief;
		brief << "Change Matching Reponse Item \"" << item->textContainer()->single() << "\" text.";
		info.setBrief(brief.str());
		appCmd->setInfo(std::move(info));

		cmdManager()->run(std::move(appCmd));
	}
}

void Context::act_appendMatchingRespItem(data::ListContainer<data::MatchingRespItem, std::shared_ptr<data::MatchingRespItem>>* container, std::string const& text)
{
	auto make = std::make_shared<data::CreateAppendToList<data::MatchingRespItem>>();
	make->setContainer(container);
	auto setText = std::make_shared<data::SetSinglePrim<std::string>>();
	setText->setContainer(make->result()->textContainer());
	setText->setValue(text);

	auto cmds = std::make_shared<data::DataCmdList>();
	cmds->reserve(2);
	cmds->append(std::move(make));
	cmds->append(std::move(setText));

	auto appCmd = std::make_shared<AppDataCmd>(std::move(cmds));

	AppCmdInfo info;
	std::stringstream brief;
	brief << "Append Matching Response Item.";
	info.setBrief(brief.str());
	appCmd->setInfo(std::move(info));

	cmdManager()->run(std::move(appCmd));
}

void Context::act_removeMatchingRespItem(data::MatchingRespItem* item)
{
	if ( item->parentContainer() )
	{
		if ( item->parentContainer()->type() == data::ContainerType::List )
		{
			auto container = static_cast<data::ListContainer<data::MatchingRespItem, std::shared_ptr<data::MatchingRespItem>>*>(item->parentContainer());
			auto index = container->index(item);

			auto remove = std::make_shared<data::RemoveFromList<data::MatchingRespItem>>();
			remove->setContainer(container);
			remove->setTarget(index);

			auto appCmd = std::make_shared<AppDataCmd>(std::move(remove));

			AppCmdInfo info;
			std::stringstream brief;
			brief << "Delete Matching Response Item.";
			info.setBrief(brief.str());
			appCmd->setInfo(std::move(info));

			cmdManager()->run(std::move(appCmd));
		}
		else
		{
			assert(false);
		}
	}
}

void Context::act_moveMatchingRespItemUp(data::MatchingRespItem* item)
{
	if ( item->parentContainer() )
	{
		assert(item->parentContainer()->type() == data::ContainerType::List);

		auto container = static_cast<data::ListContainer<data::MatchingRespItem, std::shared_ptr<data::MatchingRespItem>>*>(item->parentContainer());
		auto index = container->index(item);

		if ( index != 0 )
		{
			auto move = std::make_shared<data::MoveList<data::MatchingRespItem>>();
			move->setContainer(container);
			move->setTarget(index, index - 1);

			auto appCmd = std::make_shared<AppDataCmd>(std::move(move));

			AppCmdInfo info;
			std::stringstream brief;
			brief << "Move Matching Response Item up.";
			info.setBrief(brief.str());
			appCmd->setInfo(std::move(info));

			cmdManager()->run(std::move(appCmd));
		}
	}
}

void Context::act_moveMatchingRespItemDown(data::MatchingRespItem* item)
{
	if ( item->parentContainer() )
	{
		assert(item->parentContainer()->type() == data::ContainerType::List);

		auto container = static_cast<data::ListContainer<data::MatchingRespItem, std::shared_ptr<data::MatchingRespItem>>*>(item->parentContainer());
		auto index = container->index(item);

		if ( index != container->size() - 1 )
		{
			auto move = std::make_shared<data::MoveList<data::MatchingRespItem>>();
			move->setContainer(container);
			move->setTarget(index, index + 1);

			auto appCmd = std::make_shared<AppDataCmd>(std::move(move));

			AppCmdInfo info;
			std::stringstream brief;
			brief << "Move Matching Response Item down.";
			info.setBrief(brief.str());
			appCmd->setInfo(std::move(info));

			cmdManager()->run(std::move(appCmd));
		}
	}
}

void Context::act_appendTextBlock(data::ListContainer<data::Block, std::shared_ptr<data::Block>>* container, std::string const& text)
{
	auto make = std::make_shared<data::CreateAppendToList<data::TextBlock, data::Block>>();
	make->setContainer(container);
	auto setText = std::make_shared<data::SetSinglePrim<std::string>>();
	setText->setContainer(make->result()->textContainer());
	setText->setValue(text);

	auto cmds = std::make_shared<data::DataCmdList>();
	cmds->reserve(2);
	cmds->append(std::move(make));
	cmds->append(std::move(setText));

	auto appCmd = std::make_shared<AppDataCmd>(std::move(cmds));

	AppCmdInfo info;
	std::stringstream brief;
	brief << "Append Text Block.";
	info.setBrief(brief.str());
	appCmd->setInfo(std::move(info));

	cmdManager()->run(std::move(appCmd));
}

void Context::act_appendImageBlock(data::ListContainer<data::Block, std::shared_ptr<data::Block> >* container)
{
	auto make = std::make_shared<data::CreateAppendToList<data::ImageBlock, data::Block>>();
	make->setContainer(container);

	auto appCmd = std::make_shared<AppDataCmd>(std::move(make));

	AppCmdInfo info;
	std::stringstream brief;
	brief << "Append Image Block.";
	info.setBrief(brief.str());
	appCmd->setInfo(std::move(info));

	cmdManager()->run(std::move(appCmd));
}

void Context::act_removeBlock(data::Block* block)
{
	using BlockContainerType = data::ListContainer<data::Block, std::shared_ptr<data::Block>>;

	if ( block->parentContainer() )
	{
		if ( block->parentContainer()->type() == data::ContainerType::List )
		{
			auto remove = std::make_shared<data::RemoveFromList<data::Block>>();
			remove->setContainer(static_cast<BlockContainerType*>(block->parentContainer()));
			remove->setTarget(static_cast<BlockContainerType*>(block->parentContainer())->index(block));

			auto appCmd = std::make_shared<AppDataCmd>(std::move(remove));

			AppCmdInfo info;
			std::stringstream brief;
			brief << "Delete Block.";
			info.setBrief(brief.str());
			appCmd->setInfo(std::move(info));

			cmdManager()->run(std::move(appCmd));
		}
		else
		{
			assert(false);
		}
	}
}

void Context::act_moveBlockUp(data::Block* block)
{
	using BlockContainerType = data::ListContainer<data::Block, std::shared_ptr<data::Block>>;

	if ( block->parentContainer() )
	{
		assert(block->parentContainer()->type() == data::ContainerType::List);

		auto container = static_cast<BlockContainerType*>(block->parentContainer());
		auto index = container->index(block);

		if ( index != 0 )
		{
			auto move = std::make_shared<data::MoveList<data::Block>>();
			move->setContainer(container);
			move->setTarget(index, index - 1);

			auto appCmd = std::make_shared<AppDataCmd>(std::move(move));

			AppCmdInfo info;
			std::stringstream brief;
			brief << "Move Block up.";
			info.setBrief(brief.str());
			appCmd->setInfo(std::move(info));

			cmdManager()->run(std::move(appCmd));
		}
	}
}

void Context::act_moveBlockDown(data::Block* block)
{
	using BlockContainerType = data::ListContainer<data::Block, std::shared_ptr<data::Block>>;

	if ( block->parentContainer() )
	{
		assert(block->parentContainer()->type() == data::ContainerType::List);

		auto container = static_cast<BlockContainerType*>(block->parentContainer());
		auto index = container->index(block);

		if ( index != container->size() - 1 )
		{
			auto move = std::make_shared<data::MoveList<data::Block>>();
			move->setContainer(container);
			move->setTarget(index, index + 1);

			auto appCmd = std::make_shared<AppDataCmd>(std::move(move));

			AppCmdInfo info;
			std::stringstream brief;
			brief << "Move Block down.";
			info.setBrief(brief.str());
			appCmd->setInfo(std::move(info));

			cmdManager()->run(std::move(appCmd));
		}
	}
}

void Context::act_removeContext(data::Container* container_)
{
	assert(container_->type() == data::ContainerType::Single);
	auto container = static_cast<data::SingleContainer<data::Context, std::shared_ptr<data::Context>>*>(container_);

	if ( container->isValid() == true )
	{
		auto remove = std::make_shared<data::UnsetFromSingle<data::Context>>();
		remove->setContainer(container);

		auto appCmd = std::make_shared<AppDataCmd>(std::move(remove));

		AppCmdInfo info;
		std::stringstream brief;
		brief << "Delete Context.";
		info.setBrief(brief.str());
		appCmd->setInfo(std::move(info));

		cmdManager()->run(std::move(appCmd));
	}
}

void Context::act_removeResp(data::Container* container_)
{
	assert(container_->type() == data::ContainerType::Single);
	auto container = static_cast<data::SingleContainer<data::Resp, std::shared_ptr<data::Resp>>*>(container_);

	if ( container->isValid() == true )
	{
		auto remove = std::make_shared<data::UnsetFromSingle<data::Resp>>();
		remove->setContainer(container);

		auto appCmd = std::make_shared<AppDataCmd>(std::move(remove));

		AppCmdInfo info;
		std::stringstream brief;
		brief << "Delete Response.";
		info.setBrief(brief.str());
		appCmd->setInfo(std::move(info));

		cmdManager()->run(std::move(appCmd));
	}
}

void Context::act_setImageBlockImage(data::ImageBlock* block, data::Image* image)
{
	auto cmds = std::make_shared<data::DataCmdList>();

	// If there's image already, remove it first.
	if ( block->imageContainer()->isValid() )
	{
		auto remove = std::make_shared<data::UnsetRefFromSingle<data::Image>>();
		remove->setContainer(block->imageContainer());

		cmds->append(std::move(remove));
	}

	// Now set image.
	auto setImage = std::make_shared<data::SetRefToSingle<data::Image>>();
	setImage->setContainer(block->imageContainer());
	setImage->setData(image);
	cmds->append(std::move(setImage));

	auto appCmd = std::make_shared<AppDataCmd>(std::move(cmds));

	AppCmdInfo info;
	std::stringstream brief;
	brief << "Set Image to Block Image.";
	info.setBrief(brief.str());
	appCmd->setInfo(std::move(info));

	cmdManager()->run(std::move(appCmd));
}

void Context::act_appendChoice(data::ListContainer<data::Choice, std::shared_ptr<data::Choice> >* container, std::string const& text)
{
	auto make = std::make_shared<data::CreateAppendToList<data::Choice>>();
	make->setContainer(container);
	auto setText = std::make_shared<data::SetSinglePrim<std::string>>();
	setText->setContainer(make->result()->textContainer());
	setText->setValue(text);

	auto cmds = std::make_shared<data::DataCmdList>();
	cmds->reserve(2);
	cmds->append(std::move(make));
	cmds->append(std::move(setText));

	auto appCmd = std::make_shared<AppDataCmd>(std::move(cmds));

	AppCmdInfo info;
	std::stringstream brief;
	brief << "Append Choice.";
	info.setBrief(brief.str());
	appCmd->setInfo(std::move(info));

	cmdManager()->run(std::move(appCmd));
}

void Context::act_removeChoice(data::Choice* choice)
{
	if ( choice->parentContainer() )
	{
		if ( choice->parentContainer()->type() == data::ContainerType::List )
		{
			auto container = static_cast<data::ListContainer<data::Choice, std::shared_ptr<data::Choice>>*>(choice->parentContainer());
			auto index = container->index(choice);

			auto remove = std::make_shared<data::RemoveFromList<data::Choice>>();
			remove->setContainer(container);
			remove->setTarget(index);

			auto appCmd = std::make_shared<AppDataCmd>(std::move(remove));

			AppCmdInfo info;
			std::stringstream brief;
			brief << "Delete Choice.";
			info.setBrief(brief.str());
			appCmd->setInfo(std::move(info));

			cmdManager()->run(std::move(appCmd));
		}
		else
		{
			assert(false);
		}
	}
}

void Context::act_moveChoiceUp(data::Choice* choice)
{
	if ( choice->parentContainer() )
	{
		assert(choice->parentContainer()->type() == data::ContainerType::List);

		auto container = static_cast<data::ListContainer<data::Choice, std::shared_ptr<data::Choice>>*>(choice->parentContainer());
		auto index = container->index(choice);

		if ( index != 0 )
		{
			auto move = std::make_shared<data::MoveList<data::Choice>>();
			move->setContainer(container);
			move->setTarget(index, index - 1);

			auto appCmd = std::make_shared<AppDataCmd>(std::move(move));

			AppCmdInfo info;
			std::stringstream brief;
			brief << "Move Choice up.";
			info.setBrief(brief.str());
			appCmd->setInfo(std::move(info));

			cmdManager()->run(std::move(appCmd));
		}
	}
}

void Context::act_moveChoiceDown(data::Choice* choice)
{
	if ( choice->parentContainer() )
	{
		assert(choice->parentContainer()->type() == data::ContainerType::List);

		auto container = static_cast<data::ListContainer<data::Choice, std::shared_ptr<data::Choice>>*>(choice->parentContainer());
		auto index = container->index(choice);

		if ( index != container->size() - 1 )
		{
			auto move = std::make_shared<data::MoveList<data::Choice>>();
			move->setContainer(container);
			move->setTarget(index, index + 1);

			auto appCmd = std::make_shared<AppDataCmd>(std::move(move));

			AppCmdInfo info;
			std::stringstream brief;
			brief << "Move Choice down.";
			info.setBrief(brief.str());
			appCmd->setInfo(std::move(info));

			cmdManager()->run(std::move(appCmd));
		}
	}
}

void Context::act_addBlockContext(data::SingleContainer<data::Context, std::shared_ptr<data::Context> >* container)
{
	if ( container->isValid() == false )
	{
		auto makeBlockContext = std::make_shared<data::CreateSetToSingle<data::BlockContext, data::Context>>();
		makeBlockContext->setContainer(container);

		auto makeBlockList = std::make_shared<data::CreateSetToSingle<data::BlockList>>();
		makeBlockList->setContainer(makeBlockContext->result()->rootBlockContainer());

		auto cmds = std::make_shared<data::DataCmdList>();
		cmds->reserve(2);
		cmds->append(std::move(makeBlockContext));
		cmds->append(std::move(makeBlockList));

		auto appCmd = std::make_shared<AppDataCmd>(std::move(cmds));

		AppCmdInfo info;
		std::stringstream brief;
		brief << "Add Block Context.";
		info.setBrief(brief.str());
		appCmd->setInfo(std::move(info));

		cmdManager()->run(std::move(appCmd));
	}
}

void Context::act_addMultipleChoicesResp(data::SingleContainer<data::Resp, std::shared_ptr<data::Resp> >* container)
{
	if ( container->isValid() == false )
	{
		auto make = std::make_shared<data::CreateSetToSingle<data::MultipleChoicesResp, data::Resp>>();
		make->setContainer(container);

		auto appCmd = std::make_shared<AppDataCmd>(std::move(make));

		AppCmdInfo info;
		std::stringstream brief;
		brief << "Add Multiple Choices Response.";
		info.setBrief(brief.str());
		appCmd->setInfo(std::move(info));

		cmdManager()->run(std::move(appCmd));
	}
}

void Context::act_addMatchingResp(data::SingleContainer<data::Resp, std::shared_ptr<data::Resp> >* container)
{
	if ( container->isValid() == false )
	{
		auto make = std::make_shared<data::CreateSetToSingle<data::MatchingResp, data::Resp>>();
		make->setContainer(container);

		auto appCmd = std::make_shared<AppDataCmd>(std::move(make));

		AppCmdInfo info;
		std::stringstream brief;
		brief << "Add Matching Response.";
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
