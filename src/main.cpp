#include <iostream>
#include <random>

bool isInCircle(const double x, const double y, const double x1, const double y1, const double r1) {
    return r1 * r1 > (x - x1) * (x - x1) + (y - y1) * (y - y1);
}

int main() {
    double x1, y1, r1, x2, y2, r2, x3, y3, r3;
    x1 = 1;
    y1 = 1;
    r1 = 1;
    x2 = 1.5;
    y2 = 2;
    r2 = 1.118033988749895;
    x3 = 2;
    y3 = 1.5;
    r3 = 1.118033988749895;

    double answer = 0.9445171858994637;

    const auto maxX = std::max(x1 + r1, std::max(x2 + r2, x3 + r3));
    const auto minX = std::min(x1 - r1, std::min(x2 - r2, x3 - r3));
    const auto maxY = std::max(y1 + r1, std::max(y2 + r2, y3 + r3));
    const auto minY = std::min(y1 - r1, std::min(y2 - r2, y3 - r3));

    const auto innerMaxX = std::min(x1 + r1, std::min(x2 + r2, x3 + r3));
    const auto innerMinX = std::max(x1 - r1, std::max(x2 - r2, x3 - r3));
    const auto innerMaxY = std::min(y1 + r1, std::min(y2 + r2, y3 + r3));
    const auto innerMinY = std::max(y1 - r1, std::max(y2 - r2, y3 - r3));
    if (innerMaxX < innerMinX || innerMaxY < innerMinY) {
        std::cout << 0.0 << std::endl;
        return 0;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> bigRectangleX(minX, maxX);
    std::uniform_real_distribution<double> bigRectangleY(minY, maxY);

    std::uniform_real_distribution<double> smallRectangleX(innerMinX, innerMaxX);
    std::uniform_real_distribution<double> smallRectangleY(innerMinY, innerMaxY);

    std::cout << "Small square:" << std::endl;
    for (int num = 100; num < 100000; num += 500) {
        if (num == 600) num -= 100;
        int counter = 0;
        for (int i = 0; i < num; i++) {
            double x = smallRectangleX(gen);
            double y = smallRectangleY(gen);
            if (isInCircle(x, y, x1, y1, r1) &&
                isInCircle(x, y, x2, y2, r2) && isInCircle(x, y, x3, y3, r3)) counter++;
        }
        std::cout << num << " rnd dots. accuracy: "
        << (innerMaxX - innerMinX) * (innerMaxY - innerMinY) * counter / num / answer << std::endl;
    }

    std::cout << "Big square:" << std::endl;
    for (int num = 100; num <= 100000; num += 500) {
        if (num == 600) num -= 100;
        int counter = 0;
        for (int i = 0; i < num; i++) {
            double x = bigRectangleX(gen);
            double y = bigRectangleY(gen);
            if (isInCircle(x, y, x1, y1, r1) &&
                isInCircle(x, y, x2, y2, r2) && isInCircle(x, y, x3, y3, r3)) counter++;
        }
        std::cout << num << " rnd dots. accuracy: "
        << (maxX - minX) * (maxY - minY) * counter / num / answer << std::endl;
    }
}
