#include "pch.h"
#include "CppUnitTest.h"

#include "config.h"

#include "entity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ProjectUnitTest {
	TEST_CLASS(ProjectUnitTest) {
public:
	TEST_METHOD(TestObjectDeclarations) {
		const Chest SecretTreasure("SecretTreasure", 0, 10, 10, 5, 5, 120);

		Logger::WriteMessage(SecretTreasure.getJsonProperties().c_str());

		Logger::WriteMessage("========================\n");
	}

	TEST_METHOD(TestJsonParsing) {
		std::ifstream json_file;
		json_file.open("../../objects/templates/object_examples.json");

		if (json_file.is_open()) {
			Logger::WriteMessage("File is opened");

			try {
				json opened_json;
				json_file >> opened_json;

				std::stringstream json_out;
				json_out << opened_json["TraceObject"];

				std::string target_object = json_out.str();

				Logger::WriteMessage(target_object.c_str());

				json_out.clear();
			}
			catch ([[maybe_unused]] const json::parse_error& ex) {
				Logger::WriteMessage("JSON structure error");
			}
		}
		else {
			std::stringstream error_out;
			error_out << std::filesystem::current_path().string();

			std::string current_path = error_out.str();

			Logger::WriteMessage(("Current path: " + current_path).c_str());

			Logger::WriteMessage("File is not found");
		}

		json_file.close();

		Logger::WriteMessage("========================\n");
	}

	};
}