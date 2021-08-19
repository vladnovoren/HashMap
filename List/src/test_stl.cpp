#include <list>

int main() {
    std::list<int> my_list;
    for (size_t k = 0; k < 1000; k++) {
        for (size_t i = 0; i < 1000; i++)
            my_list.push_front(1);
        for (size_t i = 0; i < 999; i++)
            my_list.erase(my_list.begin());
        for (size_t i = 0; i < 999; i++)
            my_list.insert(my_list.begin());
        for (size_t i = 0; i < 999; i++)
            my_list.insert(my_list.begin());
        my_list.clear();
    }
    return 0;
}
