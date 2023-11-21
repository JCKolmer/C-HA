#include "validator.h"

#include <variant>
#include <vector>

#include "token.h"

namespace sql {

bool SqlValidator::is_valid() const {
    // TODO: Implement this
    return std::holds_alternative<state::Valid>(state_);
}

void SqlValidator::handle(const Token &token) {
    // TODO: Implement this
    if(std::holds_alternative<state::Start>(state_))
    {
        state::Start currentState = std::get<state::Start>(state_);
        state_ = transition(currentState ,token);
    }
    else if(std::holds_alternative<state::Valid>(state_))
    {
        state::Valid currentState = std::get<state::Valid>(state_);
        state_ = transition(currentState ,token);
    }
     else if(std::holds_alternative<state::SelectStmt>(state_))
    {
         state::SelectStmt currentState = std::get<state::SelectStmt>(state_);
        state_ = transition(currentState ,token);
    }
     else if(std::holds_alternative<state::Invalid>(state_))
    {
        state::Invalid currentState = std::get<state::Invalid>(state_);
        state_ = transition(std::get<state::Invalid>(state_) ,token);
    }
     else if(std::holds_alternative<state::AllColumns>(state_))
    {
        state_ = transition(std::get<state::AllColumns>(state_) ,token);
    }
     else if(std::holds_alternative<state::NamedColumn>(state_))
    {
        state_ = transition(std::get<state::NamedColumn>(state_) ,token);
    }
     else if(std::holds_alternative<state::MoreColumns>(state_))
    {
        state_ = transition(std::get<state::MoreColumns>(state_) ,token);
    }
     else if(std::holds_alternative<state::FromClause>(state_))
    {
        state_ = transition(std::get<state::FromClause>(state_) ,token);
    }
     else if(std::holds_alternative<state::TableName>(state_))
    {
        state_ = transition(std::get<state::TableName>(state_) ,token);
    }
}

struct TransitionFromStartVisitor {
    // Only the `Select` token advances the FSM from the `Start` state
    // TODO: Correct the behaviour
    State operator()(token::Select) const { return state::SelectStmt{}; }

    // All the other tokens, put it in the invalid state
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }
};

State transition(state::Start, const Token &token) {
    return std::visit(TransitionFromStartVisitor{}, token.value());
}

struct TransitionFromSelectVisitor {
    State operator()(token::Asterisks) const { return state::AllColumns{}; }
    State operator()(token::Identifier) const { return state::NamedColumn{}; }

    // All the other tokens, put it in the invalid state
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
};

State transition(state::SelectStmt, const Token &token) {
    return std::visit(TransitionFromSelectVisitor{}, token.value());
}

struct TransitionFromAllColumnsVisitor {
    State operator()(token::From) const { return state::FromClause{}; }

    // All the other tokens, put it in the invalid state
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }
};

State transition(state::AllColumns, const Token &token) {
    return std::visit(TransitionFromAllColumnsVisitor{}, token.value());
}

struct TransitionFromNamedColumnsVisitor {
    State operator()(token::From) const { return state::FromClause{}; }
    State operator()(token::Comma) const { return state::MoreColumns{}; }

    // All the other tokens, put it in the invalid state
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }
};

State transition(state::NamedColumn, const Token &token) {
    return std::visit(TransitionFromNamedColumnsVisitor{}, token.value());
}

struct TransitionFromMoreColumnsVisitor {
    State operator()(token::Identifier) const { return state::NamedColumn{}; }

    // All the other tokens, put it in the invalid state
     State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
};

State transition(state::MoreColumns, const Token &token) {
    return std::visit(TransitionFromMoreColumnsVisitor{}, token.value());
}

struct TransitionFromFromClauseVisitor {
    State operator()(token::Identifier) const { return state::TableName{}; }

    // All the other tokens, put it in the invalid state
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::Semicolon) const { return state::Invalid{}; }
};

State transition(state::FromClause, const Token &token) {
    return std::visit(TransitionFromFromClauseVisitor{}, token.value());
}

struct TransitionFromTableNameVisitor {
    State operator()(token::Semicolon) const { return state::Valid{}; }

    // All the other tokens, put it in the invalid state
    State operator()(token::From) const { return state::Invalid{}; }
    State operator()(token::Comma) const { return state::Invalid{}; }
    State operator()(token::Asterisks) const { return state::Invalid{}; }
    State operator()(token::Select) const { return state::Invalid{}; }
    State operator()(token::Identifier) const { return state::Invalid{}; }
};

State transition(state::TableName, const Token &token) {
    return std::visit(TransitionFromTableNameVisitor{}, token.value());
}


State transition(state::Valid, const Token &token) {
    // TODO: Implement
    // Selbe transitions wie bei TableName
    return std::visit(TransitionFromTableNameVisitor{}, token.value());
}



State transition(state::Invalid, const Token &token) {
    // TODO: Implement
    // Kann man es nicht so lassen? Aus den Invalid State kommt man nicht raus...
    return state::Invalid{};
}

bool is_valid_sql_query(const std::vector<Token> &tokens){
    SqlValidator validitor;
    for(int i=0;i<tokens.size();i++)
    {
        validitor.handle(tokens.at(i));
    }
    return validitor.is_valid();
}

} // namespace sql
