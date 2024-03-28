# Fold
Folding can be achieved by adding the `let hasFolder = 1;` in the TD file of an op. The fold operation is "local" by design and can only modify the single operation being folded, use existing SSA values, and may not create new ops. This is different from the `rewrite` operation which can create new ops and modify the entire graph.

The intermediate constants are all pruned, and all that remains is the return value and no operations. Canonicalize cannot propagate constants through control flow, and as such should be thought of as more “local” than sccp.

Both of these, however, are supported via folding, which is the process of taking series of ops and merging them together into simpler ops. It also requires our dialect has some sort of constant operation, which is inserted (“materialized”) with the results of a fold. Folding and canonicalization are more general than what I’m showing here, so we’ll come back to what else they can do in a future article.

The rough outline of what is needed to support folding in this way is:

    Adding a constant operation
    Adding a materialization hook
    Adding folders for each op

