#include "../headers/config.h"
#include <map>

struct PiecePosition {
	uint16_t x = NULL;
	uint16_t y = NULL;

	PiecePosition(const uint16_t& x, const uint16_t& y) : x(x), y(y) {

	}

	PiecePosition() = default;
};

[[nodiscard]] bool IsStrokeAbleToMoveOn(const PiecePosition& target, const PiecePosition& current) {
	constexpr uint16_t strokeTurnRange = 5;
	const auto xRange = static_cast<uint16_t>(std::pow(target.x - current.x, 2));
	const auto yRange = static_cast<uint16_t>(std::pow(target.x - target.y, 2));

	const uint16_t targetDistance = xRange + yRange;

	return (targetDistance == strokeTurnRange);
}

void SearchNextRoundMove(const PiecePosition& potential, const PiecePosition& currentBufferPosition) {
	if (!IsStrokeAbleToMoveOn(currentBufferPosition, potential)) {
		return;
	}

	std::cout << "To do this, it is necessary to move to the point ";
	std::cout << "x: " << currentBufferPosition.x << ", y: " << currentBufferPosition.y << std::endl;
}

[[nodiscard]] bool IsValidFigurePosition(const uint16_t& figureX, const uint16_t figureY) {
	constexpr uint16_t sideSize = 8;
	const bool isValidPosition = (std::max(figureX, figureY) <= sideSize);
	return isValidPosition;
}

void beta_source_1_4_0() {
	/* Is it possible to get from the field (knight.x, knight.y)
	to the field (potential.x, potential.y) with one move of knight?
	If not, find out how it can be done in two moves. */

	PiecePosition knight;
	PiecePosition potential;

	uint16_t definer = 0;

	std::cout << "Knight x:";
	std::cin >> knight.x;

	std::cout << "Knight y:";
	std::cin >> knight.y;

	std::cout << "Potential x:";
	std::cin >> potential.x;

	std::cout << "Potential y:";
	std::cin >> potential.y;


	const map<uint16_t, uint16_t> environment_x = {
		{0, knight.x + 1},
		{1, (knight.x + 2)},
		{2, (knight.x + 2)},
		{3, (knight.x + 1)},
		{4, (knight.x - 1)},
		{5, (knight.x - 2)},
		{6, (knight.x - 2)},
		{7, (knight.x - 1)}
	};

	const map<uint16_t, uint16_t> environment_y = {
		{0, knight.y + 2},
		{1, knight.y + 1},
		{2, knight.y - 1},
		{3, knight.y - 2},
		{4, knight.y - 2},
		{5, knight.y - 1},
		{6, knight.y + 1},
		{7, knight.y + 2}
	};

	const bool isValidFiguresLocation = IsValidFigurePosition(potential.x, potential.y) && IsValidFigurePosition(knight.x, knight.y);

	if (!isValidFiguresLocation) {
		std::cout << "The coordinates are incorrect. The maximum size of the board is 8x8" << std::endl;
		return;
	}

	if (!IsStrokeAbleToMoveOn(potential, knight)) {
		for (; definer <= 7; definer++) {
			const PiecePosition currentBufferPosition(environment_x.at(definer), environment_y.at(definer));
			SearchNextRoundMove(potential, currentBufferPosition);
		}
		return;
	}
	else {
		std::cout << "Successfully relocated to " << "x: " << potential.x << ", y: " << potential.y << std::endl;
		return;
	}

	std::cout << "No available engaging moves in next two turns" << std::endl;
}