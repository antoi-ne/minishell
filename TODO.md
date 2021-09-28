# TODO

- update execution method: piped commands must be started concurently, and only the return value of the last command must be sent to $? (https://unix.stackexchange.com/questions/194544/are-commands-in-a-pipeline-run-simultaneously/194551)
- manage redirects/pipes being overwritten by each other (and close() overwritten fd's)
- builtins
- signals (including signals for here-document (<<) redirection)
- errors management (mostly parsing errors)
- return values from builtins & binaries ($?)
- updating necessary environement variables ($_, $SHLVL)
- leaks
- norm

# known edge-cases/bugs

- tokens only containing the character '$' (nothing following it) in words & DQSs get replaced by an empty string instead of being kept as-is

# before submitting

- remove useless preproc. instructions (mostly includes)
- remove useless functions (print_tokens, print_progs, etc)
- check norm & leaks!!
- replace Makefile wildcard with hardcoded list of source files
- replace the Makefile's compiler definition to 'gcc' (without -g)
