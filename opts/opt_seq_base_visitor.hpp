#ifndef BFC_OPT_SEQ_BASE_VISITOR_HPP
#define BFC_OPT_SEQ_BASE_VISITOR_HPP

#include <stdexcept>
#include "ast/mod.hpp"
#include "ast/seq.hpp"
#include "ast/visitor.hpp"

namespace bfc {
namespace ast {

class opt_seq_base_visitor : public visitor {
    
    using error = std::runtime_error;

public:

    seq result(void) {
        return opt_seq;
    }

    status visit(program &node) {
        throw error("Malformed syntax tree: optimizer encountered nested program node"); 
    }
    
    status visit(const program &node) {
        throw error("Malformed syntax tree: optimizer encountered nested program node"); 
    }
    
    virtual status visit(set &node) {
        return handle_set(node);
    }
    
    virtual status visit(const set &node) {
        return handle_set(node);
    }
    
    virtual status visit(add &node) {
        return handle_add(node);
    }
    
    virtual status visit(const add &node) {
        return handle_add(node);
    }
    
    virtual status visit(sub &node) {
        return handle_sub(node);
    }
    
    virtual status visit(const sub &node) {
        return handle_sub(node);
    }
    
    virtual status visit(mov &node) {
        return handle_mov(node);
    }
    
    virtual status visit(const mov &node) {
        return handle_mov(node);
    }
    
    virtual status visit(mul &node) {
        return handle_mul(node);        
    }
    
    virtual status visit(const mul &node) {
        return handle_mul(node);
    }
    
    virtual status visit(loop &node) {
        return handle_loop(node);
    }
    
    virtual status visit(const loop &node) {
        return handle_loop(node);
    }
    
    virtual status visit(read &node) {
        return handle_read(node);
    }
    
    virtual status visit(const read &node) {
        return handle_read(node);
    }
    
    virtual status visit(write &node) {
        return handle_write(node);
    }
    
    virtual status visit(const write &node) {
        return handle_write(node);
    }
    
protected:

    status handle_set(set &node) {
        opt_seq.emplace_back(new set(node.loc(), node.offset(), node.value()));
        return CONTINUE;
    }
    
    status handle_set(const set &node) {
        opt_seq.emplace_back(new set(node.loc(), node.offset(), node.value()));
        return CONTINUE;
    }
    
    status handle_add(add &node) {
        opt_seq.emplace_back(new add(node.loc(), node.offset(), node.value()));
        return CONTINUE;
    }
    
    status handle_add(const add &node) {
        opt_seq.emplace_back(new add(node.loc(), node.offset(), node.value()));
        return CONTINUE;
    }
    
    status handle_sub(sub &node) {
        opt_seq.emplace_back(new sub(node.loc(), node.offset(), node.value()));
        return CONTINUE;
    }
    
    status handle_sub(const sub &node) {
        opt_seq.emplace_back(new sub(node.loc(), node.offset(), node.value()));
        return CONTINUE;
    }
    
    status handle_mul(mul &node) {
        opt_seq.emplace_back(new mul(node.loc(), node.offset(), node.value()));
        return CONTINUE;
    }
    
    status handle_mul(const mul &node) {
        opt_seq.emplace_back(new mul(node.loc(), node.offset(), node.value()));
        return CONTINUE;
    }
    
    status handle_mov(mov &node) {
        opt_seq.emplace_back(new mov(node.loc(), node.offset()));
        return CONTINUE;
    }
    
    status handle_mov(const mov &node) {
        opt_seq.emplace_back(new mov(node.loc(), node.offset()));
        return CONTINUE;
    }
    
    status handle_loop(loop &node) {
        // create an empty sequence
        seq temp_seq;
        // swap our optimized sequence for the empty one
        opt_seq.swap(temp_seq);
        // optimize the node's inner sequence
        node.accept(*this);
        // swap back the old optimized sequence
        opt_seq.swap(temp_seq);
        // create a new node and add to the sequence
        opt_seq.emplace_back(new loop(node.loc(), temp_seq));
        return CONTINUE;
    }
    
    status handle_loop(const loop &node) {
        // create an empty sequence
        seq temp_seq;
        // swap our optimized sequence for the empty one
        opt_seq.swap(temp_seq);
        // optimize the node's inner sequence
        node.accept(*this);
        // swap back the old optimized sequence
        opt_seq.swap(temp_seq);
        // create a new node and add to the sequence
        opt_seq.emplace_back(new loop(node.loc(), temp_seq));
        return CONTINUE;
    }
    
    status handle_read(read &node) {
        opt_seq.emplace_back(new read(node.loc(), node.offset()));
        return CONTINUE;
    }
    
    status handle_read(const read &node) {
        opt_seq.emplace_back(new read(node.loc(), node.offset()));
        return CONTINUE;
    }
    
    status handle_write(write &node) {
        opt_seq.emplace_back(new write(node.loc(), node.offset()));
        return CONTINUE;
    }
    
    status handle_write(const write &node) {
        opt_seq.emplace_back(new write(node.loc(), node.offset()));
        return CONTINUE;
    }
    
protected:

    // optimized sequence of previous nodes visited
    seq opt_seq;

};

}
}

#endif /* !BFC_OPT_SEQ_BASE_VISITOR_HPP */
