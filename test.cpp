#include <gtest/gtest.h>
#include "s21_matrix_oop.h"

TEST(create_and_remove_suit, create_and_remove) {
    S21Matrix a;
    S21Matrix b(a);
    S21Matrix c(5, 6);
    S21Matrix d((S21Matrix&&)a);
    ASSERT_ANY_THROW(S21Matrix e(0, 5));
}

TEST(is_equal_suit, is_equal) {
    S21Matrix a(2, 2);
    a(1, 1) = 4.;
    S21Matrix b(2, 2);
    b(1, 1) = 4.;
    ASSERT_EQ(a.eq_matrix(b), true);

    b(0, 0) = 15;
    ASSERT_EQ(a.eq_matrix(b), false);

    b = S21Matrix(2, 3);
    ASSERT_EQ(a.eq_matrix(b), false);

    S21Matrix a1(3, 3);
    S21Matrix b1(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a1(i, j) = (i + j) * 0.25;
            b1(i, j) = (i + j) * 0.25;
        }
    }
    ASSERT_EQ(a1.eq_matrix(b1), true);

    a1(1, 1) = 1.12345678;
    b1(1, 1) = 1.12345679;
    ASSERT_EQ(a1.eq_matrix(b1), false);
}

TEST(sum_matrix_suit, sum_matrix) {
    S21Matrix a(2, 2);
    S21Matrix b(2, 2);
    S21Matrix c(2, 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            a(i, j) = (i + j) * 0.25;
            b(i, j) = (i + j) * 0.25;
            c(i, j) = (i + j) * 0.25 * 2;
        }
    }
    a.sum_matrix(b);
    ASSERT_EQ(a.eq_matrix(c), true);

    S21Matrix a1(12, 2);
    S21Matrix b1(12, 2);
    S21Matrix c1(12, 2);
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 2; j++) {
            a1(i, j) = (i + j) * 0.25 * (-1);
            b1(i, j) = (i + j) * 0.25 * (-1);
            c1(i, j) = (i + j) * 0.25 * 2 * (-1);
        }
    }
    a1.sum_matrix(b1);
    ASSERT_EQ(a1.eq_matrix(c1), true);

    S21Matrix a2;
    S21Matrix b2;
    S21Matrix c2;
    a2(0, 0) = 1;
    a2(1, 1) = 1;
    b2(2, 2) = 1;
    c2(0, 0) = 1;
    c2(1, 1) = 1;
    c2(2, 2) = 1;
    a2.sum_matrix(b2);
    ASSERT_EQ(a2.eq_matrix(c2), true);

    ASSERT_ANY_THROW(a2.sum_matrix(a));
}

TEST(sub_matrix_suit, sub_matrix) {
    S21Matrix a(2, 2);
    S21Matrix b(2, 2);
    S21Matrix c(2, 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            a(i, j) = (i + j) * 0.25;
            b(i, j) = (i + j) * 0.25;
            c(i, j) = 0;
        }
    }
    a.sub_matrix(b);
    ASSERT_EQ(a.eq_matrix(c), true);

    S21Matrix a1(12, 2);
    S21Matrix b1(12, 2);
    S21Matrix c1(12, 2);
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 2; j++) {
            a1(i, j) = (i + j) * 0.25 * (-1);
            b1(i, j) = (i + j) * 0.25;
            c1(i, j) = (i + j) * 0.25 * 2 * (-1);
        }
    }
    a1.sub_matrix(b1);
    ASSERT_EQ(a1.eq_matrix(c1), true);

    S21Matrix a2;
    S21Matrix b2;
    S21Matrix c2;
    a2(0, 0) = 1;
    a2(1, 1) = 1;
    b2(2, 2) = 1;
    c2(0, 0) = 1;
    c2(1, 1) = 1;
    c2(2, 2) = -1;
    a2.sub_matrix(b2);
    ASSERT_EQ(a2.eq_matrix(c2), true);

    // ASSERT_ANY_THROW(a2.sub_matrix(a));
}

TEST(mult_number_suit, mult_number) {
    S21Matrix a;
    S21Matrix b;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a(i, j) = i + j + 1;
            b(i, j) = a(i, j) * 2;
        }
    }
    a.mul_number(2);
    ASSERT_EQ(a.eq_matrix(b), true);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a(i, j) = 0;
            b(i, j) = 0;
        }
    }
    a.mul_number(2);
    ASSERT_EQ(a.eq_matrix(b), true);

    ASSERT_ANY_THROW(a.mul_number(NAN));
}

