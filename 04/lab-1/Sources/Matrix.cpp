#include "../Headers/Matrix.h"

Matrix::Matrix(const uint64_t &rows, const uint64_t &columns) : _rows(rows), _columns(columns) {
    this->_data.resize(rows);

    for (uint64_t i = 0; i < rows; i++) {
        this->_data[i].resize(columns);
    }

    this->Nullify();
}

std::vector<double80_t> const &Matrix::operator[](const uint64_t &index) const {
    if (index >= this->GetRowsNumber()) {
        throw (std::out_of_range("Matrix out of range"));
    }
    return this->_data[index];
}

std::vector<double80_t> &Matrix::operator[](const uint64_t &index) {
    if (index >= this->GetRowsNumber()) {
        throw (std::out_of_range("Matrix out of range"));
    }
    return this->_data[index];
}

uint64_t Matrix::GetRowsNumber() const {
    return this->_rows;
}

uint64_t Matrix::GetColumnsNumber() const {
    return this->_columns;
}

void Matrix::SumRows(const OperableSet &sumSet) {
    this->CheckOperableSet(sumSet);

    for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
        this->_data[sumSet.modifiableIndex][i] += this->_data[sumSet.operableIndex][i];
    }
}

void Matrix::SubtractRows(const OperableSet &subtractionSet) {
    this->CheckOperableSet(subtractionSet);

    for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
        this->_data[subtractionSet.modifiableIndex][i] -= this->_data[subtractionSet.operableIndex][i];
    }
}

void Matrix::MultiplyRow(const uint64_t &targetRowIndex, const double80_t &multiplier) {
    for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
        this->_data[targetRowIndex][i] *= multiplier;
    }
}

void Matrix::SubtractMultipliedRow(const OperableSet &subtractionSet, const double80_t &multiplier) {
    for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
        this->_data[subtractionSet.modifiableIndex][i] -= this->_data[subtractionSet.operableIndex][i] * multiplier;
    }
}

uint64_t Matrix::GetMaxColumnElementIndex(const uint64_t &columnIndex) const {
    std::vector<double80_t> columnVector{};
    columnVector.resize(this->GetRowsNumber());

    for (uint64_t i = columnIndex; i < this->GetRowsNumber(); i++) {
        columnVector[i] = this->operator[](i)[columnIndex];
    }

    auto it = std::ranges::max_element(columnVector.begin(), columnVector.end(),
                               [](double80_t a, double80_t b) { return std::fabs(a) < std::fabs(b); });

    return (std::distance(columnVector.begin(), it));
}

void Matrix::RandomInit(const double80_t &minRandom, const double80_t &maxRandom) {
    std::random_device randomDevice;
    std::mt19937 generate(randomDevice());
    std::uniform_real_distribution<double80_t> distribution(minRandom, maxRandom);

    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
            this->_data[i][j] = distribution(generate);
        }
    }
}

void Matrix::Print() const {
    const uint64_t precision = 2;
    const uint64_t width = 7;

    std::cout << std::setprecision(precision);
    std::cout.setf(std::ios::right);
    std::cout.setf(std::ios::fixed);

    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
            std::cout << std::setw(width) << this->_data[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void Matrix::CheckOperableSet(const OperableSet &operableSet) const {
    if (operableSet.operableIndex >= this->GetRowsNumber() || operableSet.modifiableIndex >= this->GetRowsNumber()) {
        throw (std::out_of_range("Given index set is out of Matrix range"));
    }
}

Matrix Matrix::operator*(const Matrix &multiplier) const {
    if (this->GetColumnsNumber() != multiplier.GetRowsNumber()) {
        throw (std::invalid_argument("Multiplied matrices should have equal columns and rows number"));
    }

    Matrix result(this->GetRowsNumber(), multiplier.GetColumnsNumber());

    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        for (uint64_t j = 0; j < multiplier.GetColumnsNumber(); j++) {
            for (uint64_t k = 0; k < multiplier.GetRowsNumber(); k++) {
                result[i][j] += this->operator[](i)[k] * multiplier[k][j];
            }
        }
    }

    return result;
}

Matrix::Matrix(const Matrix &source) : _data(source._data), _rows(source.GetRowsNumber()),
                                       _columns(source.GetColumnsNumber()) {
}

Matrix &Matrix::operator=(const Matrix &source) {
    this->_data = source._data;
    this->_rows = source.GetRowsNumber();
    this->_columns = source.GetColumnsNumber();
    return *this;
}

void Matrix::ReadFromFile(const std::filesystem::path &filePath) {
    std::ifstream sourceFile(filePath);

    if (sourceFile.fail()) {
        throw (std::invalid_argument("Invalid matrix file path given"));
    }

    for (uint64_t i = 0; i < this->_rows; i++) {
        for (uint64_t j = 0; j < this->_columns; j++) {
            if (!(sourceFile >> this->_data[i][j])) {
                throw (std::invalid_argument("Matrix file read error. Double data expected (also check if matrix _rows + 1 = _columns."));
            }
        }
    }

    sourceFile.close();
}

Matrix Matrix::operator-(const Matrix &matrixToSubtract) const {
    const bool isAbleToSubtract = (this->GetRowsNumber() == matrixToSubtract.GetRowsNumber()) &&
                                  (this->GetColumnsNumber() == matrixToSubtract.GetColumnsNumber());
    if (!isAbleToSubtract) {
        throw (std::invalid_argument("Matrices should have equal number of rows and columns"));
    }

    Matrix result(this->GetRowsNumber(), this->GetColumnsNumber());

    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
            result[i][j] = this->operator[](i)[j] - matrixToSubtract[i][j];
        }
    }

    return result;
}

