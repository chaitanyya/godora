#ifndef CHAT_DOCK_H
#define CHAT_DOCK_H

#include "scene/gui/box_container.h"
#include "scene/gui/rich_text_label.h"
#include "scene/gui/text_edit.h"
#include "editor/editor_node.h"
#include "ai_builder/oai_req.h"

class ChatDock : public VBoxContainer {
	GDCLASS(ChatDock, VBoxContainer);

private:
	VBoxContainer *chat_container;
	ScrollContainer *scroll_container;
	VBoxContainer *message_container;
	TextEdit *input_field = nullptr;
    EditorSelection* editor_selection;
    OpenAIRequest* oai_request = nullptr;

	enum MessageType {
		MESSAGE_USER,
		MESSAGE_SYSTEM,
		MESSAGE_ERROR,
		MESSAGE_SUCCESS
	};

    void _update_selected_node_label();
    void _on_selection_changed();

    HBoxContainer *node_pill = nullptr;
    TypedArray<Node> selected_nodes;

	void _text_submitted(const String &p_text);
	void _on_response_received(const Dictionary &p_scene_data);
	void _on_request_failed(const String &p_error);
	void _process_scene_changes(const Array &p_tasks);

	void gather_project_resources(Dictionary &p_resources);
	Dictionary gather_node_info(Node* p_node);

	void _add_message(const String &p_text, MessageType p_type, const Array &p_tasks);
	void _add_log(const String &p_text);
	void _text_editor_gui_input(const Ref<InputEvent> &p_event);

    void clear();

protected:
	static void _bind_methods();

public:
	ChatDock();
};

#endif // CHAT_DOCK_H