TEST(mult_matrix_suit, mult_matrix) {
    S21Matrix a;
    S21Matrix b;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a(i, j) = (i * 3) + j + 1;
            b(i, j) = 2;
        }
    }
    S21Matrix c;
    c(0, 0) = 12;
    c(0, 1) = 12;
    c(0, 2) = 12;
    c(1, 0) = 30;
    c(1, 1) = 30;
    c(1, 2) = 30;
    c(2, 0) = 48;
    c(2, 1) = 48;
    c(2, 2) = 48;
    a.mul_matrix(b);
    ASSERT_EQ(a.eq_matrix(c), true);

    S21Matrix a1(3, 2);
    a1(0, 0) = 1;
    a1(0, 1) = 4;
    a1(1, 0) = 2;
    a1(1, 1) = 5;
    a1(2, 0) = 3;
    a1(2, 1) = 6;

    S21Matrix b1(2, 3);
    b1(0, 0) = 1;
    b1(0, 1) = -1;
    b1(0, 2) = 1;
    b1(1, 0) = 2;
    b1(1, 1) = 3;
    b1(1, 2) = 4;

    S21Matrix c1;
    c1(0, 0) = 9;
    c1(0, 1) = 11;
    c1(0, 2) = 17;
    c1(1, 0) = 12;
    c1(1, 1) = 13;
    c1(1, 2) = 22;
    c1(2, 0) = 15;
    c1(2, 1) = 15;
    c1(2, 2) = 27;

    a1.mul_matrix(b1);
    ASSERT_EQ(a1.eq_matrix(c1), true);

    ASSERT_ANY_THROW(c1.mul_matrix(b1));
}

TEST(transpose_suit, transpose) {
    S21Matrix a(3, 2);
    a(0, 0) = 1;
    a(0, 1) = 4;
    a(1, 0) = 2;
    a(1, 1) = 5;
    a(2, 0) = 3;
    a(2, 1) = 6;

    S21Matrix b(2, 3);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            b(i, j) = (i * 3) + j + 1;
        }
    }

    S21Matrix c(a.transpose());
    ASSERT_EQ(c.eq_matrix(b), true);

    S21Matrix a1(1, 1);
    S21Matrix b1(a1);
    S21Matrix c1(a1.transpose());
    ASSERT_TRUE(a1.eq_matrix(b1));

    S21Matrix a2;
    a2(0, 0) = 1;
    a2(1, 1) = 1;
    a2(2, 2) = 1;
    S21Matrix b2(a2);
    S21Matrix c2(a2.transpose());
    ASSERT_TRUE(a2.eq_matrix(b2));
}

TEST(calc_complements_suit, calc_complements) {
    S21Matrix a;
    a(0, 0) = 1;
    a(0, 1) = 2;
    a(0, 2) = 3;
    a(1, 0) = 0;
    a(1, 1) = 4;
    a(1, 2) = 2;
    a(2, 0) = 5;
    a(2, 1) = 2;
    a(2, 2) = 1;

    S21Matrix b;
    b(0, 0) = 0;
    b(0, 1) = 10;
    b(0, 2) = -20;
    b(1, 0) = 4;
    b(1, 1) = -14;
    b(1, 2) = 8;
    b(2, 0) = -8;
    b(2, 1) = -2;
    b(2, 2) = 4;

    S21Matrix c(a.calc_complements());
    ASSERT_TRUE(c.eq_matrix(b));

    S21Matrix a1(1, 1);
    // S21Matrix c1(a1.calc_complements());
    // ASSERT_TRUE(c1.eq_matrix(a1));
    ASSERT_ANY_THROW(a1.calc_complements());

    S21Matrix a2;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a2(i, j) = (i * 3) + j + 1;
        }
    }
    S21Matrix b2;
    b2(0, 0) = -3;
    b2(0, 1) = 6;
    b2(0, 2) = -3;
    b2(1, 0) = 6;
    b2(1, 1) = -12;
    b2(1, 2) = 6;
    b2(2, 0) = -3;
    b2(2, 1) = 6;
    b2(2, 2) = -3;
    S21Matrix c2(a2.calc_complements());
    ASSERT_TRUE(c2.eq_matrix(b2));

    S21Matrix a3(2, 3);
    ASSERT_ANY_THROW(a3.calc_complements());
}

