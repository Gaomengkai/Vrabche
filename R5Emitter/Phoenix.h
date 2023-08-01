//
// Created by gaome on 2023/7/30.
//

#ifndef IRBACKENDR5_PHOENIX_H
#define IRBACKENDR5_PHOENIX_H
#include "R5Def.h"
#include <unordered_map>
#include <list>
#include <algorithm>
using lsPair = std::pair<int, int>;

// 判断两个线段是否相交
static bool isIntersect(const std::pair<int, int>& segment1, const std::pair<int, int>& segment2) {
    return segment1.second > segment2.first && segment2.second > segment1.first;
}

// 判断两个有序线段列表是否相交
static bool areSegmentsIntersecting(const std::list<std::pair<int, int>>& list1,
                             const std::list<std::pair<int, int>>& list2) {
    auto it1 = list1.begin();
    auto it2 = list2.begin();

    while (it1 != list1.end() && it2 != list2.end()) {
        // 判断当前两个线段是否相交
        if (isIntersect(*it1, *it2)) {
            return true;
        }

        // 移动较小的终点对应的迭代器，因为它们不可能与其他线段相交
        if (it1->second < it2->second) {
            ++it1;
        } else {
            ++it2;
        }
    }

    return false;
}

// 一个寄存器的lifespan，可能有多个生死段。
// 必须倒序扫描基本块，才能构建lifespan。
// 先死而后生，此乃生死循环。凤凰涅槃，浴火重生。
struct Phoenix {
    std::list<lsPair> ls;
    inline void       death(int j)
    {
        if (ls.empty()) {
            // 新建一个生死段
            ls.emplace_back(-1, j);
        } else {
            // 如果最后段的死亡时间是-1，那么就更新它的死亡时间，否则新建一个生死段
            if (ls.back().first == -1) {   // 说明这个段还没活过来
                ;                          // 不必更新
            } else {
                ls.emplace_back(-1, j);
            }
        }
    }
    inline void birth(int j)
    {
        if (ls.empty()) {
            // 新建一个生死段
            ls.emplace_back(j, -1);
        } else {
            // 直接更新最后段的出生时间
            ls.back().first = j;
        }
    }
    inline bool isDead(int j)
    {
        if (ls.empty()) {
            return false;
        } else {
            // 它是个范围，所以要用>=
            if (ls.back().second == -1 || ls.back().first != -1)
                return false;
            else
                return ls.back().second >= j;
        }
    }
    [[maybe_unused]] inline bool isBorn(int j) { return false; }
    inline bool                  isNowDying(int j)
    {
        if (ls.empty()) {
            return false;
        } else {
            // 遍历所有ls，如果相等，就是现在正在死亡
            return std::any_of(ls.begin(), ls.end(), [j](const lsPair& p) {
                return p.second == j;
            });
        }
    }
    inline bool isNowBearing(int j)
    {
        if (ls.empty()) {
            return false;
        } else {
            // 遍历所有ls，如果相等，就是现在正在死亡
            return std::any_of(ls.begin(), ls.end(), [j](const lsPair& p) { return p.first == j; });
        }
    }
    inline bool isFree(int j)
    {
        if (ls.empty()) {
            return true;
        } else {
            // 范围，是范围！
            return (!isDead(j)) && ls.back().second < j;
        }
    }
    inline bool isComplete()
    {
        if (ls.empty()) {
            return false;
        } else {
            return (ls.back().second != -1) && (ls.back().first != -1);
        }
    }
    // 重载<，用于排序.仅对虚拟寄存器有效。
    inline bool operator<(const Phoenix& rhs) const
    {
        if (ls.empty() || rhs.ls.empty()) {
            return false;
        } else {
            return ls.back().second < rhs.ls.back().second;
        }
    }
    // 两个凤凰相交
    inline bool operator^(const Phoenix& rhs) const
    {
        // 都是空的，不相交
        if (ls.empty() || rhs.ls.empty()) {
            return false;
        } else {
            return areSegmentsIntersecting(ls, rhs.ls);
        }
    }
};

using LifespanMap = std::unordered_map<string, Phoenix>;
#endif   // IRBACKENDR5_PHOENIX_H
