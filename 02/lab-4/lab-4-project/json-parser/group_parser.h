#pragma once

#ifndef GROUP_PARSER
#define GROUP_PARSER

#include "entity.h"

inline void GameGroup::parseObjectFrom(const std::string& file_path, const std::string& target_object) {
	std::ifstream input_json_file;
	input_json_file.open(file_path);

	if (input_json_file.is_open()) {
		json json_structure;
		// TODO: How to make it adequate? (Maybe using interfaces, but it's parsing xD)
		CONSOLE::COLOR_OUT("ParseObjectFrom(): File is found", "SUCCESS");

		input_json_file >> json_structure;

		if (json_structure.contains(target_object)) {
			auto object_name = json_structure[target_object]["name"].get<std::string>();
			auto object_type = json_structure[target_object]["type"].get<std::string>();

			unsigned object_id = json_structure[target_object]["id"].get<unsigned int>();

			int object_position_x = json_structure[target_object]["position"]["x"].get<int>();
			int object_position_y = json_structure[target_object]["position"]["y"].get<int>();

			if (object_type == "GameObject") {
				GameObject result(object_name, object_id, object_position_x, object_position_y);
				local_group_.push_back(&result);
			}

			else if (object_type == "Entity") {
				Entity result(object_name, object_id, object_position_x, object_position_y,
					json_structure[target_object]["width"].get<unsigned int>(),
					json_structure[target_object]["height"].get<unsigned int>()
				);
				local_group_.push_back(&result);
			}
			else if (object_type == "Chest") {
				Chest result(object_name, object_id, object_position_x, object_position_y,
					json_structure[target_object]["width"].get<unsigned int>(),
					json_structure[target_object]["height"].get<unsigned int>(),
					json_structure[target_object]["coin_amount"].get<unsigned int>()
				);
				local_group_.push_back(&result);
			}
			else if (object_type == "Stone") {
				Stone result(object_name, object_id, object_position_x, object_position_y,
					json_structure[target_object]["width"].get<unsigned int>(),
					json_structure[target_object]["height"].get<unsigned int>(),
					json_structure[target_object]["sprite_id"].get<unsigned short>()
				);
				local_group_.push_back(&result);
			}

			else if (object_type == "NPC") {
				Npc result(object_name, object_id, object_position_x, object_position_y,
					json_structure[target_object]["game_name"].get<std::string>()
				);
				local_group_.push_back(&result);
			}
			else if (object_type == "Civilian") {
				Civilian result(object_name, object_id, object_position_x, object_position_y,
					json_structure[target_object]["game_name"].get<std::string>()
				);
				local_group_.push_back(&result);
			}
			else if (object_type == "Trader") {
				Trader result(object_name, object_id, object_position_x, object_position_y,
					json_structure[target_object]["game_name"].get<std::string>(),
					json_structure[target_object]["selling_item"].get<unsigned char>()
				);
				local_group_.push_back(&result);
			}

			else if (object_type == "Player") {
				Player result(object_name, object_id, object_position_x, object_position_y,
					json_structure[target_object]["nickname"].get<std::string>(),
					json_structure[target_object]["skin_id"].get<unsigned int>()
				);
				local_group_.push_back(&result);
			}
		}
		else {
			std::string error_description = "ParseObjectFrom(): Object '" + target_object + "' is not found:";

			CONSOLE::COLOR_OUT(error_description, "WARNING");
		}
	}

	else {
		std::string error_description = "ParseObjectFrom(): File is not found, current path: " + std::filesystem::current_path().string();

		CONSOLE::COLOR_OUT(error_description, "WARNING");
	}

	input_json_file.close();
}


// Adds '_list' before '.' (file extension)
inline std::string addFileListIndication(const std::string& original_path) {
	std::string result;
	for (unsigned i{}; i < original_path.length(); i++) {
		if (original_path[i] == '.') {
			result.append("_list");
		}
		result.push_back(original_path[i]);
	}

	return result;
}

inline void GameGroup::saveObjectsList(const std::string& properties_path) const {
	const std::string indicated_path = addFileListIndication(properties_path);

	std::ofstream object_list;
	object_list.open(indicated_path);

	for (unsigned i{}; i < local_group_.size(); i++) {
		object_list << (*local_group_[i]).GameObject::getDebugName() << " ";
	}

	object_list.close();
}

#endif