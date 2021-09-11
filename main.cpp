#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <array>
#include <string>
#include <sstream>

#include <doctest/doctest.h>

#include <magic_enum.hpp>

enum class Color : int {
    RED = -10, BLUE = 0, GREEN = 10
};

template<typename E>
auto to_integer(magic_enum::Enum<E> value) {
    // magic_enum::Enum<E> - C++17 Concept for enum type.
    return static_cast<magic_enum::underlying_type_t<E>>(value);
}

TEST_SUITE ("Example derived tests.") {
    TEST_CASE ("Enum variable to string name.") {
        /* Example snippet:
         *
         * // Enum variable to string name.
         * Color c1 = Color::RED;
         * auto c1_name = magic_enum::enum_name(c1);
         * std::cout << c1_name << std::endl; // RED
         */
        Color c1 = Color::RED;
                REQUIRE(magic_enum::enum_name(c1) == "RED");
    }

    TEST_CASE ("String enum name sequence.") {
        /* Example snippet:
         *
         * // String enum name sequence.
         * constexpr auto& names = magic_enum::enum_names<Color>();
         * std::cout << "Color names:";
         * for (const auto& n : names) {
         *   std::cout << " " << n;
         * }
         * std::cout << std::endl;
         * // Color names: RED BLUE GREEN
        */
        constexpr auto &names = magic_enum::enum_names<Color>();
        std::array<const std::string, 3> const seq{"RED", "BLUE", "GREEN"};
        auto index = 0;
        for (const auto &n: names) {
            if (n != "RED" and n != "BLUE" && n != "GREEN") FAIL ("Unexpected color name");
                    CHECK(n == seq[index++]);
        }
    }

    TEST_CASE ("String name to enum value.") {
        /* Example snippet:
         *
         * // String name to enum value.
         * auto c2 = magic_enum::enum_cast<Color>("BLUE");
         * if (c2.has_value()) {
         *   std::cout << "BLUE = " << to_integer(c2.value()) << std::endl; // BLUE = 0
         * }
         */
        auto c2 = magic_enum::enum_cast<Color>("BLUE");
                CHECK(c2.has_value());
                REQUIRE(to_integer(c2.value()) == 0);
    }

    TEST_CASE ("Integer value to enum value.") {
        /* Example snippet:
         *
         * // Integer value to enum value.
         * auto c3 = magic_enum::enum_cast<Color>(10);
         * if (c3.has_value()) {
         *   std::cout << "GREEN = " << magic_enum::enum_integer(c3.value()) << std::endl; // GREEN = 10
         * }
         */
        auto c3 = magic_enum::enum_cast<Color>(10);
                CHECK(c3.has_value());
                REQUIRE(magic_enum::enum_integer(c3.value()) == 10);
    }

    TEST_CASE ("Integer value to enum value.") {
        /* Example snippet:
         *
         * // Enum value to integer value.
         * auto c4_integer = magic_enum::enum_integer(Color::RED);
         * std::cout << "RED = " << c4_integer << std::endl; // RED = -10
         */
        auto c4_integer = magic_enum::enum_integer(Color::RED);
                REQUIRE(c4_integer == -10);
    }

    TEST_CASE ("Ostream operator for enum.") {
        /* Example snippet:
         *
         * using namespace magic_enum::ostream_operators; // out-of-the-box ostream operator for all enums.
         * // Ostream operator for enum.
         * std::cout << "Color: " << c1 << " " << c2 << " " << c3 << std::endl; // Color: RED BLUE GREEN
         */
        Color c1 = Color::RED;
        auto c2 = magic_enum::enum_cast<Color>("BLUE");
        auto c3 = magic_enum::enum_cast<Color>(10);
        using namespace magic_enum::ostream_operators;
        std::ostringstream os;
        os << "Color: " << c1 << " " << c2 << " " << c3;
                REQUIRE(os.str() == "Color: RED BLUE GREEN");
    }

    TEST_CASE ("Number of enum values.") {
        /* Example snippet:
         *
         * // Number of enum values.
         * std::cout << "Color enum size: " << magic_enum::enum_count<Color>() << std::endl; // Color size: 3
         */
                REQUIRE(magic_enum::enum_count<Color>() == 3);
    }

    TEST_CASE ("Indexed access to enum value.") {
        /* Example snippet:
         *
         * // Indexed access to enum value.
         * std::cout << "Color[0] = " << magic_enum::enum_value<Color>(0) << std::endl; // Color[0] = RED
         */
                REQUIRE(magic_enum::enum_value<Color>(0) == Color::RED);
    }

    TEST_CASE ("Enum value sequence.") {
        /* Example snippet:
         *
         * // Enum value sequence.
         * constexpr auto& values = magic_enum::enum_values<Color>();
         * std::cout << "Colors values:";
         * for (const auto& c : values) {
         *   std::cout << " " << c; // Ostream operator for enum.
         * }
         * std::cout << std::endl;
         * // Color sequence: RED BLUE GREEN
         */
        constexpr auto &values = magic_enum::enum_values<Color>();
        using namespace magic_enum::ostream_operators;
        std::ostringstream os;
        for (const auto &c: values) os << " " << c;
                REQUIRE(os.str() == " RED BLUE GREEN");
    }

    TEST_CASE ("Support operators.") {
        /* Example snippet:
         *
         * enum class Flags { A = 1, B = 2, C = 4, D = 8 };
         * using namespace magic_enum::bitwise_operators; // out-of-the-box bitwise operators for all enums.
         * // Support operators: ~, |, &, ^, |=, &=, ^=.
         * Flags flag = Flags::A | Flags::C;
         * std::cout << flag << std::endl; // 5
         */
        enum class Flags {
            A = 1, B = 2, C = 4, D = 8
        };
        using namespace magic_enum::bitwise_operators;
        Flags flag = Flags::A | Flags::C;
                CHECK(static_cast<int>(flag) == 5);
                CHECK(static_cast<int>(~Flags::A) == -2);
                CHECK(static_cast<int>(Flags::A & Flags::C) == 0);
        flag |= Flags::D;
                CHECK(static_cast<int>(flag) == 13);
        flag &= Flags::B;
                CHECK(static_cast<int>(flag) == 0);
        flag ^= Flags::C;
                REQUIRE(static_cast<int>(flag) == 4);
    }

    TEST_CASE ("Type is an Unscoped enumeration.") {
        /* Example snippet:
         *
         * enum class Flags { A = 1, B = 2, C = 4, D = 8 };
         * enum color { red, green, blue };
         * // Checks whether type is an Unscoped enumeration.
         * static_assert(magic_enum::is_unscoped_enum_v<color>);
         * static_assert(!magic_enum::is_unscoped_enum_v<Color>);
         * static_assert(!magic_enum::is_unscoped_enum_v<Flags>);
         */
        enum class Flags {
            A = 1, B = 2, C = 4, D = 8
        };
        enum color {
            red, green, blue
        };
        static_assert(magic_enum::is_unscoped_enum_v<color>);
        static_assert(!magic_enum::is_unscoped_enum_v<Color>);
        static_assert(!magic_enum::is_unscoped_enum_v<Flags>);
                CHECK(magic_enum::is_unscoped_enum_v<color>);
                CHECK(!magic_enum::is_unscoped_enum_v<Color>);
                REQUIRE(!magic_enum::is_unscoped_enum_v<Flags>);
    }

    TEST_CASE ("Type is an Unscoped enumeration.") {
        /* Example snippet:
         *
         * enum class Flags { A = 1, B = 2, C = 4, D = 8 };
         * enum color { red, green, blue };
         * // Checks whether type is an Scoped enumeration.
         * static_assert(!magic_enum::is_scoped_enum_v<color>);
         * static_assert(magic_enum::is_scoped_enum_v<Color>);
         * static_assert(magic_enum::is_scoped_enum_v<Flags>);
         */
        enum class Flags {
            A = 1, B = 2, C = 4, D = 8
        };
        enum color {
            red, green, blue
        };
        static_assert(!magic_enum::is_scoped_enum_v<color>);
        static_assert(magic_enum::is_scoped_enum_v<Color>);
        static_assert(magic_enum::is_scoped_enum_v<Flags>);
                CHECK(!magic_enum::is_scoped_enum_v<color>);
                CHECK(magic_enum::is_scoped_enum_v<Color>);
                REQUIRE(magic_enum::is_scoped_enum_v<Flags>);
    }

    TEST_CASE ("Enum pair (value enum, string enum name) sequence.") {
        /* Example snippet:
         *
         * // Enum pair (value enum, string enum name) sequence.
         * constexpr auto& entries = magic_enum::enum_entries<Color>();
         * std::cout << "Colors entries:";
         * for (const auto& e : entries) {
         *   std::cout << " "  << e.second << " = " << static_cast<int>(e.first);
         * }
         * std::cout << std::endl;
         * // Color entries: RED = -10 BLUE = 0 GREEN = 10
         */
        constexpr auto &entries = magic_enum::enum_entries<Color>();
        for (const auto &e: entries) {
            auto label = e.second;
            auto value = static_cast<int>(e.first);
            INFO("Color entry: ", label, " = ", value);
            switch (value) {
                case -10:
                            CHECK(label == "RED");
                    break;
                case 0:
                            CHECK(label == "BLUE");
                    break;
                case 10:
                            CHECK(label == "GREEN");
                    break;
                default:
                            FAIL("Unknown value");
            }
        }
    }
}