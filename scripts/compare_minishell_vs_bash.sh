#!/usr/bin/env bash
# Read tester_text.txt line by line, run each line in ./minishell and in bash,
# write results to compare_results.txt with minishell output, 3 tabs, bash output.
set -euo pipefail

INPUT="tester_text.txt"
OUT="compare_results.txt"

# prepare output
: > "$OUT"

escape_newlines() {
	# escape backslashes first, then tabs, then join lines and replace newlines
	# this preserves existing backslashes in output
	sed -e 's/\\/\\\\/g' -e 's/\t/\\t/g' -e ':a' -e 'N' -e '$!ba' -e 's/\n/\\n/g'
}

while IFS= read -r line || [ -n "$line" ]; do
	# skip empty lines
	[ "$line" = "" ] && continue

	# run command in minishell and bash, capture stdout+stderr
	min_out=$(printf '%s\n' "$line" | ./minishell 2>&1 || true)
	bash_out=$(printf '%s\n' "$line" | bash 2>&1 || true)

	# write: command, minishell output, bash output, two blank lines
	printf '%s\n' "$line" >> "$OUT"
	if [ -n "$min_out" ]; then
		printf '%s\n' "$min_out" >> "$OUT"
	else
		printf '\n' >> "$OUT"
	fi
	if [ -n "$bash_out" ]; then
		printf '%s\n' "$bash_out" >> "$OUT"
	else
		printf '\n' >> "$OUT"
	fi
	printf '\n\n' >> "$OUT"
done < "$INPUT"

echo "Results written to $OUT"
