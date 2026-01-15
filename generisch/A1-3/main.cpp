#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "vec.h"

using vec3f = my::Vec<float, 3>;



int main() {


    std::cout << "=== Vector Tests using STL ===\n" << std::endl;
    /*
    * 1. std::vector mir 10 vec3f, random werte
    */
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> dist(0.0f, 100.0f);

    std::vector<vec3f> vectors;

    for (int i = 0; i < 10; ++i)
    {
        float x = dist(generator);
        float y = dist(generator);
        float z = dist(generator);

        vec3f temp(x, y, z);
        vectors.push_back(temp);
    }

    std::cout << "--- 10 random vec3fs: ---" << std::endl;
    my::printVec(vectors);
    std::cout << std::endl;


    /*
    * mit std::transform jedes element um 1 erhöhen
    */
    auto increase_by_one = [](const vec3f& v){ return  v + vec3f(1.0f, 1.0f, 1.0f); };
    std::transform(
        vectors.begin(),
        vectors.end(),
        vectors.begin(),
        increase_by_one
    );
    std::cout << "--- increase every vector data by 1: ---" << std::endl;
    my::printVec(vectors);
    std::cout << std::endl;
    
    /*
    * sortieren nach:
    * erst: <90.0, dann >= 90
    * stable partition: die reihenfole innerhalb der partitionen bleibt erhalten
    */

    std::stable_partition(
        vectors.begin(), 
        vectors.end(), 
        [](const vec3f& v){ return v.length() < 90.0f; }
    );

    std::cout << "--- sort by less than 90 length: ---" << std::endl;
    my::printVec(vectors);
    std::cout << std::endl;



    std::sort(
        vectors.begin(), 
        vectors.end(),
        [](const vec3f& a, const vec3f& b){ return a.length() < b.length(); }
    );
    std::cout << "--- sort whole vector using std::sort: ---" << std::endl;
    my::printVec(vectors);
    std::cout << std::endl;


    int medianIndex = vectors.size() / 2;
    auto median = vectors[medianIndex];
    std::vector<vec3f> print_placeholder;
    print_placeholder.push_back(median);
    std::cout << "--- median vector ---" << std::endl;
    my::printVec(print_placeholder);
    std::cout << std::endl;

    /*
    * copy zu neuen vector
    */
    std::vector<vec3f> vectors_copy;
    std::copy_if(
        vectors.begin(), 
        vectors.end(),
        std::back_inserter(vectors_copy), 
        [](const vec3f& v){ return v.length() < 80; }
    );
    std::cout << "--- copy to new vector if length < 80 ---" << std::endl;
    std::cout << "original: " << std::endl;
    my::printVec(vectors);

    std::cout << "copy: " << std::endl;
    my::printVec(vectors_copy);
    std::cout << std::endl;

    
    auto to_be_erased = std::remove_if(
                            vectors.begin(), 
                            vectors.end(), 
                            [](const vec3f& v){ return (v.length() > 90 && v.length() < 120); }
                        );
    vectors.erase(to_be_erased, vectors.end());

    std::cout << "--- deleting every vector with 90 < length < 120  ---" << std::endl;
    my::printVec(vectors);
    std::cout << std::endl;

    std::cout << "=== All Tests passed... ===\n" << std::endl;                  
    return 0;
}