TEST(determinant_suit, determinant) {
    S21Matrix a(1, 1);
    a(0, 0) = 15;
    double c = 15;
    ASSERT_EQ(a.determinant(), c);

    S21Matrix a1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a1(i, j) = (i * 3) + j + 1;
        }
    }
    c = 0;
    ASSERT_EQ(a1.determinant(), c);

    a1(2, 2) = 0;
    c = 27;
    ASSERT_EQ(a1.determinant(), c);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                a1(i, j) = 1;
            } else {
                a1(i, j) = 0;
            }
        }
    }
    c = 1;
    ASSERT_EQ(a1.determinant(), c);

    S21Matrix a2(2, 3);
    ASSERT_ANY_THROW(a2.determinant());
}

TEST(inverse_matrix_suit, inverse_matrix) {
    S21Matrix a;
    a(0, 0) = 1;
    a(0, 1) = 2;
    a(0, 2) = 3;
    a(1, 0) = 0;
    a(1, 1) = 4;
    a(1, 2) = 2;
    a(2, 0) = 5;
    a(2, 1) = 2;
    a(2, 2) = 1;

    S21Matrix b;
    b(0, 0) = 0;
    b(0, 1) = -0.1;
    b(0, 2) = 0.2;
    b(1, 0) = -0.25;
    b(1, 1) = 0.35;
    b(1, 2) = 0.05;
    b(2, 0) = 0.5;
    b(2, 1) = -0.2;
    b(2, 2) = -0.1;

    S21Matrix c(a.inverse_matrix());
    ASSERT_TRUE(b.eq_matrix(c));

    S21Matrix a1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                a1(i, j) = 1;
            } else {
                a1(i, j) = 0;
            }
        }
    }
    S21Matrix b1(a1);
    S21Matrix c1(a1.inverse_matrix());
    ASSERT_TRUE(c1.eq_matrix(b1));

    S21Matrix a2(1, 1);
    a2(0, 0) = 2;
    S21Matrix b2(1, 1);
    b2(0, 0) = 0.5;
    S21Matrix c2(a2.inverse_matrix());
    ASSERT_TRUE(c2.eq_matrix(b2));

    S21Matrix a3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a3(i, j) = (i * 3) + j + 1;
        }
    }
    ASSERT_ANY_THROW(a3.inverse_matrix());
}

TEST(operator_plus_suit, operator_plus) {
    S21Matrix a(2, 2);
    S21Matrix b(2, 2);
    S21Matrix c(2, 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            a(i, j) = (i + j) * 0.25;
            b(i, j) = (i + j) * 0.25;
            c(i, j) = (i + j) * 0.25 * 2;
        }
    }
    ASSERT_TRUE(c.eq_matrix(a + b));

    S21Matrix a1(12, 2);
    S21Matrix b1(12, 2);
    S21Matrix c1(12, 2);
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 2; j++) {
            a1(i, j) = (i + j) * 0.25 * (-1);
            b1(i, j) = (i + j) * 0.25 * (-1);
            c1(i, j) = (i + j) * 0.25 * 2 * (-1);
        }
    }
    ASSERT_TRUE(c1.eq_matrix(a1 + b1));

    S21Matrix a2;
    S21Matrix b2;
    S21Matrix c2;
    a2(0, 0) = 1;
    a2(1, 1) = 1;
    b2(2, 2) = 1;
    c2(0, 0) = 1;
    c2(1, 1) = 1;
    c2(2, 2) = 1;
    ASSERT_TRUE(c2.eq_matrix(a2 + b2));

    ASSERT_ANY_THROW(a2 + a);
}

TEST(operator_minus_suit, operator_minus) {
    S21Matrix a(2, 2);
    S21Matrix b(2, 2);
    S21Matrix c(2, 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            a(i, j) = (i + j) * 0.25;
            b(i, j) = (i + j) * 0.25;
            c(i, j) = 0;
        }
    }
    ASSERT_TRUE(c.eq_matrix(a - b));

    S21Matrix a1(12, 2);
    S21Matrix b1(12, 2);
    S21Matrix c1(12, 2);
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 2; j++) {
            a1(i, j) = (i + j) * 0.25 * (-1);
            b1(i, j) = (i + j) * 0.25;
            c1(i, j) = (i + j) * 0.25 * 2 * (-1);
        }
    }
    ASSERT_TRUE(c1.eq_matrix(a1 - b1));

    S21Matrix a2;
    S21Matrix b2;
    S21Matrix c2;
    a2(0, 0) = 1;
    a2(1, 1) = 1;
    b2(2, 2) = 1;
    c2(0, 0) = 1;
    c2(1, 1) = 1;
    c2(2, 2) = -1;
    ASSERT_TRUE(c2.eq_matrix(a2 - b2));

    ASSERT_ANY_THROW(a2 - a);
}

