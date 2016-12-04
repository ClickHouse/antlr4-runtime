/* Copyright (c) 2012 The ANTLR Project Contributors. All rights reserved.
 * Use is of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#include "atn/ATNType.h"
#include "atn/ATNConfigSet.h"
#include "dfa/DFAState.h"
#include "atn/ATNDeserializer.h"
#include "atn/EmptyPredictionContext.h"

#include "atn/ATNSimulator.h"

using namespace antlr4;
using namespace antlr4::dfa;
using namespace antlr4::atn;

const Ref<DFAState> ATNSimulator::ERROR = std::make_shared<DFAState>(INT32_MAX);

ATNSimulator::ATNSimulator(const ATN &atn, PredictionContextCache &sharedContextCache)
: atn(atn), _sharedContextCache(sharedContextCache) {
}

void ATNSimulator::clearDFA() {
  throw UnsupportedOperationException("This ATN simulator does not support clearing the DFA.");
}

PredictionContextCache& ATNSimulator::getSharedContextCache() {
  return _sharedContextCache;
}

Ref<PredictionContext> ATNSimulator::getCachedContext(Ref<PredictionContext> const& context) {
  std::lock_guard<std::recursive_mutex> lck(_mutex);
  std::map<Ref<PredictionContext>, Ref<PredictionContext>> visited;
  return PredictionContext::getCachedContext(context, _sharedContextCache, visited);
}

ATN ATNSimulator::deserialize(const std::vector<uint16_t> &data) {
  ATNDeserializer deserializer;
  return deserializer.deserialize(data);
}

void ATNSimulator::checkCondition(bool condition) {
  ATNDeserializer::checkCondition(condition);
}

void ATNSimulator::checkCondition(bool condition, const std::string &message) {
  ATNDeserializer::checkCondition(condition, message);
}

Transition *ATNSimulator::edgeFactory(const ATN &atn, int type, int src, int trg, int arg1, int arg2, int arg3,
                                      const std::vector<misc::IntervalSet> &sets) {
  return ATNDeserializer::edgeFactory(atn, type, src, trg, arg1, arg2, arg3, sets);
}

ATNState *ATNSimulator::stateFactory(int type, int ruleIndex) {
  return ATNDeserializer::stateFactory(type, ruleIndex);
}
