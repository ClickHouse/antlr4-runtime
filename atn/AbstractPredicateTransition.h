/* Copyright (c) 2012 The ANTLR Project Contributors. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#pragma once

#include "atn/Transition.h"

namespace antlr4 {
namespace atn {

  class ANTState;

  class ANTLR4CPP_PUBLIC AbstractPredicateTransition : public Transition {

  public:
    AbstractPredicateTransition(ATNState *target);

  };

} // namespace atn
} // namespace antlr4