Matrix Matrix::operator+(const Matrix &matrixToSubtract) const {
    const bool isAbleToSum = (this->GetRowsNumber() == matrixToSubtract.GetRowsNumber()) &&
                             (this->GetColumnsNumber() == matrixToSubtract.GetColumnsNumber());
    if (!isAbleToSum) {
        throw (std::invalid_argument("Matrices should have equal number of rows and columns"));
    }

    Matrix result(this->GetRowsNumber(), this->GetColumnsNumber());

    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
            result[i][j] = this->operator[](i)[j] + matrixToSubtract[i][j];
        }
    }

    return result;
}


bool Matrix::IsEmpty() const {
    const bool emptinessCriteria =
            this->_data.empty() || this->GetRowsNumber() == 0 || this->GetColumnsNumber() == 0;
    return emptinessCriteria;
}

void Matrix::Append(const Matrix &appendSource) {
    if (appendSource.IsEmpty()) {
        throw (std::invalid_argument("Empty append source"));
    }

    if (this->GetRowsNumber() != appendSource.GetRowsNumber()) {
        throw (std::invalid_argument("Append source has more rows than the target matrix"));
    }

    for (uint64_t i = 0; i < appendSource.GetRowsNumber(); i++) {
        for (uint64_t j = 0; j < appendSource.GetColumnsNumber(); j++) {
            this->_data[i].push_back(appendSource._data[i][j]);
        }
    }

    this->_columns += appendSource.GetColumnsNumber();
}

bool Matrix::operator==(const Matrix &comparedTo) const {
    const bool haveEqualRowsNumber = this->GetRowsNumber() == comparedTo.GetRowsNumber();
    const bool haveEqualColumnsNumber = this->GetColumnsNumber() == comparedTo.GetColumnsNumber();

    const bool haveEqualData = this->_data == comparedTo._data;

    return (haveEqualColumnsNumber && haveEqualRowsNumber && haveEqualData);
}

/**
 *
 */
Matrix Matrix::GetTransposed() const {
    if (this->GetColumnsNumber() != this->GetRowsNumber()) {
        throw (std::logic_error("Unable to transpose matrix: columns != rows"));
    }

    Matrix result(this->GetRowsNumber(), this->GetColumnsNumber());

    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
            result[i][j] = this->operator[](j)[i];
        }
    }

    return result;
}

bool Matrix::IsSymmetric() const {
    Matrix transposed = this->GetTransposed();
    return (*this == transposed);
}

Matrix::Matrix() : Matrix(3, 4) {
    QualitativeNumbers qualitativeNumbers{};
    qualitativeNumbers.ObtainData();

    const double80_t patternAlpha = 2.0 * qualitativeNumbers.lambda1 + qualitativeNumbers.lambda2;
    const double80_t patternBeta = 2.0 * (qualitativeNumbers.lambda1 - qualitativeNumbers.lambda2);

    const double80_t patternGamma = 3.0 * qualitativeNumbers.lambda3;
    const double80_t patternPhi = - 4.0 * qualitativeNumbers.lambda1 + qualitativeNumbers.lambda2;

    const double80_t patternOmega = patternGamma * patternGamma;

    this->_data[0][0] = 2.0 * qualitativeNumbers.lambda1 + 4.0 * qualitativeNumbers.lambda2;
    this->_data[1][0] = patternBeta;
    this->_data[2][0] = patternBeta;

    this->_data[1][0] = patternBeta;
    this->_data[1][1] = patternAlpha + patternGamma;
    this->_data[1][2] = patternAlpha - patternGamma;

    this->_data[2][0] = patternBeta;
    this->_data[2][1] = patternAlpha - patternGamma;
    this->_data[2][2] = patternAlpha + patternGamma;

    this->_data[2][0] = - 2.0 * patternBeta;
    this->_data[2][1] = patternPhi + patternOmega;
    this->_data[2][2] = patternPhi - patternOmega;
}

Matrix::Matrix(const std::filesystem::path &filePath) {
    if (!exists(filePath)) {
        throw (std::invalid_argument("Invalid matrix file path given"));
    }
    std::string line;

    std::ifstream inFile(filePath);
    if (inFile.bad()) {
        throw (std::ios_base::failure("Unknown Stream error occurred"));
    }

    this->_rows = std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n') + 1;

    inFile.clear();
    inFile.seekg(0, std::ios::beg);
    getline(inFile, line);

    this->_columns = std::ranges::count_if( line.begin(), line.end(), []( char c ){return c == ' ';}) + 1;
    inFile.close();

    this->InitVector(this->_rows, this->_columns);
    this->ReadFromFile(filePath);
}

void Matrix::RandomSymmetricInit(const double80_t &minRandom, const double80_t &maxRandom) {
    std::random_device randomDevice;
    std::mt19937 generate(randomDevice());
    std::uniform_real_distribution<double80_t> distribution(minRandom, maxRandom);

    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        for (uint64_t j = 0; j <= i; j++) {
            this->_data[i][j] = distribution(generate);
        }
    }

    *this = *this + this->GetTransposed();
}

void Matrix::Nullify() {
    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
            this->operator[](i)[j] = 0.0;
        }
    }
}

void Matrix::InitVector(const uint64_t &rows, const uint64_t &columns) {
    this->_data.resize(rows);

    for (uint64_t i = 0; i < rows; i++) {
        this->_data[i].resize(columns);
    }
}
