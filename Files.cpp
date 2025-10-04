#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

class Drink {
    string name;
    double price;

public:
    Drink() {
        name = "";
        price = 0.0;
    }

    Drink(const string& name, double price) {
        if (name.empty()) {
            throw invalid_argument("Name cannot be empty");
        }
        if (price < 0.0) {
            throw invalid_argument("Price cannot be negative");
        }
        this->name = name;
        this->price = price;
    }

    string getName() const {
        return this->name;
    }

    double getPrice() const {
        return this->price;
    }

    friend istream& operator>>(istream& in, Drink& drink) {
        string inputName;
        double inputPrice;

        in >> ws;
        in >> inputName >> inputPrice;

        if (inputName.empty()) {
            throw invalid_argument("Name cannot be empty");
        }

        if (inputPrice < 0.0) {
            throw invalid_argument("Price cannot be negative");
        }

        drink.name = inputName;
        drink.price = inputPrice;

        return in;
    }
};

class Receipt {
    int id;
    double amount;
    vector<Drink> drinks;

public: 
    Receipt() {
        id = 1;
        amount = 0.0;
        drinks = {};
    }

    double calculateReceiptAmount() const {
        double total = 0.0;
        for (auto& drink : drinks) {
            total += drink.getPrice();
        }
        return total;
    }

    bool hasReceiptBeenPaid() const {
        return this->amount >= calculateReceiptAmount() + calculateTipAmount();
    }

    virtual double calculateTipAmount() const = 0;

    friend istream& operator>>(istream& in, Receipt& receipt) {
        int inputId;
        double inputAmount;
        int drinkCount;

        in >> inputId >> inputAmount >> drinkCount;

        if (inputId <= 0) {
            throw invalid_argument("ID must be a positive integer");
        }

        if (inputAmount < 0.0) {
            throw invalid_argument("Amount cannot be negative");
        }

        if (drinkCount < 0) {
            throw invalid_argument("Drink count cannot be negative");
        }

        receipt.id = inputId;
        receipt.amount = inputAmount;
        receipt.drinks.clear();

        for (int i = 0; i < drinkCount; i ++) {
            Drink drink;
            in >> drink;
            receipt.drinks.push_back(drink);
        }

        return in;
    }

    int getId() const {
        return id;
    }

    double getAmount() const {
        return amount;
    }

    const vector<Drink>& getDrinks() const {
        return drinks;
    }

    void addDrink(const Drink& drink) {
        drinks.push_back(drink);
    }

    void setId(int id) {
        this->id = id;
    }

    void setAmount(double amount) {
        this->amount = amount;
    }

};

class PubReceipt : public Receipt {
public:
    double calculateTipAmount() const override {
        return 0.15 * calculateReceiptAmount();
    }
};

class ClubReceipt : public Receipt {
public:
    double calculateTipAmount() const override {
        return 0.25 * calculateReceiptAmount();
    }
};

class Client {
    vector<Receipt*> receipts;

public: 
    Client() {}

    double calculateTotalSuccessfullySpentMoney() const {
        double total = 0.0;
        for (const auto& receipt : receipts) {
            if (receipt->hasReceiptBeenPaid()) {
                for (const auto& drink : receipt->getDrinks()) {
                    total += drink.getPrice();
                }
                total += receipt->calculateTipAmount();}
        }
        return total;
    }
    
    void addReceipt(Receipt* r) {
        receipts.push_back(r);
    }

    ~Client() {
        for (auto receipt : receipts) {
            delete receipt;
        }
    }
};

int main() {
    try {
        ifstream file;
        file.open("receipts.txt");
        if (!file.is_open()) {
            throw runtime_error("Could not open file");
        }
        Client client;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string type;
            ss >> type;

            Receipt* receipt = nullptr;
            if (type == "Pub") {
                receipt = new PubReceipt();
            } else if (type == "Club") {
                receipt = new ClubReceipt();
            } else {
                throw invalid_argument("Unknown receipt type: " + type);
            }

            getline(file, line);
            int id = stoi(line);
            if (id <= 0) {
                throw invalid_argument("ID must be a positive integer");
            }
            receipt->setId(id);

            getline(file, line);
            double amount = stod(line);
            if (amount < 0.0) {
                throw invalid_argument("Amount cannot be negative");
            }
            receipt->setAmount(amount);

            while(getline(file, line)) {
                if (line == "-----------------------") break;

                stringstream drinkStream(line);
                Drink drink;
                drinkStream >> drink;
                if (drink.getName().empty() || drink.getPrice() < 0.0) {
                    throw invalid_argument("Invalid drink data");
                }
                receipt->addDrink(drink);
            }
            client.addReceipt(receipt);
        }
        cout << "Total successfully spent money: " << client.calculateTotalSuccessfullySpentMoney() << " BGN" << endl;
        file.close();
    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}