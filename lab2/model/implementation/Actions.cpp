//
// Created by popca on 12/12/2022.
//

#include "../header/Actions.h"

#include <utility>

ActionType Action::type() const {
    return actionType;
}

std::ostream &operator<<(std::ostream &os, Action &object) {
    os << "Action ";
    return os;
}

ShiftAction::ShiftAction() : Action() {

}

std::ostream &operator<<(std::ostream &os, ShiftAction &object) {
    os << "Shift Action ";
    return os;
}

ActionType ShiftAction::type() const {
    return ActionType::SHIFT;
}

ReduceAction::ReduceAction(Production production) : Action(), production(std::move(production)) {

}

std::ostream &operator<<(std::ostream &os, ReduceAction &object) {
    os << "Reduce Action with production " << object.production;
    return os;
}

ActionType ReduceAction::type() const {
    return ActionType::REDUCE;
}

AcceptAction::AcceptAction() : Action() {

}

std::ostream &operator<<(std::ostream &os, AcceptAction &object) {
    os << "Accept action ";
    return os;
}

ActionType AcceptAction::type() const {
    return ActionType::ACCEPT;
}

ShiftReduceConflict::ShiftReduceConflict(LR0Item shiftItem, LR0Item reduceItem) :
        Action(), shiftItem(std::move(shiftItem)), reduceItem(std::move(reduceItem)) {

}

std::ostream &operator<<(std::ostream &os, ShiftReduceConflict &object) {
    os << "Shift Reduce Conflict " << object.shiftItem << " " << object.reduceItem;
    return os;
}

ActionType ShiftReduceConflict::type() const {
    return ActionType::SHIFT_REDUCE_CONFLICT;
}

ReduceReduceConflict::ReduceReduceConflict(LR0Item firstReduceItem, LR0Item secondReduceItem) :
        Action(), firstReduceItem(std::move(firstReduceItem)),
        secondReduceItem(std::move(secondReduceItem)) {

}

std::ostream &operator<<(std::ostream &os, ReduceReduceConflict &object) {
    os << "Reduce Reduce Conflict " << object.firstReduceItem << " " << object.secondReduceItem;
    return os;
}

ActionType ReduceReduceConflict::type() const {
    return ActionType::REDUCE_REDUCE_CONFLICT;
}

ErrorAction::ErrorAction() : Action() {

}

std::ostream &operator<<(std::ostream &os, ErrorAction &object) {
    os << "Error Action ";
    return os;
}

ActionType ErrorAction::type() const {
    return ActionType::ERROR;
}
