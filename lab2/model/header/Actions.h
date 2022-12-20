//
// Created by popca on 12/12/2022.
//

#pragma once

#include "Production.h"
#include "LR0Item.h"

enum class ActionType {
    SHIFT,
    REDUCE,
    ERROR,
    ACCEPT,
    SHIFT_REDUCE_CONFLICT,
    REDUCE_REDUCE_CONFLICT
};

class Action {
protected:
    ActionType actionType;

public:
    virtual ActionType type() const;
    friend std::ostream &operator<<(std::ostream &os, Action& object);
};

class ShiftAction: public Action {
public:
    ShiftAction();
    friend std::ostream &operator<<(std::ostream &os, ShiftAction& object);
    ActionType type() const override;
};

class ReduceAction: public Action {
private:

public:
    Production production;
    ReduceAction(Production  production);
    friend std::ostream &operator<<(std::ostream &os, ReduceAction& object);
    ActionType type() const override;
};

class ErrorAction: public Action {
public:
    ErrorAction();
    friend std::ostream &operator<<(std::ostream &os, ErrorAction& object);
    ActionType type() const override;
};

class AcceptAction: public Action {
public:
    AcceptAction();
    friend std::ostream &operator<<(std::ostream &os, AcceptAction& object);
    ActionType type() const override;
};

class ShiftReduceConflict: public Action {
private:
    LR0Item shiftItem;
    LR0Item reduceItem;

public:
    ShiftReduceConflict(LR0Item  shiftItem, LR0Item  reduceItem);
    friend std::ostream &operator<<(std::ostream &os, ShiftReduceConflict& object);
    ActionType type() const override;
};

class ReduceReduceConflict: public Action {
private:
    LR0Item firstReduceItem;
    LR0Item secondReduceItem;

public:
    ReduceReduceConflict(LR0Item  firstReduceItem, LR0Item  secondReduceItem);
    friend std::ostream &operator<<(std::ostream &os, ReduceReduceConflict& object);
    ActionType type() const override;
};