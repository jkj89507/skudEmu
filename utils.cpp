#include "utils.h"

Utils::Utils()
{
}

Utils::~Utils()
{
}

void Utils::drawWorkplace(MyScene* scene, int width, int height)
{
    for (int y = 10; y < height; y += 40) {
        scene->addLine(10, y, width - 40, y, QPen(Qt::black));
    }
    for (int x = 10; x < width; x += 40) {
        scene->addLine(x, 10, x, height - 40,QPen(Qt::black));
    }
}