TEST(operator_mult_suit, mult_number) {
    S21Matrix a;
    S21Matrix b;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a(i, j) = i + j + 1;
            b(i, j) = a(i, j) * 2;
        }
    }
    ASSERT_TRUE(b.eq_matrix(a * 2));
    ASSERT_TRUE(b.eq_matrix(2 * a));

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a(i, j) = 0;
            b(i, j) = 0;
        }
    }
    ASSERT_TRUE(b.eq_matrix(a * 2));
    ASSERT_TRUE(b.eq_matrix(2 * a));

    ASSERT_ANY_THROW(a * NAN);
    ASSERT_ANY_THROW(NAN * a);
}

TEST(operator_mult_suit, mult_matrix) {
    S21Matrix a;
    S21Matrix b;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a(i, j) = (i * 3) + j + 1;
            b(i, j) = 2;
        }
    }
    S21Matrix c;
    c(0, 0) = 12;
    c(0, 1) = 12;
    c(0, 2) = 12;
    c(1, 0) = 30;
    c(1, 1) = 30;
    c(1, 2) = 30;
    c(2, 0) = 48;
    c(2, 1) = 48;
    c(2, 2) = 48;
    ASSERT_TRUE(c.eq_matrix(a * b));

    S21Matrix a1(3, 2);
    a1(0, 0) = 1;
    a1(0, 1) = 4;
    a1(1, 0) = 2;
    a1(1, 1) = 5;
    a1(2, 0) = 3;
    a1(2, 1) = 6;

    S21Matrix b1(2, 3);
    b1(0, 0) = 1;
    b1(0, 1) = -1;
    b1(0, 2) = 1;
    b1(1, 0) = 2;
    b1(1, 1) = 3;
    b1(1, 2) = 4;

    S21Matrix c1;
    c1(0, 0) = 9;
    c1(0, 1) = 11;
    c1(0, 2) = 17;
    c1(1, 0) = 12;
    c1(1, 1) = 13;
    c1(1, 2) = 22;
    c1(2, 0) = 15;
    c1(2, 1) = 15;
    c1(2, 2) = 27;

    ASSERT_TRUE(c1.eq_matrix(a1 * b1));

    ASSERT_ANY_THROW(c1 * b1);
}

TEST(operator_equal_suit, operator_equal) {
    S21Matrix a(2, 2);
    a(1, 1) = 4.;
    S21Matrix b(2, 2);
    b(1, 1) = 4.;
    ASSERT_TRUE(a == b);

    b(0, 0) = 15;
    ASSERT_FALSE(a == b);

    b = S21Matrix(2, 3);
    ASSERT_FALSE(a == b);

    S21Matrix a1(3, 3);
    S21Matrix b1(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a1(i, j) = (i + j) * 0.25;
            b1(i, j) = (i + j) * 0.25;
        }
    }
    ASSERT_TRUE(a1 == b1);

    a1(1, 1) = 1.12345678;
    b1(1, 1) = 1.12345679;
    ASSERT_FALSE(a1 == b1);
}

TEST(addition_assignment_suit, addition_assignment) {
    S21Matrix a(2, 2);
    S21Matrix b(2, 2);
    S21Matrix c(2, 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            a(i, j) = (i + j) * 0.25;
            b(i, j) = (i + j) * 0.25;
            c(i, j) = (i + j) * 0.25 * 2;
        }
    }
    a += b;
    ASSERT_TRUE(c.eq_matrix(a));

    S21Matrix a1(12, 2);
    S21Matrix b1(12, 2);
    S21Matrix c1(12, 2);
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 2; j++) {
            a1(i, j) = (i + j) * 0.25 * (-1);
            b1(i, j) = (i + j) * 0.25 * (-1);
            c1(i, j) = (i + j) * 0.25 * 2 * (-1);
        }
    }
    a1 += b1;
    ASSERT_TRUE(c1.eq_matrix(a1));

    S21Matrix a2;
    S21Matrix b2;
    S21Matrix c2;
    a2(0, 0) = 1;
    a2(1, 1) = 1;
    b2(2, 2) = 1;
    c2(0, 0) = 1;
    c2(1, 1) = 1;
    c2(2, 2) = 1;
    a2 += b2;
    ASSERT_TRUE(c2.eq_matrix(a2));

    ASSERT_ANY_THROW(a2 += a);
}

