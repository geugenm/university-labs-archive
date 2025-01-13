#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "config.h"
#include "abstract_object.h"

class Player final : public GameObject {
private:
	std::string nickname_;
	unsigned skin_id_ = NULL;

public:
	Player() = default;

	Player(const std::string& new_name, const unsigned& new_id, const int& new_x, const int& new_y,
		const std::string& new_nickname, const unsigned& new_skin_id) : GameObject(new_name, new_id, new_x, new_y) {
		nickname_ = new_nickname;
		skin_id_ = new_skin_id;
	}

	virtual std::ostream& printProperties(std::ostream& out) const override {
		out << "Player" << nickname_ << ", skin: " << skin_id_ << std::endl;
		return out;
	}

	[[nodiscard]] std::string getJsonProperties(const std::string& object_type = "Player") const override {
		const std::string base_data = GameObject::getJsonProperties(object_type);

		const std::string nickname = ",\"nickname\":" + nickname_ + ",";
		const std::string skin_id = ",\"skin_id\":" + std::to_string(skin_id_);

		return (base_data + nickname + skin_id);
	}

	void changeNickname(const std::string& new_name) {
		nickname_ = new_name;
	}

	void changeSkin(const unsigned& new_skin_id) {
		skin_id_ = new_skin_id;
	}
};

#endif