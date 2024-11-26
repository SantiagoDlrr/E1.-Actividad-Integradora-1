#include <catch2/catch_test_macros.hpp>
#include "transmission.h"

TEST_CASE("analyzeTransmission - Parte 1") {
    // Transmission 1 and mcode 1
    REQUIRE(analyzeTransmission("transmission1.txt", "mcode1.txt") == 1276);

    // Transmission 1 and mcode 2
    REQUIRE(analyzeTransmission("transmission1.txt", "mcode2.txt") == -1);

    // Transmission 1 and mcode 3
    REQUIRE(analyzeTransmission("transmission1.txt", "mcode3.txt") == -1);

    // Transmission 2 and mcode 1
    REQUIRE(analyzeTransmission("transmission2.txt", "mcode1.txt") == -1);

    // Transmission 2 and mcode 2
    REQUIRE(analyzeTransmission("transmission2.txt", "mcode2.txt") == 1);

    // Transmission 2 and mcode 3
    REQUIRE(analyzeTransmission("transmission2.txt", "mcode3.txt") == 1786);
}

TEST_CASE("analyzePalindromes - Parte 2") {
    SECTION("Transmission 1") {
        // Using transmission1.txt
        std::string transmission1 = readFile("transmission1.txt");
        auto result1 = longestPalindrome(transmission1);

        REQUIRE(result1.first == 850);          // Starting position (1-based)
        REQUIRE(result1.second == "dD242Dd");  // Longest palindrome
    }

    SECTION("Transmission 2") {
        // Using transmission2.txt
        std::string transmission2 = readFile("transmission2.txt");
        auto result2 = longestPalindrome(transmission2);

        REQUIRE(result2.first == 1785);  // Starting position (1-based)
        REQUIRE(result2.second ==
                "BDa92D09Ac7a63E1C1fECDcb2bcDCEf1C1E36a7cA90D29aDB"); // Longest palindrome
    }
}

TEST_CASE("longestCommonSubstring - Parte 3") {
    // Using transmission1.txt and transmission2.txt
    std::string transmission1 = readFile("transmission1.txt");
    std::string transmission2 = readFile("transmission2.txt");

    REQUIRE(!transmission1.empty());
    REQUIRE(!transmission2.empty());

    auto result = longestCommonSubstring(transmission1, transmission2);

    REQUIRE(result.first == 657);        // Start index (1-based)
    REQUIRE(result.second == 661);      // End index (1-based)
    REQUIRE(transmission1.substr(result.first, result.second - result.first + 1) == "1C1E3");
}