TEST(difference_assignment_suit, difference_assignment) {
    S21Matrix a(2, 2);
    S21Matrix b(2, 2);
    S21Matrix c(2, 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            a(i, j) = (i + j) * 0.25;
            b(i, j) = (i + j) * 0.25;
            c(i, j) = 0;
        }
    }
    a -= b;
    ASSERT_TRUE(c.eq_matrix(a));

    S21Matrix a1(12, 2);
    S21Matrix b1(12, 2);
    S21Matrix c1(12, 2);
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 2; j++) {
            a1(i, j) = (i + j) * 0.25 * (-1);
            b1(i, j) = (i + j) * 0.25;
            c1(i, j) = (i + j) * 0.25 * 2 * (-1);
        }
    }
    a1 -= b1;
    ASSERT_TRUE(c1.eq_matrix(a1));

    S21Matrix a2;
    S21Matrix b2;
    S21Matrix c2;
    a2(0, 0) = 1;
    a2(1, 1) = 1;
    b2(2, 2) = 1;
    c2(0, 0) = 1;
    c2(1, 1) = 1;
    c2(2, 2) = -1;
    a2 -= b2;
    ASSERT_TRUE(c2.eq_matrix(a2));

    ASSERT_ANY_THROW(a2 -= a);
}

TEST(multiplication_assignment_suit, mult_number) {
    S21Matrix a;
    S21Matrix b;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a(i, j) = i + j + 1;
            b(i, j) = a(i, j) * 2;
        }
    }
    a *= 2;
    ASSERT_TRUE(b.eq_matrix(a));

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a(i, j) = 0;
            b(i, j) = 0;
        }
    }
    a *= 2;
    ASSERT_TRUE(b.eq_matrix(a));

    ASSERT_ANY_THROW(a *= NAN);
}

TEST(multiplication_assignment_suit, mult_matrix) {
    S21Matrix a;
    S21Matrix b;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a(i, j) = (i * 3) + j + 1;
            b(i, j) = 2;
        }
    }
    S21Matrix c;
    c(0, 0) = 12;
    c(0, 1) = 12;
    c(0, 2) = 12;
    c(1, 0) = 30;
    c(1, 1) = 30;
    c(1, 2) = 30;
    c(2, 0) = 48;
    c(2, 1) = 48;
    c(2, 2) = 48;

    a *= b;
    ASSERT_TRUE(c.eq_matrix(a));

    S21Matrix a1(3, 2);
    a1(0, 0) = 1;
    a1(0, 1) = 4;
    a1(1, 0) = 2;
    a1(1, 1) = 5;
    a1(2, 0) = 3;
    a1(2, 1) = 6;

    S21Matrix b1(2, 3);
    b1(0, 0) = 1;
    b1(0, 1) = -1;
    b1(0, 2) = 1;
    b1(1, 0) = 2;
    b1(1, 1) = 3;
    b1(1, 2) = 4;

    S21Matrix c1;
    c1(0, 0) = 9;
    c1(0, 1) = 11;
    c1(0, 2) = 17;
    c1(1, 0) = 12;
    c1(1, 1) = 13;
    c1(1, 2) = 22;
    c1(2, 0) = 15;
    c1(2, 1) = 15;
    c1(2, 2) = 27;

    a1 *= b1;
    ASSERT_TRUE(c1.eq_matrix(a1));

    ASSERT_ANY_THROW(c1 *= b1);
}

TEST(set_and_get_rows_suit, set_get_rows) {
    S21Matrix a(4, 5);
    ASSERT_EQ(a.get_rows(), 4);

    S21Matrix b(a);
    a.set_rows(5);
    ASSERT_EQ(a.get_rows(), 5);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            ASSERT_DOUBLE_EQ(b(i, j), a(i, j));
        }
    }

    a.set_rows(2);
    ASSERT_EQ(a.get_rows(), 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++) {
            ASSERT_DOUBLE_EQ(b(i, j), a(i, j));
        }
    }
    ASSERT_ANY_THROW(a.set_rows(-1));
}

TEST(set_and_get_cols_suit, set_get_cols) {
    S21Matrix a(5, 4);
    ASSERT_EQ(a.get_cols(), 4);

    S21Matrix b(a);
    a.set_cols(5);
    ASSERT_EQ(a.get_cols(), 5);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            ASSERT_DOUBLE_EQ(b(i, j), a(i, j));
        }
    }

    a.set_cols(2);
    ASSERT_EQ(a.get_cols(), 2);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 2; j++) {
            ASSERT_DOUBLE_EQ(b(i, j), a(i, j));
        }
    }
    ASSERT_ANY_THROW(a.set_cols(-1));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
