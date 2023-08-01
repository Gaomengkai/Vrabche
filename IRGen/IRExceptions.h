//
// Created by gao on 6/29/23.
//

#ifndef SYSYLEX_IREXCEPTIONS_H
#define SYSYLEX_IREXCEPTIONS_H

#include <stdexcept>


namespace IRCtrl
{

class NotImplementedException : public std::logic_error
{
public:
    NotImplementedException()
        : std::logic_error("IRFunction not yet implemented.")
    {
    }
};

}   // namespace IRCtrl

#endif   // SYSYLEX_IREXCEPTIONS_H
