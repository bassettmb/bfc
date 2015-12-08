#ifndef BFC_OPTIMIZER_HPP
#define BFC_OPTIMIZER_HPP

#include <vector>
#include "ast.hpp"
#include "opts.hpp"

namespace bfc {

class optimizer {
    
    public:
    
        optimizer(bool clean, bool quick) : clean(clean), quick(quick)  {}
        
        ast_node optimize(const ast_node &program) {
            return program;
            /*
            // create list of optimizers
            std::vector<opt_seq_base_visitor> opts;
            combine_inc_visitor inc;
            opts.push_back(inc);
            
            if (clean) {
                // add additional optimizers
                dead_loops_visitor deadloop;
                opts.push_back(deadloop);
            }
            
            opt_program_visitor opt_prog(std::move(opts));
            // run optimizations
            program.accept(opt_prog);
            
            if (!quick) {
                if (!program.equals(opt_prog.result()) {
                    // re-run optimizations until AST is stable
                    ast_node result;
                    do {
                        result = opt_prog.result();
                        result.accept(opt_prog);
                    } while (result != opt_prog.result());
                }
            }
            
            return opt_prog.result();
            */
        }    

    private:
        // indicates if redundant code should be cleaned up during optimization
        bool clean;
        
        // indicates if one-pass or full optimization is performed
        bool quick;
        
    
};

}
#endif /* !BFC_OPTIMIZER_HPP */
