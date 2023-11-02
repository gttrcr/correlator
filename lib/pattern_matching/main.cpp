#include <iostream>
#include <vector>

void ranges(const std::vector<unsigned int> &small, const std::vector<unsigned int> &big, const unsigned int &v1from, const unsigned int &v1to, const unsigned int &v2from, const unsigned int &v2to)
{
    std::cout << "small [" << v1from << "," << v1to << "] big [" << v2from << "," << v2to << "]" << std::endl;
}

void pattern_matching(const std::vector<unsigned int> &v1, const std::vector<unsigned int> &v2)
{
    const unsigned int min_window = 2;
    const unsigned int max_window = std::min(v1.size(), v2.size());
    std::vector<unsigned int> small(v1.size() == max_window ? v1 : v2);
    std::vector<unsigned int> big(v1.size() == max_window ? v2 : v1);
    unsigned int big_size = big.size();

    for (unsigned int w = 0; w < max_window; w++)
        for (int i = max_window - 1; i >= (int)(w + min_window - 1); i--)
        {
            const unsigned int width = i - w + 1;
            for (unsigned int j = 0; j <= big_size - width; j++)
                ranges(small, big, w, i, j, j + width - 1);
        }
}

int main()
{
    std::vector<unsigned int> v1;
    std::vector<unsigned int> v2;
    const unsigned int v1size = 5;
    const unsigned int v2size = 8;
    std::srand((unsigned)time(NULL));
    for (unsigned int i = 0; i < v1size; i++)
        v1.push_back(std::rand());
    for (unsigned int i = 0; i < v2size; i++)
        v2.push_back(std::rand());

    pattern_matching(v1, v2);
}