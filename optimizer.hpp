#ifndef BFC_OPTIMIZER_HPP
#define BFC_OPTIMIZER_HPP

#include <vector>
#include <memory>
#include "ast.hpp"
#include "opts.hpp"

namespace bfc {

class optimizer {

    public:

        ast_node optimize(const ast_node &program) {
            // create list of optimizers
            std::vector<std::unique_ptr<opt_seq_base_visitor>> opts;
            
            // combine increments
            std::unique_ptr<opt_seq_base_visitor> inc = std::make_unique<combine_inc_visitor>();
            opts.push_back(std::move(inc));
            // combine move ops
            std::unique_ptr<opt_seq_base_visitor> mov = std::make_unique<combine_ptr_visitor>();
            opts.push_back(std::move(mov));
            // convert clearing loops to SET(0) ops
            std::unique_ptr<opt_seq_base_visitor> clear = std::make_unique<clear_loops_visitor>();
            opts.push_back(std::move(clear));
            // convert multiplying loops to MUL ops
            std::unique_ptr<opt_seq_base_visitor> mul = std::make_unique<mul_loops_visitor>();
            opts.push_back(std::move(mul));
            // combine new set ops with each other (and with fold increments into them)
            std::unique_ptr<opt_seq_base_visitor> set = std::make_unique<combine_set_visitor>();
            opts.push_back(std::move(set));

            opt_program_visitor opt_prog(std::move(opts));
            // run optimizations
            program.accept(opt_prog);

            return opt_prog.result();
        }

};

}
#endif /* !BFC_OPTIMIZER_HPP */
