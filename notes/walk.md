# Walking
Two methods to walk the AST:
1. Match and Rewrite patterns with the rewrite engine.
2. Walk the entire syntax tree from the root operation

## Match and Rewrite
The pattern rewrite engine is convinient for **local** transformations. Local meaning that the input and out can be detected via a subset of the AST as a directed acyclic graph. Essentially, any operation that can be identified by looking around the neighboring operations in the same block and applying some filtering logic. E.g., “is this exp operation followed by a log operation with no other uses of the output of the exp?”

## Walk the entire syntax tree
Some rewrites require more complex analysis and optimzaitons which need to construct the entire dataflow of a program to work. A good example is common subexpression elimination, which determines whether it is cost effective to extract a subexpression used in multiple places into a separate variable. Doing so may introduce additional cost of memory access, so it depends both on the operation’s cost and on the availability of registers at that point in the program. You can’t get this information by pattern matching the AST locally.

## Conclusion
The wisdom seems to be: using the pattern rewrite engine is usually easier than writing a pass that walks the AST. You don’t need large case/switch statements to handle everything that could show up in the IR. The engine handles re-applying patterns many times. And so you can write the patterns in isolation and trust the engine to combine them appropriately.