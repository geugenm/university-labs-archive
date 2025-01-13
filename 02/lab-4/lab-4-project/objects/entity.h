#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "config.h"
#include "abstract_object.h"

class Entity : public GameObject {
protected:
	struct {
		unsigned width = NULL;
		unsigned height = NULL;
	} size_;

public:
	Entity() = default;

	Entity(const std::string& new_name, const unsigned& new_id, const int& new_x, const int& new_y,
		const unsigned& new_width, const unsigned& new_height) : GameObject(new_name, new_id, new_x, new_y) {
		size_.width = new_width;
		size_.height = new_height;
	}

	virtual std::ostream& printProperties(std::ostream& out) const override {
		out << "Entity, height: " << size_.height << ", width: " << size_.width << std::endl;
		return out;
	}

	virtual void setPosition(const int& x_direction, const int& y_direction) {
		position_.x = x_direction;
		position_.y = y_direction;
	}

	[[nodiscard]] std::string getJsonProperties(const std::string& object_type = "Entity") const override {
		const std::string& base_data = GameObject::getJsonProperties(object_type);
		const std::string& object_height = R"(,"size": { "width":)" + std::to_string(size_.width) + ",";

		const std::string& object_width = " \"height\":" + std::to_string(size_.height) + "}";

		return (base_data + object_height + object_width);
	}

	~Entity() override = default;
};



class Chest final : public Entity {
private:
	uint32_t _coin_amount = NULL;

public:
	Chest() = default;

	Chest(const std::string& new_name, const unsigned& new_id, const int& new_x, const int& new_y,
		const unsigned& new_width, const unsigned& new_height, const unsigned& new_coin_amount)
		: Entity(new_name, new_id, new_x, new_y, new_width, new_height) {
		_coin_amount = new_coin_amount;
	}

	virtual std::ostream& printProperties(std::ostream& out) const override {
		out << "Chest, coins: " << _coin_amount << std::endl;
		return out;
	}

	[[nodiscard]] std::string getJsonProperties(const std::string& object_type = "Chest") const override {
		const std::string base_data = Entity::getJsonProperties(object_type);
		const std::string coin_amount = ",\"coin_amount\":" + std::to_string(_coin_amount);

		return (base_data + coin_amount);
	}

	~Chest() override = default;
};

class Stone final : public Entity {
private:
	uint16_t _sprite_id = NULL;
	const uint16_t MAX_SPRITE_ID = 10000;

public:
	Stone(const std::string& new_name, const unsigned& new_id, const int& new_x, const int& new_y,
		const unsigned& new_width, const unsigned& new_height, const unsigned short& new_sprite_id)
		: Entity(new_name, new_id, new_x, new_y, new_width, new_height) {
		_sprite_id = new_sprite_id;
	}

	virtual std::ostream& printProperties(std::ostream& out) const override {
		out << "Stone, sprite_id: " << _sprite_id << std::endl;
		return out;
	}

	[[nodiscard]] std::string getJsonProperties(const std::string& object_type = "Stone") const override {
		const std::string base_data = Entity::getJsonProperties(object_type);
		const std::string sprite_id = ",\"sprite_id\":" + std::to_string(_sprite_id);

		return (base_data + sprite_id);
	}

	void SetSpriteId(const uint8_t& new_id) {
		if (new_id < MAX_SPRITE_ID) {
			_sprite_id = new_id;
		}
	}
};

#endif