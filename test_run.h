#pragma once
#include <iostream>

class test_run
{
public:
    test_run()
        : m_tests_total(0)
        , m_tests_passed(0)
    {}
    void test(bool result) {
        ++m_tests_total;
        if (result) {
            ++m_tests_passed;
        }
        else {
            std::cout << "test " << m_tests_total << " failed."
                << std::endl;
        }
    }
    int tests_passed() const {
        return m_tests_passed;
    }
    int tests_total() const {
        return m_tests_total;
    }
    void print() const {
        std::cout << "tests: " << m_tests_passed << " of "
            << m_tests_total << " passed." << std::endl;
    }
private:
    int m_tests_total;
    int m_tests_passed;
};

