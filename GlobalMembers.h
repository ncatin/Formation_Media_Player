#include <memory>
#include "DancerDot.h"

#ifndef GLOBALMEMBERS_H
#define GLOBALMEMBERS_H
namespace GlobalMembers{
    bool loaded;
    std::vector<std::unique_ptr<DancerDot>> dancers;
}
#endif // GLOBALMEMBERS_H

