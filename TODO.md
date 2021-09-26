# TODO

- update execution method: piped commands must be started concurently, and only the return value of the last command must be sent to $? (https://unix.stackexchange.com/questions/194544/are-commands-in-a-pipeline-run-simultaneously/194551) ()
- builtins
- signals (including signals for here-document (<<) redirection)
- errors management (mostly parsing errors)
- return values from builtins & binaries ($?)
- updating necessary environement variables ($_, $SHLVL)
- leaks
- norm

# known edge-cases/bugs

- tokens only containing the character '$' (nothing following it) in words & DQSs get replaced by an empty string instead of being kept as-is

- 
