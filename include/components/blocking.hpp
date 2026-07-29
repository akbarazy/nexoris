#pragma once

enum class BodyType : int {
    Half = 0,
    Full = 1
};

struct Blocking {
    BodyType bodyType = BodyType::Full;
    float ceilOffsetY;
};
