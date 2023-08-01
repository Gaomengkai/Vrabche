//
// Created by gaome on 2023/7/20.
//

#ifndef IRBACKENDR5_ARRAY_HELPER_H
#define IRBACKENDR5_ARRAY_HELPER_H
#include <forward_list>
#include "R5Def.h"
#include "MiddleIRVal.h"
namespace MiddleIR
{
template<typename T>
struct ArrayNode {
    std::vector<T> data;
    size_t         zeroBytes;
};

template<typename T>
using Chain = std::forward_list<ArrayNode<T>>;

template<typename T>
Chain<T> makeArrayChain(const shared_ptr<R5IRArray>& array)
{
    Chain<T> chain;
    if (array->empty()) {
        size_t       arrSizeBytes = array->getSizeBytes();
        ArrayNode<T> node{{}, arrSizeBytes};
        chain.push_front(node);
    } else if (array->getArrayType()->getElementType()->type == MiddleIRType::INT) {
        ArrayNode<T> node{{}, 0};
        for (auto& val : array->_elements) {
            auto intVal = dynamic_pointer_cast<R5IRValConstInt>(val);
            node.data.push_back(intVal->getValue());
        }
        chain.push_front(node);
    } else if (array->getArrayType()->getElementType()->type == MiddleIRType::FLOAT) {
        ArrayNode<T> node{{}, 0};
        for (auto& val : array->_elements) {
            auto fVal = dynamic_pointer_cast<R5IRValConstFloat>(val);
            node.data.push_back(fVal->getValue());
        }
        chain.push_front(node);
    } else {
        auto arrayType = array->getArrayType();
        for (auto& val : array->_elements) {
            auto subArray        = dynamic_pointer_cast<R5IRArray>(val);
            auto zeroInitializer = dynamic_pointer_cast<R5IRZeroInitializerVal>(val);
            if (subArray) {
                auto subChain = makeArrayChain<T>(subArray);
                chain.splice_after(chain.before_begin(), subChain);
            } else if (zeroInitializer) {
                // 猜出每个元素的大小
                auto subArrayType = arrayType->getElementType();
                IR_ASSERT(
                    subArrayType->type == MiddleIRType::ARRAY,
                    "makeIntArrayChain: subArrayType must be ARRAY"
                );
                auto subArraySize = dynamic_pointer_cast<ArrayType>(subArrayType)->getSizeBytes();
                ArrayNode<T> node{{}, subArraySize};
                chain.push_front(node);
            } else {
                RUNTIME_ERROR("Not implemented");
            }
        }
    }
    return chain;
}

template<typename T>
Chain<T> flattenChain(Chain<T> chain)
{
    chain.reverse();
    Chain<T> newChain;
    enum State {
        ZERO,
        NON_ZERO,
    } state = ZERO;
    ArrayNode<T> newNode{{}, 0};
    for (auto& node : chain) {
        if (node.zeroBytes) {
            if (state == ZERO) {
                newNode.zeroBytes += node.zeroBytes;
            } else {
                newChain.push_front(newNode);
                newNode = ArrayNode<T>{{}, node.zeroBytes};
                state   = ZERO;
            }
        } else {
            if (state == ZERO) {
                for (auto j : node.data) {
                    if (j == 0) {
                        if (state == ZERO) {
                            newNode.zeroBytes += sizeof(T);
                        } else {
                            newChain.push_front(newNode);
                            newNode = ArrayNode<T>{{}, sizeof(T)};
                            state   = ZERO;
                        }
                    } else {
                        if (state == ZERO) {
                            newChain.push_front(newNode);
                            newNode = ArrayNode<T>{{}, 0};
                            newNode.data.push_back(j);
                            state = NON_ZERO;
                        } else {
                            newNode.data.push_back(j);
                        }
                    }
                }
            } else {
                newNode.data.insert(newNode.data.end(), node.data.begin(), node.data.end());
            }
        }
    }
    newChain.push_front(newNode);
    newChain.reverse();
    return newChain;
}

}   // namespace MiddleIR
#endif   // IRBACKENDR5_ARRAY_HELPER_H
