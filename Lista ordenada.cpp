#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

class AutoSortingList {
private:
    vector<float> elements;

public:
    vector<float> getContent() const {
        return elements;
    }

    void printSorted() const {
        for (int i = 0; i < (int)elements.size(); i++) {
            cout << elements.at(i) << endl;
        }
    }

    vector<float> insert(float value) {
        auto it = lower_bound(elements.begin(), elements.end(), value);
        elements.insert(it, value);
        return elements;
    }

    vector<float> remove(float value) {
        if (elements.empty()) return elements;

        auto it = lower_bound(elements.begin(), elements.end(), value);
        if (it != elements.end() && *it == value) {
            elements.erase(it);
        }

        return elements;
    }

    vector<float> min(int amount = 1) const {
        vector<float> output;
        int n = elements.size();

        for (int i = 0; i < amount && i < n; i++) {
            output.push_back(elements.at(i));
        }

        return output;
    }

    vector<float> max(int amount = 1) const {
        vector<float> output;
        int n = elements.size();

        for (int i = 0; i < amount && i < n; i++) {
            output.insert(output.begin(), elements.at(n - 1 - i));
        }

        return output;
    }

    vector<float> rangeQuery(float x, float y) const {
        vector<float> output;
        int n = elements.size();
        if (n == 0 || x > y) return output;

        auto it = lower_bound(elements.begin(), elements.end(), x);
        while (it != elements.end() && *it <= y) {
            output.push_back(*it);
            ++it;
        }

        return output;
    }

    float median() const {
        int n = elements.size();
        if (n == 0) {
            throw runtime_error("Lista vazia");
        }

        if (n % 2 == 1) {
            return elements.at(n / 2);
        } else {
            return (elements.at(n/2 - 1) + elements.at(n/2)) / 2.0f;
        }
    }
};

void printVector(const vector<float>& v) {
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v.at(i) << endl;
    }
}

int main() {
    AutoSortingList data;
    data.insert(3.6);
    data.insert(0.4);
    printVector(data.insert(9.5));
    cout << "\n\n";

    data.insert(5.4);
    printVector(data.getContent());
    cout << "\n\n";

    data.remove(2.0);
    data.printSorted();
    cout << "\n\n";

    data.insert(5.6);
    data.insert(1.85);
    data.insert(9.8);
    data.insert(4.7);
    data.insert(6.0);
    data.insert(4.1);
    data.insert(0.7);

    data.printSorted();
    cout << "\n\n";

    printVector(data.rangeQuery(1, 8));
    cout << "\n\n";

    cout << "Mediana: " << data.median() << endl;
    return 0;
}