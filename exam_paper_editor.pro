#-------------------------------------------------
#
# Project created by QtCreator 2018-12-01T23:08:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = exam_paper_editor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14
CONFIG += object_parallel_to_source

SOURCES += \
    main.cpp \
    data/data.cpp \
    data/data_cmd.cpp \
    data/dependency_key.cpp \
    data/container.cpp \
    data/single_container.cpp \
    data/map_container.cpp \
    data/list_container.cpp \
    data/set_container.cpp \
    data/single_prim_container.cpp \
    data/root.cpp \
    data/dir.cpp \
    data/image.cpp \
    data/question.cpp \
    data/exam.cpp \
    data/block_context.cpp \
    data/text_block.cpp \
    data/image_block.cpp \
    data/block_list.cpp \
    data/multiple_choices_resp.cpp \
    data/matching_resp.cpp \
    data/choice.cpp \
    data/matching_resp_item.cpp \
    data/block.cpp \
    data/context.cpp \
    data/file.cpp \
    data/tree_item.cpp \
    data/resp.cpp \
    data/single_container_cmd.cpp \
    data/single_prim_container_cmd.cpp \
    data/list_container_cmd.cpp \
    data/set_container_cmd.cpp \
    data/map_container_cmd.cpp \
    qtfront/app.cpp \
    qtfront/loader.cpp \
    qtfront/app_cmd_manager.cpp \
    qtfront/context.cpp \
    qtfront/main_window.cpp \
    qtfront/context_holder.cpp \
    qtfront/app_cmd.cpp \
    qtfront/dir_context_var.cpp \
    qtfront/drag_context_var.cpp \
    qtfront/opened_tree_item_context_var.cpp \
    qtfront/tree_item_model_sub/dir_mimic.cpp \
    qtfront/tree_item_model_sub/tree_item_mimic.cpp \
    qtfront/tree_item_model_sub/tree_item_model_context_holder.cpp \
    qtfront/tree_item_view_sub/tree_item_view_context_holder.cpp \
    qtfront/tree_item_view_sub/view.cpp \
    qtfront/click_event_emitter.cpp \
    qtfront/tree_item_model.cpp \
    qtfront/tree_item_view.cpp \
    qtfront/app_cmd_info.cpp \
    qtfront/exam_model_sub/exam_mimic.cpp \
    qtfront/exam_model_sub/exam_model_context_holder.cpp \
    qtfront/exam_model_sub/question_mimic.cpp \
    qtfront/exam_view_sub/exam_view_context_holder.cpp \
    qtfront/exam_view_sub/list_view.cpp \
    qtfront/exam_view_sub/name_edit.cpp \
    qtfront/exam_html_exporter.cpp \
    qtfront/exam_model.cpp \
    qtfront/exam_view.cpp \
    qtfront/question_view.cpp \
    qtfront/question_view_sub/block_context_mimic.cpp \
    qtfront/question_view_sub/block_list_mimic.cpp \
    qtfront/question_view_sub/block_mimic.cpp \
    qtfront/question_view_sub/choice_mimic.cpp \
    qtfront/question_view_sub/context_mimic.cpp \
    qtfront/question_view_sub/image_block_mimic.cpp \
    qtfront/question_view_sub/image_mimic.cpp \
    qtfront/question_view_sub/matching_resp_item_mimic.cpp \
    qtfront/question_view_sub/matching_resp_mimic.cpp \
    qtfront/question_view_sub/multiple_choices_resp_mimic.cpp \
    qtfront/question_view_sub/question_mimic.cpp \
    qtfront/question_view_sub/question_view_context_holder.cpp \
    qtfront/question_view_sub/resp_mimic.cpp \
    qtfront/question_view_sub/text_block_mimic.cpp \
    qtfront/question_view_sub/name_edit.cpp \
    qtfront/app_cmd_model_sub/app_cmd_model_context_holder.cpp \
    qtfront/app_cmd_model_sub/cmd_manager_mimic.cpp \
    qtfront/app_cmd_view_sub/app_cmd_view_context_holder.cpp \
    qtfront/app_cmd_view_sub/view.cpp \
    qtfront/app_cmd_model.cpp \
    qtfront/app_cmd_view.cpp \
    qtfront/editor_view.cpp

