#pragma once

#ifndef NPC_H
#define NPC_H

#include "config.h"
#include "abstract_object.h"

class Npc : public GameObject {
private:
	std::string game_name_ = "Unnamed NPC";

public:
	Npc() = default;

	Npc(const std::string& new_name, const unsigned& new_id, const int& new_x, const int& new_y,
		const std::string& new_game_name) : GameObject(new_name, new_id, new_x, new_y) {
		game_name_ = new_game_name;
	}

	[[nodiscard]] std::string getJsonProperties(const std::string& object_type = "NPC") const override {
		const std::string base_data = GameObject::getJsonProperties(object_type);
		const std::string game_name = ",\"game_name\":" + game_name_;

		return (base_data + game_name);
	}

	virtual void setPosition(const int& x_direction, const int& y_direction) {
		position_.x = x_direction;
		position_.y = y_direction;
	}

	~Npc() override = default;
};



class Civilian final : public Npc {
public:
	Civilian() = default;

	Civilian(const std::string& new_name, const unsigned& new_id, const int& new_x, const int& new_y,
		const std::string& new_game_name) : Npc(new_name, new_id, new_x, new_y, new_game_name) {
	}

	[[nodiscard]] std::string getJsonProperties(const std::string& object_type = "Civilian") const override {
		std::string base_data = Civilian::getJsonProperties(object_type);
		return (base_data);
	}
};

class Trader final : public Npc {
private:
	uint8_t selling_item_id_ = NULL;

	const uint8_t max_selling_item_id_ = 100;

public:
	Trader() = default;

	Trader(const std::string& new_name, const uint32_t& new_id, const int& new_x, const int& new_y,
		const std::string& new_game_name, const uint8_t& new_item_id) : Npc(new_name, new_id, new_x, new_y, new_game_name) {
		selling_item_id_ = new_item_id;
	}

	[[nodiscard]] std::string getJsonProperties(const std::string& object_type = "Trader") const override {
		const std::string base_data = Npc::getJsonProperties(object_type);
		const std::string selling_item = ",\"selling_item\":" + selling_item_id_;

		return (base_data + selling_item);
	}

	void setItemId(const uint8_t& new_id) {
		if (new_id < max_selling_item_id_) {
			selling_item_id_ = new_id;
		}
	}
};

#endif