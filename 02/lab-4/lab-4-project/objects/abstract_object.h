#pragma once

#ifndef ABSTRACT_OBJECT_H
#define ABSTRACT_OBJECT_H

#include "config.h"

class GameObject {
private:
	std::string debug_name_;
	unsigned id_ = NULL;

protected:
	struct {
		int x = NULL;
		int y = NULL;
	} position_;

public:
	GameObject() = default;

	GameObject(const std::string& new_debug_name, unsigned new_id, int new_x, int new_y) {
		debug_name_ = new_debug_name;
		id_ = new_id;

		position_.x = new_x;
		position_.y = new_y;
	}

	friend std::ostream& operator <<(std::ostream& out, const GameObject& object) {
		return object.printProperties(out);
	}

	bool operator == (const GameObject& comparable) const {
		return ((*this).id_ == comparable.id_) && ((*this).debug_name_ == comparable.debug_name_);
	}

	virtual std::ostream& printProperties(std::ostream& out) const {
		out << "Debug name: " << debug_name_ << ", Id: " << id_ << std::endl;
		return out;
	}

	[[nodiscard]] std::string getDebugName() const {
		return debug_name_;
	}

	[[nodiscard]] virtual std::string getJsonProperties(const std::string& object_type = "GameObject") const {
		const std::string object_type_text = R"("type": ")" + object_type + "\",";
		const std::string object_name = R"("name": ")" + debug_name_ + "\",";

		const std::string object_id = "\"id\":" + std::to_string(id_) + ",";

		const std::string object_position_x = R"("position": { "x":)" + std::to_string(position_.x) + ",";
		const std::string object_position_y = " \"y\":" + std::to_string(position_.y) + "}";

		return (object_type_text + object_name + object_id + object_position_x + object_position_y);
	}

	virtual ~GameObject() = default;
};


class GameGroup {
private:
	std::vector <GameObject*> local_group_ = {};

	void parseObjectFrom(const std::string& file_path, const std::string& target_object);

	void saveObjectsList(const std::string& properties_path) const;

public:
	GameGroup() = default;

	GameGroup(GameObject* place_holder, const unsigned& object_count) {
		for (unsigned i{}; i < object_count; i++) {
			local_group_.push_back(place_holder);
		}
	}

	GameGroup(const GameGroup& group) {
		local_group_ = group.local_group_;
	}

	GameGroup(GameGroup&& group) noexcept : local_group_(group.local_group_) {
		local_group_ = group.local_group_;

		group.clear();
	}

	GameGroup& operator = (GameGroup&& group) noexcept {
		if (this != &group) {
			(*this).clear();

			local_group_ = group.local_group_;
		}

		return *this;
	}

	void copy(const GameGroup& group) {
		local_group_ = group.local_group_;
	}

	void pushBack(GameObject* object) {
		local_group_.push_back(object);
	}

	void deleteObject(const GameObject& object) {
		GameGroup result;

		for (unsigned i{}; i < local_group_.size(); i++) {
			if (!(*local_group_[i] == object)) {
				result.local_group_.push_back(local_group_[i]);
			}
		}

		local_group_ = result.local_group_;
	}

	[[nodiscard]] size_t getObjectSize() const {
		return local_group_.size();
	}

	[[nodiscard]] std::string getComposition() const {
		std::stringstream out;

		for (uint64_t i{}; i < local_group_.size(); i++) {
			out << "\"" + (*local_group_[i]).GameObject::getDebugName() + "\" :";
			json output_buffer = json::parse("{" + (*local_group_[i]).getJsonProperties() + "}");
			out << output_buffer.dump(4) << std::endl;
		}

		return out.str();
	}

	void parseFile(const std::string& object_list, const std::string& object_properties) {
		std::ifstream list_file;
		list_file.open(object_list);

		if (list_file.is_open()) {
			CONSOLE::COLOR_OUT("ParseFile(): File is opened", "SUCCESS");

			std::string buffer;
			while (list_file >> buffer) {
				parseObjectFrom(object_properties, buffer);
			}
		}
		else {
			const std::string error_description = "ParseFile(): File is not found, current path: " + std::filesystem::current_path().string();

			CONSOLE::COLOR_OUT(error_description, "WARNING");
		}

		list_file.close();
	}