HEADERS += \
    data/data.h \
    data/data_cmd.h \
    data/data_type.h \
    data/dependency_key.h \
    data/container.h \
    data/container_type.h \
    data/type_enum_ref.h \
    data/single_container.h \
    data/map_container.h \
    data/list_container.h \
    data/set_container.h \
    data/single_prim_container.h \
    data/root.h \
    data/dir.h \
    data/image.h \
    data/question.h \
    data/exam.h \
    data/block_context.h \
    data/text_block.h \
    data/image_block.h \
    data/block_list.h \
    data/multiple_choices_resp.h \
    data/matching_resp.h \
    data/choice.h \
    data/matching_resp_item.h \
    data/block.h \
    data/context.h \
    data/file.h \
    data/tree_item.h \
    data/resp.h \
    data/single_container_cmd.h \
    data/single_prim_container_cmd.h \
    data/list_container_cmd.h \
    data/set_container_cmd.h \
    data/map_container_cmd.h \
    qtfront/app.h \
    qtfront/loader.h \
    qtfront/app_cmd_manager.h \
    qtfront/context.h \
    qtfront/main_window.h \
    qtfront/context_holder.h \
    qtfront/app_cmd.h \
    qtfront/dir_context_var.h \
    qtfront/drag_context_var.h \
    qtfront/opened_tree_item_context_var.h \
    qtfront/tree_item_model_sub/dir_mimic.h \
    qtfront/tree_item_model_sub/tree_item_mimic.h \
    qtfront/tree_item_model_sub/tree_item_model_context_holder.h \
    qtfront/tree_item_view_sub/tree_item_view_context_holder.h \
    qtfront/tree_item_view_sub/view.h \
    qtfront/click_event_emitter.h \
    qtfront/tree_item_model.h \
    qtfront/tree_item_view.h \
    qtfront/app_cmd_info.h \
    qtfront/exam_model_sub/exam_mimic.h \
    qtfront/exam_model_sub/exam_model_context_holder.h \
    qtfront/exam_model_sub/question_mimic.h \
    qtfront/exam_view_sub/exam_view_context_holder.h \
    qtfront/exam_view_sub/list_view.h \
    qtfront/exam_view_sub/name_edit.h \
    qtfront/exam_html_exporter.h \
    qtfront/exam_model.h \
    qtfront/exam_view.h \
    qtfront/question_view.h \
    qtfront/question_view_sub/block_context_mimic.h \
    qtfront/question_view_sub/block_list_mimic.h \
    qtfront/question_view_sub/block_mimic.h \
    qtfront/question_view_sub/choice_mimic.h \
    qtfront/question_view_sub/context_mimic.h \
    qtfront/question_view_sub/image_block_mimic.h \
    qtfront/question_view_sub/image_mimic.h \
    qtfront/question_view_sub/matching_resp_item_mimic.h \
    qtfront/question_view_sub/matching_resp_mimic.h \
    qtfront/question_view_sub/multiple_choices_resp_mimic.h \
    qtfront/question_view_sub/question_mimic.h \
    qtfront/question_view_sub/question_view_context_holder.h \
    qtfront/question_view_sub/resp_mimic.h \
    qtfront/question_view_sub/text_block_mimic.h \
    qtfront/question_view_sub/name_edit.h \
    qtfront/app_cmd_model_sub/app_cmd_model_context_holder.h \
    qtfront/app_cmd_model_sub/cmd_manager_mimic.h \
    qtfront/app_cmd_view_sub/app_cmd_view_context_holder.h \
    qtfront/app_cmd_view_sub/view.h \
    qtfront/app_cmd_model.h \
    qtfront/app_cmd_view.h \
    qtfront/editor_view.h

FORMS += \
    qtfront/tree_item_view.ui \
    qtfront/exam_view.ui \
    qtfront/question_view.ui \
    qtfront/question_view_sub/block_context_mimic.ui \
    qtfront/question_view_sub/block_list_mimic.ui \
    qtfront/question_view_sub/choice_mimic.ui \
    qtfront/question_view_sub/image_block_mimic.ui \
    qtfront/question_view_sub/matching_resp_item_mimic.ui \
    qtfront/question_view_sub/matching_resp_mimic.ui \
    qtfront/question_view_sub/multiple_choices_resp_mimic.ui \
    qtfront/question_view_sub/question_mimic.ui \
    qtfront/question_view_sub/text_block_mimic.ui \
    qtfront/app_cmd_view.ui \
    qtfront/main_window.ui
