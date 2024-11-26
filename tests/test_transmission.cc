#include <catch2/catch_test_macros.hpp>
#include "transmission.h"

TEST_CASE("analyzeTransmission - Part 1") {
    SECTION("Checking transmission1.txt with mcode files") {
        int result1 = analyzeTransmission("transmission1.txt", "mcode1.txt");
        int result2 = analyzeTransmission("transmission1.txt", "mcode2.txt");
        int result3 = analyzeTransmission("transmission1.txt", "mcode3.txt");

        REQUIRE(result1 == 1276);
        REQUIRE(result2 == -1);
        REQUIRE(result3 == -1);
    }

    SECTION("Checking transmission2.txt with mcode files") {
        int result1 = analyzeTransmission("transmission2.txt", "mcode1.txt");
        int result2 = analyzeTransmission("transmission2.txt", "mcode2.txt");
        int result3 = analyzeTransmission("transmission2.txt", "mcode3.txt");

        REQUIRE(result1 == -1);
        REQUIRE(result2 == 1);
        REQUIRE(result3 == 1786);
    }
}

TEST_CASE("analyzePalindromes - Part 2") {
    SECTION("Finding the longest palindrome in transmission1.txt") {
        std::string transmission1 = readFile("transmission1.txt");
        REQUIRE(!transmission1.empty()); // Ensure the file is read correctly

        auto result = longestPalindrome(transmission1);

        REQUIRE(result.first == 850);          // Start index (1-based)
        REQUIRE(result.second == "dD242Dd");  // Longest palindrome
    }

    SECTION("Finding the longest palindrome in transmission2.txt") {
        std::string transmission2 = readFile("transmission2.txt");
        REQUIRE(!transmission2.empty()); // Ensure the file is read correctly

        auto result = longestPalindrome(transmission2);

        REQUIRE(result.first == 1785);  // Start index (1-based)
        REQUIRE(result.second ==
                "BDa92D09Ac7a63E1C1fECDcb2bcDCEf1C1E36a7cA90D29aDB"); // Longest palindrome
    }
}

TEST_CASE("longestCommonSubstring - Part 3") {
    SECTION("Finding the longest common substring between transmission1.txt and transmission2.txt") {
        std::string transmission1 = readFile("transmission1.txt");
        std::string transmission2 = readFile("transmission2.txt");

        REQUIRE(!transmission1.empty());
        REQUIRE(!transmission2.empty());

        auto result = longestCommonSubstring(transmission1, transmission2);

        REQUIRE(result.first == 657);        // Start index (1-based)
        REQUIRE(result.second == 661);      // End index (1-based)
        REQUIRE(transmission1.substr(result.first, result.second - result.first + 1) == "1C1E3");
    }
}
