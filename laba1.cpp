#include <iostream>
#include <string>
#include <locale>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif


class InternetOperator {
private:
    static constexpr double MAX_TARIFF = 3000.0;

    double tariffPrice;        
    std::string operatorName;    
    int numberOfSubscribers;     

    void validateTariff(double price) const {
        if (price < 0.0) {
            throw std::invalid_argument("Ошибка: стоимость тарифа не может быть отрицательной.");
        }
        if (price > MAX_TARIFF) {
            throw std::invalid_argument(
                "Ошибка: стоимость тарифа не может превышать 3000 рублей. Указано: " +
                std::to_string(price)
            );
        }
    }

public:

    InternetOperator() : tariffPrice(0.0), operatorName(""), numberOfSubscribers(0) {}

    InternetOperator(double tariffPrice, const std::string& operatorName, int numberOfSubscribers)
        : operatorName(operatorName), numberOfSubscribers(numberOfSubscribers) {
        validateTariff(tariffPrice);
        this->tariffPrice = tariffPrice;
    }

    double getTariffPrice() const { return tariffPrice; }
    std::string getOperatorName() const { return operatorName; }
    int getNumberOfSubscribers() const { return numberOfSubscribers; }

    void setTariffPrice(double tariffPrice) {
        validateTariff(tariffPrice);
        this->tariffPrice = tariffPrice;
    }

    void setOperatorName(const std::string& operatorName) {
        this->operatorName = operatorName;
    }

    void setNumberOfSubscribers(int numberOfSubscribers) {
        this->numberOfSubscribers = numberOfSubscribers;
    }

 
    double calculateTotalRevenue() const {
        return tariffPrice * numberOfSubscribers;
    }

    friend std::ostream& operator<<(std::ostream& os, const InternetOperator& io) {
        os << "Интернет оператор:\n"
            << "Стоимость тарифа=" << std::fixed << std::setprecision(2) << io.tariffPrice << "\n\n"
            << "Имя оператора=" << io.operatorName << "\n\n"
            << "количество абонентов=" << io.numberOfSubscribers << "\n\n"
            << "итоговая выручка=" << io.calculateTotalRevenue() << "\n\n";
        return os;
    }
};


int main() {
    std::setlocale(LC_ALL, "");
    std::locale::global(std::locale(""));

#ifdef _WIN32
    std::system("chcp 65001 > nul"); 
#endif

    try {
        InternetOperator operator1(500.0, "Ростелеком", 10000);
        std::cout << operator1 << std::endl;

    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}