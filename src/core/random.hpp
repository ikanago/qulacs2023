#pragma once

#include <limits>
#include <random>

#include "types.hpp"

class Random {
private:
    std::uniform_real_distribution<double> uniform_dist;
    std::normal_distribution<double> normal_dist;
    std::mt19937_64 mt;

public:
    /**
     * \~japanese-en コンストラクタ
     */
    Random() : uniform_dist(0, 1), normal_dist(0, 1) {
        std::random_device rd;
        mt.seed(rd());
    }

    /**
     * \~japanese-en シードを設定する
     *
     * @param seed シード値
     */
    void set_seed(uint64_t seed) { mt.seed(seed); }
    /**
     * \~japanese-en \f$[0,1)\f$の一様分布から乱数を生成する
     *
     * @return 生成された乱数
     */
    double uniform() { return uniform_dist(mt); }

    /**
     * \~japanese-en 期待値0、分散1の正規分から乱数を生成する
     *
     * @return double 生成された乱数
     */
    double normal() { return normal_dist(mt); }

    /**
     * \~japanese-en 64bit整数の乱数を生成する
     *
     * @return 生成された乱数
     */
    UINT int64() { return mt(); }

    /**
     * \~japanese-en 32bit整数の乱数を生成する
     *
     * @return 生成された乱数
     */
    std::uint32_t int32() { return mt() % UINT32_MAX; }
};