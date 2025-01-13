#include "config.h"
#include "references.h"

INITIALIZE_EASYLOGGINGPP


int main(const int argc, char* argv[]) {
	START_EASYLOGGINGPP(argc, argv);

	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1024);



	Chest SecretTreasure("SecretTreasure", 0, 10, 10, 5, 5, 120);
	const Chest PlayerChest("PlayerChest", 1, 0, 10, 5, 5, 0);

	const Chest DragonTreasure("DragonTreasure", 2, 50, 12, 7, 7, 500);


	GameGroup test_group;
	test_group.pushBack(&SecretTreasure);
	std::cout << test_group.getComposition();

	GameList<Chest> initial_test_game_list;
	std::cout << "THE INITIAL LIST JUST CREATED: \n" << initial_test_game_list << std::endl;

	initial_test_game_list.pushObject(SecretTreasure);
	initial_test_game_list.pushObject(PlayerChest);
	initial_test_game_list.pushObject(DragonTreasure);

	std::cout << "\n\nINITIAL LIST WITH OBJECTS: \n" << initial_test_game_list << std::endl;


	initial_test_game_list.deleteObject(SecretTreasure);

	std::cout << "\n\nINITIAL LIST AFTER DELETION OF ONE OBJECT: \n" << initial_test_game_list << std::endl;


	GameList<Chest> copy_list;
	copy_list.rewrite(initial_test_game_list);

	std::cout << "\n\nCOPIED LIST: \n" << copy_list << std::endl;

	copy_list.clear();

	std::cout << "\n\nCOPY AFTER CLEAR METHOD EXECUTED: \n" << copy_list << std::endl;


	CONSOLE::COLOR_OUT("Program successfully ended", "SUCCESS");

	return 0;
}
