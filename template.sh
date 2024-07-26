#!/usr/bin/env bash

set -e

PROMPT_INPUT="Extract all example input data from the problem statement.
DO NOT include the example output data. Response ONLY with data in a code block."

PROMPT_OUTPUT="Extract all example output data from the problem statement.
DO NOT include the example input data. Response ONLY with data in a code block."

LANG=cpp
OUTPUT_CODE="a.${LANG}"

if [ -n "$1" ]; then
	LANG=$1
fi

# echo "Please paste your problem here (CTRL+D to finish):"
# cat >problem.txt

echo "Generating template..."
echo "// Created at:" $(date) > "$OUTPUT_CODE"
cat "template.${LANG}" problem.txt |
	${HOME}/dotfiles/chatgpt.sh --model "gpt-4o" --stdin |
	tee /dev/stderr |
	awk '/```/{flag=!flag;next} flag{print}' >> "$OUTPUT_CODE"

echo "Parsing input..."
cat problem.txt |
	${HOME}/dotfiles/chatgpt.sh --stdin "$PROMPT_INPUT" |
	tee /dev/stderr |
	awk '/```/{flag=!flag;next} flag{print}' > in.txt


echo "Parsing output..."
cat problem.txt |
	${HOME}/dotfiles/chatgpt.sh --stdin "$PROMPT_OUTPUT" |
	tee /dev/stderr |
	awk '/```/{flag=!flag;next} flag{print}' > ans.txt