	void saveToFile(const std::string& save_file) const {
		std::ofstream out_file;
		out_file.open(save_file);

		out_file << (*this).getComposition();

		(*this).saveObjectsList(save_file);

		out_file.close();
	}

	void clear() {
		local_group_.clear();
	}

	~GameGroup() = default;
};


template <typename T>
class GameList {
private:
	struct Node {
		T object;
		std::unique_ptr<Node> next = nullptr;

		explicit Node(T data) {
			object = data;
			next = nullptr;
		}
	};

	std::unique_ptr<Node> head_ = nullptr;

public:
	GameList() = default;

	GameList(const GameList& sample) {
		GameList::rewrite(sample);
	}

	GameList(GameList&& sample) noexcept {
		(*this).head_ = std::move(sample.head_);
	}

	[[nodiscard]] bool isEmpty() const {
		return ((*this).head_ == nullptr);
	}

	void rewrite(const GameList& sample) {
		Node* current_head = sample.head_.get();
		std::unique_ptr<Node> new_head = nullptr;

		Node* pointed_new_head = nullptr;

		while (current_head != nullptr) {
			auto temp = std::make_unique<Node>(current_head->object);

			if (new_head == nullptr) {
				new_head = std::move(temp);
				pointed_new_head = new_head.get();
			}
			else {
				pointed_new_head->next = std::move(temp);
				pointed_new_head = pointed_new_head->next.get();
			}
			current_head = current_head->next.get();
		}

		(*this).head_ = std::move(new_head);
	}


	void pushObject(const T& object) {
		auto temp = std::make_unique<Node>(object);

		if ((*this).head_.get() != nullptr) {
			temp->next = std::move((*this).head_);
			(*this).head_ = std::move(temp);
		}
		else {
			(*this).head_ = std::move(temp);
		}
	}

	void reverse() {
		GameList temp;

		Node* current_head = (*this).head_.get();

		while (current_head != nullptr) {
			temp.pushObject(current_head->object);
			current_head = current_head->next.get();
		}
		clear();

		(*this).head_ = std::move(temp.head_);
	}

	T& operator = (T&& sample) noexcept {
		if (sample.head_.get() != nullptr) {
			(*this).head_ = std::move(sample.head_);
		}

		return *this;
	}

	friend std::ostream& operator << (std::ostream& os, const GameList& list) {
		if (list.head_.get() == nullptr) {
			os << "List is empty" << std::endl;
			return os;
		}
		else {
			Node* current_node = list.head_.get();

			while (current_node != nullptr) {
				os << current_node->object.GameObject::getDebugName() << std::endl;
				current_node = current_node->next.get();
			}

			return os;
		}
	}

	void printObjectsProperties() {
		if ((*this).head_.get() == nullptr) {
			std::cout << "List is empty" << std::endl;
		}
		else {
			Node* current_node = (*this).head_.get();

			while (current_node != nullptr) {
				std::cout << current_node->object.GetJsonProperties() << std::endl;
				current_node = current_node->next.get();
			}
		}
	}

	void deleteObject(const T& object) {
		if ((*this).isEmpty() == false) {
			GameList result;

			Node* current_node = (*this).head_.get();

			while ((current_node != nullptr) && !(current_node->object == object)) {
				result.pushObject(current_node->object);

				current_node = current_node->next.get();
			}

			if (current_node != nullptr) {
				current_node = current_node->next.get();

				while (current_node != nullptr) {
					result.pushObject(current_node->object);
					current_node = current_node->next.get();
				}

				result.reverse();
				(*this).rewrite(result);
			}
		}

	}

	void clear() {
		while ((*this).head_.get() != nullptr) {
			(*this).head_->object.~T();
			(*this).head_ = std::move((*this).head_->next);
		}
	}

	~GameList() {
		clear();
	}
};
#endif