#include <iostream>
#include "parsing_driver.h"
#include "printer.h"
#include "semantic_analyzer_caller.h"


int main(int argc, char *argv[]) {
    try{
        driver drv;
        for (int i = 1; i < argc; ++i) {
            if (argv[i] == std::string("-p"))
                drv.set_trace_parsing(true);
            else if (argv[i] == std::string("-s"))
                drv.set_trace_scanning(true);
            else if (!drv.parse(argv[i]))
                std::cout << "parsing ended\n";
        }
        AstPrinter printer;
        drv.tree_->GetRoot()->Accept(printer);

        SemanticAnalyzerCaller analyzer;
        auto error_context = analyzer.CallAnalyzer(*drv.tree_);
        error_context.PrintOut(std::cout);
        return 0;
    }catch (std::exception& e){
        std::cout << e.what();
    }
}
